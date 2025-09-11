#include "main.h"
#include "Shader/ShaderProgram.h"
#include <memory>



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


int main()
{
	Window& window {Window::GetInstance()};

	//加载的贴图
	std::shared_ptr<Texture2D> texture0{new Texture2D("E:/study/LearnOpenGL/Art/Texture/T_WoodBox.jpg")};
	std::shared_ptr<Texture2D> texture1{new Texture2D("E:/study/LearnOpenGL/Art/Texture/T_face.png")};

	//着色器程序
	std::shared_ptr<ShaderProgram> PhoneShaderPrograme = std::make_shared<ShaderProgram>("src/Shader/PhoneShader/PhoneVertex.glsl","src/Shader/PhoneShader/PhoneFragment.glsl");
	std::shared_ptr<ShaderProgram> BaseShaderPrograme = ShaderProgram::GetDefaultShaderProgram();
	TestFun();

	// Camera camera;

	std::shared_ptr<StaticMesh> SM = TestMesh0();
	SM->SetShaderProgram(PhoneShaderPrograme);
	SM->SetLocation(glm::vec3(0.5,0,0));
	SM->SetScale(glm::vec3(0.5,0.5,0.5));
	SM->SetTexture(0,texture0);
	SM->SetTexture(1,texture1);

	std::shared_ptr<StaticMesh> SM1 = TestMesh0();
	// SM1->SetShaderProgram(BaseShaderPrograme);
	SM1->SetLocation(glm::vec3(-0.5,0,-0.9f));
	SM1->SetScale(glm::vec3(0.5,0.5,0.5));

	std::shared_ptr<StaticMesh> SM2 = BoxMesh();
	SM2->SetShaderProgram(PhoneShaderPrograme);
	SM2->SetLocation(glm::vec3(-0.0f,0,-1.5f));
	SM2->SetScale(glm::vec3(0.5,0.5,0.5));
	SM2->SetTexture(0,texture0);
	SM2->SetTexture(1,texture1);


	MeshManager::GetInstance().BindData();


	

	window.SetRunFunction([&](){
		glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		SM->SetRotation(glm::vec3{0.0f,0.0f,90 * std::fmod(glfwGetTime(),4)});
		SM->GetShaderProgram()->SetParamater<float>("Test", (sin(glfwGetTime())));


		// LOG(LOGTEMP,lyf::ToString(SM->GetModelMatrix()));
		MeshManager::GetInstance().Render();
	});
	window.Run();
	


	window.Close();	
	return 0;
}