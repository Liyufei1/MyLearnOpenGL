#include "MeshLib.h"
#include "Texture/Texture2D.h"


std::shared_ptr<StaticMesh> TestMesh0(){

    std::shared_ptr<StaticMesh> SM = StaticMesh::CreateMesh();

	SM->mMeshBatch.verties = { 	glm::vec3(-0.9f, -0.5f, 0.0f), 
								glm::vec3(-0.0f, -0.5f, 0.0f), 
								glm::vec3(-0.45f, 0.5f, 0.0f),
								glm::vec3(0.9f, -0.5f, 0.0f),
								glm::vec3(0.45f, 0.5f, 0.0f)
	};
	SM->mMeshBatch.indexs = { 0,1,2,1,3,4};
	SM->mMeshBatch.normals = { 
		glm::vec3(1.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 0.0f, 1.0f),
	};
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
std::shared_ptr<StaticMesh> BoxMesh(){
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
		SM->mMeshBatch.colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	}

	SM->mMeshBatch.uvs.clear();
	for (int i = 0; i < 6; i ++) {
		SM->mMeshBatch.uvs.push_back(glm::vec2(0.0f, 0.0f));
		SM->mMeshBatch.uvs.push_back(glm::vec2(1.0f, 0.0f));
		SM->mMeshBatch.uvs.push_back(glm::vec2(1.0f, 1.0f));
		SM->mMeshBatch.uvs.push_back(glm::vec2(0.0f, 1.0f));
	}

	SM->mMeshBatch.normals.clear();
	SM->mMeshBatch.normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	SM->mMeshBatch.normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	SM->mMeshBatch.normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	SM->mMeshBatch.normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));

	SM->mMeshBatch.normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	SM->mMeshBatch.normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	SM->mMeshBatch.normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	SM->mMeshBatch.normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));

	SM->mMeshBatch.normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	SM->mMeshBatch.normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	SM->mMeshBatch.normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	SM->mMeshBatch.normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	
	SM->mMeshBatch.normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	SM->mMeshBatch.normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	SM->mMeshBatch.normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	SM->mMeshBatch.normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	
	SM->mMeshBatch.normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	SM->mMeshBatch.normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	SM->mMeshBatch.normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	SM->mMeshBatch.normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	
	SM->mMeshBatch.normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	SM->mMeshBatch.normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	SM->mMeshBatch.normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	SM->mMeshBatch.normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));

	
    return SM;
}
