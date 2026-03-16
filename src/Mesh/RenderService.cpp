#include "RenderService.h"
#include "Common/CommonFunLib.hpp"
#include "Mesh.h"
#include "Camera/Camera.h"
#include "Light/Light.h"
#include "Shader/ShaderProgram.h"
#include "glm/ext/vector_float3.hpp"
#include "glm/glm.hpp"

RenderService::RenderService() {
    mCamera = std::make_shared<Camera>();
}

// ==================== 着色器管理 ====================

std::shared_ptr<ShaderProgram> RenderService::GetOrCreateShader(
    const std::string& vertexPath,
    const std::string& fragmentPath) {
    
    std::string key = MakeShaderKey(vertexPath, fragmentPath);
    
    auto it = mPathShaderCache.find(key);
    if (it != mPathShaderCache.end()) {
        return it->second;
    }

    auto shader = std::make_shared<ShaderProgram>(vertexPath.c_str(), fragmentPath.c_str());
    mPathShaderCache[key] = shader;
    
    LOG(LOGTEMP, "RenderService: Created shader [" + key + "]");
    return shader;
}

void RenderService::RegisterShader(const std::string& name, std::shared_ptr<ShaderProgram> shader) {
    if (!shader) {
        LOG(LOGERROR, "RenderService::RegisterShader: shader is null");
        return;
    }
    mNameShaderCache[name] = shader;
    LOG(LOGTEMP, "RenderService: Registered shader [" + name + "]");
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
    mPathShaderCache.clear();
    mNameShaderCache.clear();
    LOG(LOGTEMP, "RenderService: Cleared all shaders");
}

void RenderService::PreloadDefaultShaders() {
    auto baseShader = GetOrCreateShader("src/Shader/BaseShader/BaseVertex.glsl", 
                                         "src/Shader/BaseShader/BaseFragment.glsl");
    RegisterShader("Base", baseShader);

    auto phoneShader = GetOrCreateShader("src/Shader/PhoneShader/PhoneVertex.glsl",
                                          "src/Shader/PhoneShader/PhoneFragment.glsl");
    RegisterShader("Phone", phoneShader);
}

std::string RenderService::MakeShaderKey(const std::string& vertexPath, const std::string& fragmentPath) const {
    return vertexPath + "|" + fragmentPath;
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
        
        auto shader = mesh->GetMaterial()->GetShaderProgram().get();
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
            mesh->GetMaterial()->Use();
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
