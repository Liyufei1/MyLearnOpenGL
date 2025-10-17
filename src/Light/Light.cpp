#include "Light.h"
#include "Common/CommonFunLib.hpp"
#include <string>
#include "Mesh/MeshLib.h"
#include "Shader/Material.h"



void DirLight::UpdateLight(std::shared_ptr<ShaderProgram>pShaderProgram){
    if (!bIsDirty) {
        return;
    }
    pShaderProgram->SetParamater<glm::vec3>("uDirLight.direction", mDirection);
    
    pShaderProgram->SetParamater<glm::vec3>("uDirLight.ambient", GetAmbient()*mInstensity);
    pShaderProgram->SetParamater<glm::vec3>("uDirLight.diffuse", GetDiffuse()*mInstensity);
    pShaderProgram->SetParamater<glm::vec3>("uDirLight.specula", GetSpecular()*mInstensity);
}
void DirLight::SetInstensity(float pInstensity)
{
    bIsDirty = true ; 
    mInstensity = pInstensity;
}


PointLight::PointLight(){
    mMesh =  BoxMesh();
    mMesh->SetMaterial(Material::CreateDefaultMaterial());
    mMesh->SetLocation(GetLocation());
    mMesh->SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
    mMesh->GetMaterial()->SetDiffuseColor(GetDiffuse());
    // mMesh->GetMaterial()->SetDiffuseColor(glm::vec3(1.0f, 0.0f, 1.0f));
}

void PointLight::UpdateLight(std::shared_ptr<ShaderProgram> pShaderProgram){
    if (!bIsDirty) {
        return;
    }
    std::string tempName = std::string("uPointLights[") + std::to_string(mIndex) + "].";
    pShaderProgram->SetParamater<glm::vec3>((tempName + "position").c_str(), mLocation);

    pShaderProgram->SetParamater((tempName + "constant").c_str(), mConstant);
    pShaderProgram->SetParamater((tempName + "linear").c_str(), mLinear);
    pShaderProgram->SetParamater((tempName + "quadratic").c_str(), mQuadratic);

    
    pShaderProgram->SetParamater<glm::vec3>((tempName + "ambient").c_str(), GetAmbient());
    pShaderProgram->SetParamater<glm::vec3>((tempName + "diffuse").c_str(), GetDiffuse());
    pShaderProgram->SetParamater<glm::vec3>((tempName + "specular").c_str(), GetSpecular());

    // LOG(LOGTEMP,"PointLight::UpdateLight")
    // LOG(LOGTEMP,(tempName + "position").c_str())

}

void PointLight::SetLocation(glm::vec3 pLocation){
    bIsDirty = true ;
    mLocation = pLocation;
    mMesh->SetLocation(pLocation);
}
void SpotLight::UpdateLight(std::shared_ptr<ShaderProgram> pShaderProgram){
    if (!bIsDirty) {
        return;
    }
    std::string tempName = std::string("uSpotLights[") + std::to_string(mIndex) + "].";
    pShaderProgram->SetParamater((tempName + "position").c_str(), mPosition);
    pShaderProgram->SetParamater((tempName + "direction").c_str(), mDirection);
    pShaderProgram->SetParamater((tempName + "cutOff").c_str(), mCutOff);
    pShaderProgram->SetParamater((tempName + "outerCutOff").c_str(), mOuterCutOff);

    
    pShaderProgram->SetParamater<glm::vec3>((tempName + "ambient").c_str(), GetAmbient());
    pShaderProgram->SetParamater<glm::vec3>((tempName + "diffuse").c_str(), GetDiffuse());
    pShaderProgram->SetParamater<glm::vec3>((tempName + "specula").c_str(), GetSpecular());
}
