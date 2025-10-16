#include "RenderManager.h"
#include "Common/CommonFunLib.hpp"
#include "Mesh.h"
#include "Camera/Camera.h"
#include "Light/Light.h"
#include "glm/ext/vector_float3.hpp"

void RenderManager::Render(){
    
    for (auto SP = m_ShaderPrograms.begin();SP != m_ShaderPrograms.end();SP++) {
        for(auto light : m_Lights){
            light->UpdateLight(*SP);
            if (std::next(SP) == m_ShaderPrograms.end()) {
                light->bIsDirty = false;
            }
        }
    }

    for (auto mesh : m_meshes) {
        mesh->GetMaterial()->Use();
        std::shared_ptr<ShaderProgram> TempShader = mesh->GetMaterial()->GetShaderProgram();

        //设置光照
        // TempShader->SetParamater(const char *name, T value)

        //设置模型矩阵
        TempShader->SetParamater<glm::mat4>("uModelMatrix", mesh->GetModelMatrix());

        //设置视图投影矩阵
		TempShader->SetParamater<glm::mat4>("uViewProjectionMatrix", mCamera->GetViewProjectionMMatrix());
		TempShader->SetParamater<glm::vec3>("uCameraPos", mCamera->GetPosition());

        //绘制
        mesh->Draw();
    }
}
void RenderManager::BindData(){
    for (auto mesh : m_meshes) {
        mesh->BindGlVertexAttribPointer();
    }
}


void RenderManager::AddMesh(std::shared_ptr<StaticMesh> mesh){
    // mMeshMap[mesh->GetMaterial()->GetShaderProgram()->GetProgramID()].insert(mesh);
    m_meshes.insert(mesh);
}
void RenderManager::RemoveMesh(std::shared_ptr<StaticMesh> mesh){
    // mMeshMap[mesh->GetMaterial()->GetShaderProgram()->GetProgramID()].erase(mesh);
    m_meshes.erase(mesh);
}

RenderManager::RenderManager(){
    mCamera = std::make_shared<Camera>();
}