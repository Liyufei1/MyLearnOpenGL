#pragma once
#include "ShaderProgram.h"
#include "Texture/Texture2D.h"
#include "glm/ext/vector_float3.hpp"
#include <memory>

class Material {
private:
    std::shared_ptr<Texture2D> mDiffuseTexture = nullptr;
    std::shared_ptr<Texture2D> mSpecularTexture = nullptr;
    glm::vec3 mDiffuseColor{1.0f, 1.0f, 1.0f};
    glm::vec3 mSpecularColor{1.0f, 1.0f, 1.0f};
    float mShininess = 32.0f;

    std::shared_ptr<ShaderProgram> mShaderProgram = nullptr;

public:
    Material() = default;
    Material(std::shared_ptr<ShaderProgram> pShaderProgram) : mShaderProgram(pShaderProgram) {}
    virtual ~Material() = default;

    // 获取默认材质
    static std::shared_ptr<Material> GetDefaultMaterial();

    // 创建默认材质
    static std::shared_ptr<Material> CreateDefaultMaterial();

    // 使用材质（绑定着色器和设置材质参数）
    virtual void Use();

    // 设置纹理
    void SetDiffuseTexture(std::shared_ptr<Texture2D> pDiffuse) { mDiffuseTexture = pDiffuse; }
    void SetSpecularTexture(std::shared_ptr<Texture2D> pSpecular) { mSpecularTexture = pSpecular; }

    // 设置颜色
    void SetDiffuseColor(glm::vec3 pDiffuseColor) { mDiffuseColor = pDiffuseColor; }
    void SetSpecularColor(glm::vec3 pSpecularColor) { mSpecularColor = pSpecularColor; }

    // 设置高光强度
    void SetShininess(float pShininess) { mShininess = pShininess; }

    // 设置着色器程序
    void SetShaderProgram(std::shared_ptr<ShaderProgram> pShaderProgram) { mShaderProgram = pShaderProgram; }

    // 通过名称设置着色器（从 RenderService 获取）
    void SetShaderByName(const std::string& name);

    // 通过路径设置着色器（从 RenderService 获取或创建）
    void SetShaderByPath(const std::string& vertexPath, const std::string& fragmentPath);

    // Getter
    std::shared_ptr<Texture2D> GetDiffuseTexture() { return mDiffuseTexture; }
    glm::vec3 GetDiffuseColor() { return mDiffuseColor; }
    std::shared_ptr<Texture2D> GetSpecularTexture() { return mSpecularTexture; }
    glm::vec3 GetSpecularColor() { return mSpecularColor; }
    float GetShininess() { return mShininess; }
    std::shared_ptr<ShaderProgram> GetShaderProgram() { return mShaderProgram; }
};

class StdMaterial : public Material {
public:
    StdMaterial() = default;
    ~StdMaterial() = default;

    virtual void Use() override;
};

class PhoneMaterial : public Material {
public:
    PhoneMaterial() = default;
    ~PhoneMaterial() = default;

    virtual void Use() override;
};
