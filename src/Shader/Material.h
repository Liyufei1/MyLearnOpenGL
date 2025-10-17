#pragma once
#include "Shaderprogram.h"
#include "Texture/Texture2D.h"
#include "glm/ext/vector_float3.hpp"
#include <memory>


class Material
{
private:
    std::shared_ptr<Texture2D> mDiffuseTexture = nullptr;
    std::shared_ptr<Texture2D> mSpecularTexture = nullptr;
    glm::vec3 mDiffuseColor{ 1.0f, 1.0f, 1.0f };
    glm::vec3 mSpecularColor{ 1.0f, 1.0f, 1.0f };
    float mShininess = 32.0f;

    std::shared_ptr<ShaderProgram> mShaderProgram = nullptr;

    static std::shared_ptr<Material> DefaultMaterial;

public:
    static std::shared_ptr<Material> GetDefaultMaterial();

    static std::shared_ptr<Material> CreateDefaultMaterial();


    Material(std::shared_ptr<ShaderProgram> pShaderProgram) : mShaderProgram(pShaderProgram){}
    Material()  = default;
    ~Material() = default;

    virtual void Use();
    void SetDiffuseTexture(std::shared_ptr<Texture2D> pDiffuse){mDiffuseTexture = pDiffuse;}
    void SetDiffuseColor(glm::vec3 pDiffuseColor){mDiffuseColor = pDiffuseColor;}
    void SetSpecularTexture(std::shared_ptr<Texture2D> pSpecular){mSpecularTexture = pSpecular;}
    void SetSpecularColor(glm::vec3 pSpecular){mSpecularColor = pSpecular;}
    void SetShininess(float pShininess){mShininess = pShininess;}
    void SetShaderPrograrm(std::shared_ptr<ShaderProgram> pShaderProgram){mShaderProgram = pShaderProgram;}
    std::shared_ptr<Texture2D>  GetDiffuseTexture(){return mDiffuseTexture;}
    glm::vec3 GetDiffuseColor(){return mDiffuseColor;}
    std::shared_ptr<Texture2D> GetSpecularTexture(){return mSpecularTexture;}
    glm::vec3 GetSpecularColor(){return mSpecularColor;}
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