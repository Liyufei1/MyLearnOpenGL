#include "MeshManager.h"
#include "Common/CommonFunLib.hpp"
#include "Mesh.h"
#include <algorithm>

void MeshManager::Render(){
    for (auto mesh : m_meshes) {
        mesh->Draw();
        // LOG(LOGTEMP,"Render Mesh");
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