#pragma once
#include "glm/ext/vector_float3.hpp"
#include "glm/fwd.hpp"
#include <cstddef>
#include <memory>
#include <vector>

#include "glad/glad.h"

#include "RenderManager.h"
#include "Shader/Material.h"



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
    std::vector<glm::vec3> verties;  // 顶点位置
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
    friend class RenderManager;
    static const int MaxTextureCount = 16;
public:
    ~StaticMesh();
    static std::shared_ptr<StaticMesh> CreateMesh(){
        std::shared_ptr<StaticMesh> mesh(new StaticMesh);
        mesh->SetMaterial(Material::GetDefaultMaterial());
        RenderManager::GetInstance().AddMesh(mesh);
        return mesh;
    }
    
    std::shared_ptr<Material> GetMaterial(){  return mMaterial; }

    glm::mat4 GetModelMatrix();
    glm::vec3 GetLocation(){return mPosition;}
    glm::vec3 GetRotation(){return mRotation;}
    glm::vec3 GetScale(){return mScale;}
    void SetMaterial(std::shared_ptr<Material> pSP){ mMaterial = pSP; }
    void SetLocation(glm::vec3 location){mPosition = location; bIsTransformDirty = true;}
    void SetRotation(glm::vec3 rotation){mRotation = rotation; bIsTransformDirty = true;}
    void SetScale(glm::vec3 scale){mScale = scale; bIsTransformDirty = true;}

    MeshBatch mMeshBatch;
private:
    StaticMesh(){}

    void Draw();

    void BindGlVertexAttribPointer();

    void CalculModelMatrix();

    std::shared_ptr<Material> mMaterial = nullptr;

    glm::vec3 mPosition{0.0f,0.0f,0.0f};
    glm::vec3 mScale{1.0f,1.0f,1.0f};
    glm::vec3 mRotation{0.0f,0.0f,0.0f};
    glm::mat4 mModelMatrix{1.0f};
    bool bIsTransformDirty = true;

    GLuint mVAO = 0;
    GLuint mVBO = 0;
    GLuint mEBO = 0;
    
};

