#pragma once
#include "glm/ext/vector_float3.hpp"
#include "glm/fwd.hpp"
#include <cstddef>
#include <memory>
#include <vector>
#include "glad/glad.h"

#include "MeshManager.h"
#include "Shader/ShaderProgram.h"



class Texture2D;

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

    std::vector<glm::int32>indexs;  //顶点索引

public:
    std::vector<VertexAttrib> GetData() const;
};


class StaticMesh : public std::enable_shared_from_this<StaticMesh>
{
    friend class MeshManager;
    static const int MaxTextureCount = 16;
public:
    ~StaticMesh();
    static std::shared_ptr<StaticMesh> CreateMesh(){
        std::shared_ptr<StaticMesh> mesh(new StaticMesh);
        MeshManager::GetInstance().AddMesh(mesh);
        return mesh;
    }
    ShaderProgram& GetShaderProgram(){  return mShaderProgram; }

    void SetTexture(int index, std::shared_ptr<Texture2D> texture);

    MeshBatch mMeshBatch;
private:
    StaticMesh(){
        mTextures.resize(MaxTextureCount,nullptr);
    }

    void Draw();

    void BindGlVertexAttribPointer();

    void BindTexture();

    void CalculModelMatrix();


    ShaderProgram mShaderProgram{"src/Shader/PhoneShader/PhoneVertex.glsl",
						"src/Shader/PhoneShader/PhoneFragment.glsl"};

    glm::vec3 mPosition{};
    glm::vec3 mScale{};
    glm::vec3 mRotation{};
    glm::mat4 mModelMatrix{1.0f};

    GLuint mVAO = 0;
    GLuint mVBO = 0;
    GLuint mEBO = 0;
    
    std::vector<std::shared_ptr<Texture2D>> mTextures;
};