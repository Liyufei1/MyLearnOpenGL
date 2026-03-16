#include "MeshLib.h"
#include "Common/CommonFunLib.hpp"
#include "Render/Texture/Texture2D.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "color4.h"


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
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
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


std::shared_ptr<StaticMesh> PlaneMesh(){
    std::shared_ptr<StaticMesh> SM = StaticMesh::CreateMesh();

	SM->mMeshBatch.verties = { 	glm::vec3(-1.0f, -1.0f, 0.0f), 
								glm::vec3(1.0f, -1.0f, 0.0f), 
								glm::vec3(1.0f, 1.0f, 0.0f),
								glm::vec3(-1.0f, 1.0f, 0.0f)
	};
	SM->mMeshBatch.indexs = { 0,1,2,2,3,0};
	SM->mMeshBatch.normals = { 
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	};
	SM->mMeshBatch.colors = { 
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 0.0f)
	};
	SM->mMeshBatch.uvs = { 
		glm::vec2(0.0f, 0.0f), 
		glm::vec2(1.0f, 0.0f), 
		glm::vec2(1.0f, 1.0f), 
		glm::vec2(0.0f, 1.0f)
	};
    return SM;
}


std::shared_ptr<StaticMesh> ArrowMesh(){
	std::shared_ptr<StaticMesh> SM = StaticMesh::CreateMesh();

	return SM;
}


void processMesh(aiMesh *mesh, const aiScene *scene,std::shared_ptr<StaticMesh> SM){ 
	int index = SM->mMeshBatch.verties.size();

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        aiVector3D vertex = mesh->mVertices[i];
		SM->mMeshBatch.verties.push_back(glm::vec3(vertex.x, vertex.y, vertex.z));
		if (mesh->HasNormals()) {
			aiVector3D normal = mesh->mNormals[i];
			SM->mMeshBatch.normals.push_back(glm::vec3(normal.x, normal.y, normal.z));
		}

		if (mesh->HasTextureCoords(0)) {
        	aiVector3D  uv = mesh->mTextureCoords[0][i];
        	// aiVector3D  tangent = mesh->mTangents[i];
			SM->mMeshBatch.uvs.push_back(glm::vec2(uv.x, uv.y));
			// SM->mMeshBatch.tangents.push_back(glm::vec3(tangent.x,tangent.y,tangent.z));
		}else {
			SM->mMeshBatch.uvs.push_back(glm::vec2(0, 0));
		}

    }

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            SM->mMeshBatch.indexs.push_back(face.mIndices[j]+index);
        }
    }


}

void processNode(aiNode *node, const aiScene *scene,std::shared_ptr<StaticMesh> SM){
	for(unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
		processMesh(mesh, scene,SM);         
		// LOG(LOGTEMP,"mesh====================",i)
	}
	// 接下来对它的子节点重复这一过程
	for(unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene,SM);
		// LOG(LOGTEMP,"node====================",i)

	}
}
std::shared_ptr<StaticMesh> ModelMesh(){
	std::shared_ptr<StaticMesh> SM = StaticMesh::CreateMesh();
	
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile("Art/SM/backpack/backpack.obj", aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		LOG(LOGERROR,"ASSIMP :: LOAD FAILED , Art/SM/backpack/backpack.obj")
		LOG(LOGERROR,"ASSIMP :: LOAD FAILED :",importer.GetErrorString())
		return SM;
	}
	processNode(scene->mRootNode,scene,SM);

	return SM;
}
