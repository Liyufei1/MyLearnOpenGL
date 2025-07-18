#include "Mesh.h"
#include "Common/CommonFunLib.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Texture/Texture2D.h"
#include <string>
#include <vector>



StaticMesh::~StaticMesh(){
    MeshManager::GetInstance().RemoveMesh(shared_from_this());
    glDeleteBuffers(1,&mVAO);
    glDeleteBuffers(1,&mVBO);
    glDeleteBuffers(1,&mEBO);
}

void StaticMesh::SetTexture(int index, std::shared_ptr<Texture2D> texture){
    if (index < 0 || index >= MaxTextureCount) {
        lyf::PrintError(std::string("StaticMesh::SetTexture index out of range") + std::to_string(index));
        return;
    }
    mTextures[index] = texture;
}

std::vector<VertexAttrib> MeshBatch::GetData() const{
    std::vector<VertexAttrib> data;
    int vertiesCount = verties.size();
    int tangentsCount = tangents.size();
    int normalsCount = normals.size();
    int colorsCount = colors.size();
    int uvsCount = uvs.size();
    int uvs1Count = uvs1.size();
    int uvs2Count = uvs2.size();

    for (int i = 0; i <  vertiesCount ; i++) {
        glm::vec3 Tempverties{verties[i]};
        glm::vec3 Temptangents{0.0f,0.0f,0.0f};
        glm::vec3 Tempnormals{0.0f,0.0f,0.0f};
        glm::vec3 Tempcolors{0.0f,0.0f,0.0f};
        glm::vec2 Tempuvs{0.0f,0.0f};
        glm::vec2 Tempuvs1{0.0f,0.0f};
        glm::vec2 Tempuvs2{0.0f,0.0f};
        if (i < tangentsCount) Temptangents = tangents[i];
        if (i < normalsCount) Tempnormals = normals[i];
        if (i < colorsCount) Tempcolors = colors[i];
        if (i < uvsCount) Tempuvs = uvs[i];
        if (i < uvs1Count) Tempuvs1 = uvs1[i];
        if (i < uvs2Count) Tempuvs2 = uvs2[i];
        data.push_back(VertexAttrib{Tempverties,Tempnormals,Temptangents,Tempcolors,Tempuvs,Tempuvs1,Tempuvs2});
    }
    

    return data;
}
void StaticMesh::Draw(){
    mShaderProgram.Use();
    for (int i = 0; i < MaxTextureCount; i++) {
        if(mTextures[i]){
            mShaderProgram.SetParamater((std::string("uTexture") + std::to_string(i)).c_str(), i);
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, mTextures[i]->GetTextureID());
        }
    }

    glBindVertexArray(mVAO);
    glDrawElements(GL_TRIANGLES, mMeshBatch.indexs.size(), GL_UNSIGNED_INT, 0);
}


void StaticMesh::BindGlVertexAttribPointer(){
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);
    glGenBuffers(1, &mEBO);

    glBindVertexArray(mVAO);

    std::vector<VertexAttrib> VAB = mMeshBatch.GetData();
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, VAB.size() * sizeof(VertexAttrib), &VAB[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mMeshBatch.indexs.size() * sizeof(glm::int32), mMeshBatch.indexs.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, sizeof(VertexAttrib), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, sizeof(VertexAttrib), (void*)offsetof(VertexAttrib, tangent));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2,3, GL_FLOAT, GL_FALSE, sizeof(VertexAttrib), (void*)offsetof(VertexAttrib, normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3,3, GL_FLOAT, GL_FALSE, sizeof(VertexAttrib), (void*)offsetof(VertexAttrib, color));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(4,2, GL_FLOAT, GL_FALSE, sizeof(VertexAttrib), (void*)offsetof(VertexAttrib, uv));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(5,2, GL_FLOAT, GL_FALSE, sizeof(VertexAttrib), (void*)offsetof(VertexAttrib, uv1s));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(6,2, GL_FLOAT, GL_FALSE, sizeof(VertexAttrib), (void*)offsetof(VertexAttrib, uv2s));
    glEnableVertexAttribArray(6);
    
    BindTexture();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void StaticMesh::BindTexture(){
    for (int i = 0; i < MaxTextureCount; i++) {
        if(mTextures[i])
            mTextures[i]->Init();
    }
}


void StaticMesh::CalculModelMatrix(){
    // 1. 缩放
    lyf::PrintError(lyf::ToString(mModelMatrix));
    mModelMatrix = glm::scale(mModelMatrix, mScale);

    // 2. 旋转（假设 mRotation 是欧拉角，按顺序绕 X, Y, Z 轴旋转）
    mModelMatrix = glm::rotate(mModelMatrix, glm::radians(mRotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // 绕 X 轴旋转
    mModelMatrix = glm::rotate(mModelMatrix, glm::radians(mRotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // 绕 Y 轴旋转
    mModelMatrix = glm::rotate(mModelMatrix, glm::radians(mRotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // 绕 Z 轴旋转

    // 3. 平移
    mModelMatrix = glm::translate(mModelMatrix, mPosition);
}
