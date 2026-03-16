#pragma once
#include "Texture/Texture2D.h"
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>

class StaticMesh;
class ICamera;
class Light;
class ShaderProgram;

class RenderService {
public:
    static RenderService& GetInstance() {
        static RenderService instance;
        return instance;
    }

    RenderService(const RenderService&) = delete;
    RenderService& operator=(const RenderService&) = delete;

    // ==================== 着色器管理 ====================
    
    // 通过名称和路径获取或创建着色器（自动缓存和注册，一步到位）
    std::shared_ptr<ShaderProgram> GetOrCreateShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);

    // 通过名称获取着色器
    std::shared_ptr<ShaderProgram> GetShader(const std::string& name);

    // 检查着色器是否存在
    bool HasShader(const std::string& name) const;

    // 清除所有着色器缓存
    void ClearShaders();

    // 预加载常用着色器
    void PreloadDefaultShaders();

    // ==================== 渲染管理 ====================
    
    // 渲染场景
    void Render();

    // 绑定 GPU 数据（在渲染前调用一次）
    void BindData();

    // ==================== 网格管理 ====================
    
    void AddMesh(std::shared_ptr<StaticMesh> mesh);
    void RemoveMesh(std::shared_ptr<StaticMesh> mesh);
    void ClearMeshes();

    // ==================== 贴图管理 ====================
    
    std::shared_ptr<Texture2D> GetOrCreateTexture(const std::string& name, const std::string& vertexPath);
    std::shared_ptr<Texture2D> GetTexture(const std::string& name);
    void ClearTextures();

    // ==================== 光源管理 ====================
    
    void AddLight(Light* light) { mLights.insert(light); }
    void RemoveLight(Light* light) { mLights.erase(light); }
    void ClearLights() { mLights.clear(); }

    // ==================== 相机管理 ====================
    
    void SetCamera(std::shared_ptr<ICamera> camera) { mCamera = camera; }
    std::shared_ptr<ICamera> GetCamera() const { return mCamera; }

private:
    RenderService();
    ~RenderService() = default;

    // 按着色器分组渲染
    void RenderByShaderGroups();

    // 更新场景级 uniform（相机）
    void UpdateSceneUniforms(ShaderProgram* shader);

    // 更新所有光源
    void UpdateLights(std::shared_ptr<ShaderProgram> shader, bool isLastShader);

    // 名称缓存 name -> ShaderProgram
    std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> mNameShaderCache;

    // 名称缓存 name -> Texture2D
    std::unordered_map<std::string, std::shared_ptr<Texture2D>> mTextureCache;

    std::shared_ptr<ICamera> mCamera = nullptr;
    std::unordered_set<std::shared_ptr<StaticMesh>> mMeshes;
    std::unordered_set<Light*> mLights;
};
