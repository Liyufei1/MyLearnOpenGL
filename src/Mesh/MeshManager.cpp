#include "MeshManager.h"
#include "Mesh.h"
#include <algorithm>

void MeshManager::Render(){
    for (auto mesh : m_meshes) {
        mesh->Draw();
    }
}
void MeshManager::BindData(){
    for (auto mesh : m_meshes) {
        mesh->BindGlVertexAttribPointer();
    }
}


void MeshManager::AddMesh(std::shared_ptr<StaticMesh> mesh){
    m_meshes.insert(mesh);
}
void MeshManager::RemoveMesh(std::shared_ptr<StaticMesh> mesh){
    m_meshes.erase(mesh);
}