#include "Material.h"
#include "Common/CommonFunLib.hpp"
#include "ShaderProgram.h"
#include <memory>

std::shared_ptr<Material> Material::DefaultMaterial = nullptr;
std::shared_ptr<Material> Material::GetDefaultMaterial(){
    if (DefaultMaterial == nullptr) {
        DefaultMaterial = std::make_shared<Material>();
        DefaultMaterial->SetShaderPrograrm(ShaderProgram::GetDefaultShaderProgram());
    }
    return DefaultMaterial;
}
void Material::Use(){
    if(GetShaderProgram() == nullptr){
        LOG(LOGERROR, "ShaderProgram is null,Use default ShaderProgram");
        SetShaderPrograrm(ShaderProgram::GetDefaultShaderProgram());
        return;
    }
    GetShaderProgram()->Use();
    GetShaderProgram()->SetParamater("uMaterial.diffuse", GetDiffuseColor());
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, mDiffuseTexture->GetTextureID());
    GetShaderProgram()->SetParamater("uMaterial.specular", GetSpecular());
    GetShaderProgram()->SetParamater("uMaterial.shininess", GetShininess());
}

void StdMaterial::Use(){
    if(GetShaderProgram() == nullptr){
        LOG(LOGERROR, "ShaderProgram is null,Use default ShaderProgram");
        SetShaderPrograrm(ShaderProgram::GetDefaultShaderProgram());
        return;
    }
    GetShaderProgram()->Use();
    GetShaderProgram()->SetParamater("uMaterial.diffuse", GetDiffuseColor());
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, mDiffuseTexture->GetTextureID());
    GetShaderProgram()->SetParamater("uMaterial.specular", GetSpecular());
    GetShaderProgram()->SetParamater("uMaterial.shininess", GetShininess());
}

void PhoneMaterial::Use(){
    if(GetShaderProgram() == nullptr){
        LOG(LOGERROR, "PhoneMaterial::ShaderProgram is null,Use default ShaderProgram");
        SetShaderPrograrm(ShaderProgram::GetDefaultShaderProgram());
        return;
    }
    GetShaderProgram()->Use();
    glActiveTexture(GL_TEXTURE8);
    GetShaderProgram()->SetParamater("uMaterial.diffuse", 8);
    glBindTexture(GL_TEXTURE_2D, GetDiffuseTexture()->GetTextureID());
    GetShaderProgram()->SetParamater("uMaterial.specular", GetSpecular());
    GetShaderProgram()->SetParamater("uMaterial.shininess", GetShininess());
}