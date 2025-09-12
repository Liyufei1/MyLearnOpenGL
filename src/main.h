#pragma once
#include "Common/CommonFunLib.h"
#include "Common/CommonFunLib.hpp"
#include "Common/Config.h"
#include "Window/Window.h"
#include "Mesh/Mesh.h"
#include "Mesh/MeshManager.h"
#include "Texture/Texture2D.h"

#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include <cmath>
#include <functional>
#include <memory>
#include <string>


#include "Test.h"

inline std::shared_ptr<StaticMesh> TestMesh0(){

    std::shared_ptr<StaticMesh> SM = StaticMesh::CreateMesh();

	SM->mMeshBatch.verties = { 	glm::vec3(-0.9f, -0.5f, 0.0f), 
								glm::vec3(-0.0f, -0.5f, 0.0f), 
								glm::vec3(-0.45f, 0.5f, 0.0f),
								glm::vec3(0.9f, -0.5f, 0.0f),
								glm::vec3(0.45f, 0.5f, 0.0f)
	};
	SM->mMeshBatch.indexs = { 0,1,2,1,3,4};
	SM->mMeshBatch.colors = { 
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 1.0f)
	};
	SM->mMeshBatch.uvs = { 
		glm::vec2(-0.9f, -0.5f), 
		glm::vec2(-0.0f, -0.5f), 
		glm::vec2(-0.45f, 0.5f),
		glm::vec2(0.9f, -0.5f),
		glm::vec2(0.45f, 0.5f)
	};

	std::shared_ptr<Texture2D> Texture0{new Texture2D("E:/study/LearnOpenGL/Art/Texture/T_WoodBox.jpg")};
	std::shared_ptr<Texture2D> Texture1{new Texture2D("E:/study/LearnOpenGL/Art/Texture/T_face.png")};
	SM->SetTexture(0,Texture0);
	SM->SetTexture(1,Texture1);
    return SM;
}
inline std::shared_ptr<StaticMesh> BoxMesh(){
	std::shared_ptr<StaticMesh> SM = StaticMesh::CreateMesh();

	SM->mMeshBatch.verties = { 	 
								glm::vec3(-0.5f, 0.5f, -0.5f), //底面
								glm::vec3(0.5f, 0.5f, -0.5f), 
								glm::vec3(0.5f, -0.5f, -0.5f), 
								glm::vec3(-0.5f, -0.5f, -0.5f),

								glm::vec3(-0.5f, -0.5f, -0.5f), //正面
								glm::vec3(0.5f, -0.5f, -0.5f), 
								glm::vec3(0.5f, -0.5f, 0.5f), 
								glm::vec3(-0.5f, -0.5f, 0.5f),
								
								glm::vec3(0.5f, -0.5f, -0.5f), //右面
								glm::vec3(0.5f, 0.5f, -0.5f), 
								glm::vec3(0.5f, 0.5f, 0.5f), 
								glm::vec3(0.5f, -0.5f, 0.5f),

								glm::vec3(0.5f, 0.5f, -0.5f), //后面
								glm::vec3(-0.5f, 0.5f, -0.5f), 
								glm::vec3(-0.5f, 0.5f, 0.5f), 
								glm::vec3(0.5f, 0.5f, 0.5f),

								glm::vec3(-0.5f, 0.5f, -0.5f),//左面
								glm::vec3(-0.5f, -0.5f, -0.5f), 
								glm::vec3(-0.5f, -0.5f, 0.5f), 
								glm::vec3(-0.5f, 0.5f, 0.5f), 

								glm::vec3(-0.5f, -0.5f, 0.5f), //顶面
								glm::vec3(0.5f, -0.5f, 0.5f), 
								glm::vec3(0.5f, 0.5f, 0.5f), 
								glm::vec3(-0.5f, 0.5f, 0.5f),
	};
	SM->mMeshBatch.indexs.clear();
	for (int i = 0; i < 6; i ++) {
		SM->mMeshBatch.indexs.insert(SM->mMeshBatch.indexs.end(),{i * 4 + 0,i * 4 + 1,i * 4 + 2,i * 4 + 2,i * 4 + 3,i * 4 + 0});
	}

	SM->mMeshBatch.colors.clear();
	for (int i = 0; i < 24; i ++) {
		SM->mMeshBatch.colors.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	}

	SM->mMeshBatch.uvs.clear();
	for (int i = 0; i < 6; i ++) {
		SM->mMeshBatch.uvs.push_back(glm::vec2(0.0f, 0.0f));
		SM->mMeshBatch.uvs.push_back(glm::vec2(1.0f, 0.0f));
		SM->mMeshBatch.uvs.push_back(glm::vec2(1.0f, 1.0f));
		SM->mMeshBatch.uvs.push_back(glm::vec2(0.0f, 1.0f));
	}
	
    return SM;
}
