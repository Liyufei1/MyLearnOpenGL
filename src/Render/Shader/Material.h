#pragma once

#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/ext/vector_float4.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include <memory>
#include <unordered_map>
#include <string>
#include <variant>

class Texture2D;
class ShaderProgram;

// 材质属性值（支持多种类型）
using MaterialValue = std::variant<
    int,
    float,
    glm::vec2,
    glm::vec3,
    glm::vec4,
    glm::mat4,
    std::shared_ptr<Texture2D>
>;

// 纹理槽信息
struct TextureSlot {
    std::shared_ptr<Texture2D> texture;
    int slot;  // 纹理单元
};

class Material {
public:
    Material() = default;
    explicit Material(const std::string& shaderName);
    virtual ~Material() = default;

    // ==================== 属性设置 ====================
    
    // 通用属性设置
    void Set(const std::string& name, const MaterialValue& value);
    
    // 便捷方法
    void SetInt(const std::string& name, int value);
    void SetFloat(const std::string& name, float value);
    void SetVec2(const std::string& name, const glm::vec2& value);
    void SetVec3(const std::string& name, const glm::vec3& value);
    void SetVec4(const std::string& name, const glm::vec4& value);
    void SetMat4(const std::string& name, const glm::mat4& value);
    
    // 纹理设置（自动分配纹理单元）
    void SetTexture(const std::string& name, std::shared_ptr<Texture2D> texture);
    
    // 纹理设置（指定纹理单元）
    void SetTexture(const std::string& name, std::shared_ptr<Texture2D> texture, int slot);

    // ==================== 属性获取 ====================
    
    const MaterialValue* Get(const std::string& name) const;
    bool Has(const std::string& name) const;

    // ==================== 着色器 ====================
    
    void SetShader(const std::string& name);
    std::string GetShaderName() const { return mShaderName; }
    ShaderProgram* GetShaderProgram() const;

    // ==================== 应用材质 ====================
    
    // 将材质属性绑定到着色器
    virtual void Apply();

    // 获取默认材质
    static std::shared_ptr<Material> GetDefaultMaterial();

protected:
    // 属性字典
    std::unordered_map<std::string, MaterialValue> mProperties;
    
    // 纹理槽映射（uniform name -> texture slot info）
    std::unordered_map<std::string, TextureSlot> mTextures;
    
    // 着色器名称（由 RenderService 管理）
    std::string mShaderName;
    
    // 下一个可用的纹理单元
    int mNextTextureSlot = 0;
};