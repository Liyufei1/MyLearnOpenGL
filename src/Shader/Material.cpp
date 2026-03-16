#include "Material.h"
#include "Mesh/RenderService.h"
#include "Common/CommonFunLib.hpp"
#include "ShaderProgram.h"
#include <memory>

std::shared_ptr<Material> Material::GetDefaultMaterial() {
    static std::shared_ptr<Material> DefaultMaterial = nullptr;
    if (DefaultMaterial == nullptr) {
        DefaultMaterial = std::make_shared<Material>();
        DefaultMaterial->SetShaderProgram(ShaderProgram::GetDefaultShaderProgram());
    }
    return DefaultMaterial;
}

std::shared_ptr<Material> Material::CreateDefaultMaterial() {
    auto mat = std::make_shared<Material>();
    mat->SetShaderProgram(ShaderProgram::GetDefaultShaderProgram());
    return mat;
}

void Material::SetShaderByName(const std::string& name) {
    auto shader = RenderService::GetInstance().GetShader(name);
    if (shader) {
        mShaderProgram = shader;
    } else {
        LOG(LOGERROR, "Material::SetShaderByName: Shader not found [" + name + "]");
    }
}

void Material::SetShaderByPath(const std::string& vertexPath, const std::string& fragmentPath) {
    mShaderProgram = RenderService::GetInstance().GetOrCreateShader(vertexPath, fragmentPath);
}

void Material::Use() {
    if (!mShaderProgram) {
        LOG(LOGERROR, "Material::Use: ShaderProgram is null, using default");
        mShaderProgram = ShaderProgram::GetDefaultShaderProgram();
    }
    
    mShaderProgram->Use();
    mShaderProgram->SetParamater("uMaterial.diffuse", GetDiffuseColor());
    mShaderProgram->SetParamater("uMaterial.specular", GetSpecularColor());
    mShaderProgram->SetParamater("uMaterial.shininess", GetShininess());
}

void StdMaterial::Use() {
    if (!GetShaderProgram()) {
        LOG(LOGERROR, "StdMaterial::Use: ShaderProgram is null, using default");
        SetShaderProgram(ShaderProgram::GetDefaultShaderProgram());
    }

    GetShaderProgram()->Use();
    GetShaderProgram()->SetParamater("uMaterial.diffuse", GetDiffuseColor());
    GetShaderProgram()->SetParamater("uMaterial.specular", GetSpecularColor());
    GetShaderProgram()->SetParamater("uMaterial.shininess", GetShininess());
}

void PhoneMaterial::Use() {
    if (!GetShaderProgram()) {
        LOG(LOGERROR, "PhoneMaterial::Use: ShaderProgram is null, using default");
        SetShaderProgram(ShaderProgram::GetDefaultShaderProgram());
    }

    if (!GetDiffuseTexture()) {
        LOG(LOGERROR, "PhoneMaterial::Use: DiffuseTexture is null");
        return;
    }

    GetShaderProgram()->Use();
    
    // 设置纹理单元
    GetShaderProgram()->SetParamater("uMaterial.diffuse", 8);
    glActiveTexture(GL_TEXTURE8);
    glBindTexture(GL_TEXTURE_2D, GetDiffuseTexture()->GetTextureID());

    if (GetSpecularTexture()) {
        GetShaderProgram()->SetParamater("uMaterial.specular", 9);
        glActiveTexture(GL_TEXTURE9);
        glBindTexture(GL_TEXTURE_2D, GetSpecularTexture()->GetTextureID());
    }

    GetShaderProgram()->SetParamater("uMaterial.shininess", GetShininess());
}
