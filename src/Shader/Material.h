#pragma once
#include "Shaderprogram.h"
#include "Texture/Texture2D.h"
#include "glm/ext/vector_float3.hpp"
#include <memory>


class Material
{
private:
    std::shared_ptr<Texture2D> mDiffuseTexture = nullptr;
    glm::vec3 mDiffuseColor{ 1.0f, 1.0f, 1.0f };
    glm::vec3 mSpecular{ 1.0f, 1.0f, 1.0f };
    float mShininess = 32.0f;

    std::shared_ptr<ShaderProgram> mShaderProgram = nullptr;

    static std::shared_ptr<Material> DefaultMaterial;

public:
    static std::shared_ptr<Material> GetDefaultMaterial();

    Material(std::shared_ptr<ShaderProgram> pShaderProgram) : mShaderProgram(pShaderProgram){}
    Material()  = default;
    ~Material() = default;

    virtual void Use();
    void SetDiffuseTexture(std::shared_ptr<Texture2D> pDiffuse){mDiffuseTexture = pDiffuse;}
    void SetDiffuseColor(glm::vec3 pDiffuseColor){mDiffuseColor = pDiffuseColor;}
    void SetSpecular(glm::vec3 pSpecular){mSpecular = pSpecular;}
    void SetShininess(float pShininess){mShininess = pShininess;}
    void SetShaderPrograrm(std::shared_ptr<ShaderProgram> pShaderProgram){mShaderProgram = pShaderProgram;}
    std::shared_ptr<Texture2D>  GetDiffuseTexture(){return mDiffuseTexture;}
    glm::vec3 GetDiffuseColor(){return mDiffuseColor;}
    glm::vec3 GetSpecular(){return mSpecular;}
    float GetShininess(){return mShininess;}
    std::shared_ptr<ShaderProgram> GetShaderProgram(){return mShaderProgram;}

};


class StdMaterial : public Material
{
public:
    StdMaterial(){};
    ~StdMaterial() = default;

    virtual void Use()override;
};

class PhoneMaterial : public Material
{
public:
    PhoneMaterial(){};
    ~PhoneMaterial() = default;

    virtual void Use()override;
};