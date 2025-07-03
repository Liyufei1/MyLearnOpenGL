#include "Mesh.h"
#include "Common/CommonFunLib.h"
#include "glm/gtc/matrix_transform.hpp"




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
void StaticMesh::BindGlVertexAttribPointer(GLuint VAO ,GLuint VBO) const{

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
