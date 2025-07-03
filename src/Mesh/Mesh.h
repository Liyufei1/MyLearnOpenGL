#pragma once
#include "glm/ext/vector_float3.hpp"
#include "glm/glm.hpp"
#include <vector>
#include "glad/glad.h"

struct VertexAttrib{
    glm::vec3 vertex{ 0.0f,0.0f,0.0f };
    glm::vec3 tangent{ 0.0f,0.0f,0.0f };
    glm::vec3 normal{ 0.0f,0.0f,0.0f };
    glm::vec3 color{ 0.0f,0.0f,0.0f };
    glm::vec2 uv{ 0.0f,0.0f};
    glm::vec2 uv1s{ 0.0f,0.0f};
    glm::vec2 uv2s{ 0.0f,0.0f};
};

struct MeshBatch {
public:
    // 顶点属性
    std::vector<glm::vec3> verties;  // 顶点位置./
    std::vector<glm::vec3> tangents;   // 切线
    std::vector<glm::vec3> normals;    // 法线
    std::vector<glm::vec3> colors;     // 颜色
    std::vector<glm::vec2> uvs;        // 纹理坐标0
    std::vector<glm::vec2> uvs1;        // 纹理坐标1
    std::vector<glm::vec2> uvs2;        // 纹理坐标2

    std::vector<VertexAttrib> GetData() const;
};

class StaticMesh{
public:
    StaticMesh(){}
    ~StaticMesh(){}
private:
    void BindGlVertexAttribPointer(GLuint VAO ,GLuint VBO) const;
    void CalculModelMatrix();
    MeshBatch mMeshBatch;
    glm::vec3 mPosition{};
    glm::vec3 mScale{};
    glm::vec3 mRotation{};
    glm::mat4 mModelMatrix{1.0f};
};