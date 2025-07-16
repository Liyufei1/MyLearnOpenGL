#include "main.h"


std::shared_ptr<StaticMesh> TestMesh0(){
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