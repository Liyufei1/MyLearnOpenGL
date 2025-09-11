#include "MeshManager.h"
#include "Common/CommonFunLib.hpp"
#include "Mesh.h"
#include "Camera/Camera.h"

void MeshManager::Render(){
    for (auto mesh : m_meshes) {
        //设置模型矩阵
        mesh->GetShaderProgram()->SetParamater<glm::mat4>("uModelMatrix", mesh->GetModelMatrix());
        //设置视图投影矩阵
		mesh->GetShaderProgram()->SetParamater<glm::mat4>("uViewProjectionMatrix", mCamera->GetViewProjectionMMatrix());
        //绘制
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

MeshManager::MeshManager(){
    mCamera = std::make_shared<Camera>();
}