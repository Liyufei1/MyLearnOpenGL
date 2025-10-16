#pragma once
#include <memory>

#include <unordered_set>
#include <map>

class StaticMesh;
class ICamera;
class Light;
class ShaderProgram;

class RenderManager
{
public:
    static RenderManager& GetInstance(){
        static RenderManager instance;
        return instance;
    }
    // 删除拷贝构造和赋值运算符，禁止复制
    RenderManager(const RenderManager&) = delete;
    RenderManager& operator=(const RenderManager&) = delete;

    void Render();

    void BindData();

    void AddMesh(std::shared_ptr<StaticMesh> mesh);
    void RemoveMesh(std::shared_ptr<StaticMesh> mesh);

    void AddLight(Light* light){m_Lights.insert(light);};

    void AddShaderProgram(std::shared_ptr<ShaderProgram> pSP){m_ShaderPrograms.insert(pSP);}

private:
    RenderManager();
    ~RenderManager() = default;
    std::shared_ptr<ICamera> mCamera = nullptr;
    std::unordered_set<std::shared_ptr<StaticMesh>> m_meshes;
    std::unordered_set<Light*> m_Lights;
    std::unordered_set<std::shared_ptr<ShaderProgram>> m_ShaderPrograms;
    // std::map<int,std::unordered_set<std::shared_ptr<StaticMesh>>> mMeshMap;
};