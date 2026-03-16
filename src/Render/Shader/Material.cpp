#include "Material.h"
#include "Render/RenderService.h"
#include "Render/Texture/Texture2D.h"
#include "Render/Shader/ShaderProgram.h"
#include "glad/glad.h"
#include "Common/CommonFunLib.hpp"

Material::Material(const std::string& shaderName) 
    : mShaderName(shaderName) {
}

// ==================== 属性设置 ====================

void Material::Set(const std::string& name, const MaterialValue& value) {
    mProperties[name] = value;
}

void Material::SetInt(const std::string& name, int value) {
    mProperties[name] = value;
}

void Material::SetFloat(const std::string& name, float value) {
    mProperties[name] = value;
}

void Material::SetVec2(const std::string& name, const glm::vec2& value) {
    mProperties[name] = value;
}

void Material::SetVec3(const std::string& name, const glm::vec3& value) {
    mProperties[name] = value;
}

void Material::SetVec4(const std::string& name, const glm::vec4& value) {
    mProperties[name] = value;
}

void Material::SetMat4(const std::string& name, const glm::mat4& value) {
    mProperties[name] = value;
}

void Material::SetTexture(const std::string& name, std::shared_ptr<Texture2D> texture) {
    SetTexture(name, texture, mNextTextureSlot++);
}

void Material::SetTexture(const std::string& name, std::shared_ptr<Texture2D> texture, int slot) {
    mTextures[name] = {texture, slot};
    // 同时记录纹理单元到属性字典
    mProperties[name] = slot;
}

// ==================== 属性获取 ====================

const MaterialValue* Material::Get(const std::string& name) const {
    auto it = mProperties.find(name);
    if (it != mProperties.end()) {
        return &it->second;
    }
    return nullptr;
}

bool Material::Has(const std::string& name) const {
    return mProperties.find(name) != mProperties.end();
}

// ==================== 着色器 ====================

void Material::SetShader(const std::string& name) {
    mShaderName = name;
}

ShaderProgram* Material::GetShaderProgram() const {
    if (mShaderName.empty()) {
        return nullptr;
    }
    return RenderService::GetInstance().GetShader(mShaderName).get();
}

// ==================== 应用材质 ====================

void Material::Apply() {
    ShaderProgram* shader = GetShaderProgram();
    if (!shader) {
        LOG(LOGERROR, "Material::Apply: Shader not found [" + mShaderName + "]");
        return;
    }
    
    shader->Use();
    
    // 绑定纹理
    for (const auto& [name, slotInfo] : mTextures) {
        if (slotInfo.texture) {
            shader->SetParamater(name.c_str(), slotInfo.slot);
            glActiveTexture(GL_TEXTURE0 + slotInfo.slot);
            glBindTexture(GL_TEXTURE_2D, slotInfo.texture->GetTextureID());
        }
    }
    
    // 绑定其他属性
    for (const auto& [name, value] : mProperties) {
        // 跳过纹理属性（已处理）
        if (mTextures.find(name) != mTextures.end()) {
            continue;
        }
        
        std::visit([shader, &name](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, int>) {
                shader->SetParamater(name.c_str(), arg);
            } else if constexpr (std::is_same_v<T, float>) {
                shader->SetParamater(name.c_str(), arg);
            } else if constexpr (std::is_same_v<T, glm::vec2>) {
                // 需要在 ShaderProgram 中添加 vec2 支持
            } else if constexpr (std::is_same_v<T, glm::vec3>) {
                shader->SetParamater(name.c_str(), arg);
            } else if constexpr (std::is_same_v<T, glm::vec4>) {
                shader->SetParamater(name.c_str(), arg);
            } else if constexpr (std::is_same_v<T, glm::mat4>) {
                shader->SetParamater(name.c_str(), arg);
            }
            // std::shared_ptr<Texture2D> 由纹理槽处理
        }, value);
    }
}

// ==================== 静态方法 ====================

std::shared_ptr<Material> Material::GetDefaultMaterial() {
    static std::shared_ptr<Material> sDefaultMaterial = nullptr;
    if (!sDefaultMaterial) {
        sDefaultMaterial = std::make_shared<Material>("Base");
    }
    return sDefaultMaterial;
}