#include "RenderService.h"
#include "Common/CommonFunLib.hpp"
#include "Scene/Mesh/Mesh.h"
#include "Scene/Camera/Camera.h"
#include "Scene/Light/Light.h"
#include "Render/Shader/ShaderProgram.h"
#include "glm/ext/vector_float3.hpp"
#include "glm/glm.hpp"

RenderService::RenderService() {
    mCamera = std::make_shared<Camera>();
}

// ==================== 着色器管理 ====================

std::shared_ptr<ShaderProgram> RenderService::GetOrCreateShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath) {
    // 先检查名称缓存
    auto nameIt = mNameShaderCache.find(name);
    if (nameIt != mNameShaderCache.end()) {
        return nameIt->second;
    }

    // 创建着色器
    auto shader = std::make_shared<ShaderProgram>(vertexPath.c_str(), fragmentPath.c_str());    
    mNameShaderCache[name] = shader;

    LOG(LOGTEMP, "RenderService: Registered shader [" + name + "]");
    return shader;
}

std::shared_ptr<ShaderProgram> RenderService::GetShader(const std::string& name) {
    auto it = mNameShaderCache.find(name);
    if (it != mNameShaderCache.end()) {
        return it->second;
    }
    LOG(LOGERROR, "RenderService::GetShader: shader not found [" + name + "]");
    return nullptr;
}

bool RenderService::HasShader(const std::string& name) const {
    return mNameShaderCache.find(name) != mNameShaderCache.end();
}

void RenderService::ClearShaders() {
    mNameShaderCache.clear();
    LOG(LOGTEMP, "RenderService: Cleared all shaders");
}

void RenderService::PreloadDefaultShaders() {
    auto baseShader = GetOrCreateShader(
        "Base",
        "src/glsl/BaseShader/BaseVertex.glsl",
        "src/glsl/BaseShader/BaseFragment.glsl");

    auto phoneShader = GetOrCreateShader(
        "Phone",
        "src/glsl/PhoneShader/PhoneVertex.glsl",
        "src/glsl/PhoneShader/PhoneFragment.glsl");

}


// ==================== 渲染管理 ====================

void RenderService::Render() {
    RenderByShaderGroups();
}

void RenderService::RenderByShaderGroups() {
    // 按着色器分组 mesh（减少 glUseProgram 切换）
    std::unordered_map<ShaderProgram*, std::vector<StaticMesh*>> shaderGroups;
    shaderGroups.reserve(mMeshes.size());

    for (auto& mesh : mMeshes) {
        if (!mesh || !mesh->GetMaterial()) continue;
        
        auto shader = mesh->GetMaterial()->GetShaderProgram();
        if (shader) {
            shaderGroups[shader].push_back(mesh.get());
        }
    }

    // 按着色器批量渲染
    size_t shaderIndex = 0;
    size_t totalShaders = shaderGroups.size();

    for (auto& [shader, meshes] : shaderGroups) {
        bool isLastShader = (shaderIndex == totalShaders - 1);
        
        shader->Use();
        UpdateSceneUniforms(shader);
        UpdateLights(std::shared_ptr<ShaderProgram>(shader, [](ShaderProgram*){}), isLastShader);

        for (auto* mesh : meshes) {
            mesh->GetMaterial()->Apply();
            shader->SetParamater<glm::mat4>("uModelMatrix", mesh->GetModelMatrix());
            mesh->Draw();
        }

        shaderIndex++;
    }
}

void RenderService::UpdateSceneUniforms(ShaderProgram* shader) {
    if (!mCamera) {
        LOG(LOGERROR, "RenderService: Camera is null");
        return;
    }

    shader->SetParamater<glm::mat4>("uViewProjectionMatrix", mCamera->GetViewProjectionMMatrix());
    shader->SetParamater<glm::vec3>("uCameraPos", mCamera->GetPosition());
}

void RenderService::UpdateLights(std::shared_ptr<ShaderProgram> shader, bool isLastShader) {
    for (auto light : mLights) {
        if (light) {
            light->UpdateLight(shader);
            if (isLastShader) {
                light->bIsDirty = false;
            }
        }
    }
}

void RenderService::BindData() {
    for (auto& mesh : mMeshes) {
        if (mesh) {
            mesh->BindGlVertexAttribPointer();
        }
    }
}

// ==================== 网格管理 ====================

void RenderService::AddMesh(std::shared_ptr<StaticMesh> mesh) {
    if (mesh) {
        mMeshes.insert(mesh);
    }
}

void RenderService::RemoveMesh(std::shared_ptr<StaticMesh> mesh) {
    mMeshes.erase(mesh);
}

void RenderService::ClearMeshes() {
    mMeshes.clear();
}

std::shared_ptr<Texture2D> RenderService::GetOrCreateTexture(const std::string& name, const std::string& Path){
        // 先检查名称缓存
    auto nameIt = mTextureCache.find(name);
    if (nameIt != mTextureCache.end()) {
        return nameIt->second;
    }

    // 创建着色器
    auto Texture = std::make_shared<Texture2D>(Path.c_str());    
    mTextureCache[name] = Texture;

    LOG(LOGTEMP, "RenderService: Registered Texture [" + name + "]");
    return Texture;
}
std::shared_ptr<Texture2D> RenderService::GetTexture(const std::string& name){
    auto it = mTextureCache.find(name);
    if (it != mTextureCache.end()) {
        return it->second;
    }
    LOG(LOGERROR, "RenderService::GetShader: shader not found [" + name + "]");
    return nullptr;
}

void RenderService::ClearTextures(){
    mTextureCache.clear();
}