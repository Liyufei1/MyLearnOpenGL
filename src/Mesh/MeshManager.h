#pragma once
#include <memory>
#include <unordered_set>
#include <vector>

class StaticMesh;
class ICamera;

class MeshManager
{
public:
    static MeshManager& GetInstance(){
        static MeshManager instance;
        return instance;
    }
    // 删除拷贝构造和赋值运算符，禁止复制
    MeshManager(const MeshManager&) = delete;
    MeshManager& operator=(const MeshManager&) = delete;

    void Render();

    void BindData();

    void AddMesh(std::shared_ptr<StaticMesh> mesh);
    void RemoveMesh(std::shared_ptr<StaticMesh> mesh);
private:
    MeshManager();
    ~MeshManager() = default;
    std::shared_ptr<ICamera> mCamera = nullptr;
    std::unordered_set<std::shared_ptr<StaticMesh>> m_meshes;
};