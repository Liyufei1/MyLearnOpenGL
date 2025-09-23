#include "main.h"

#include "Shader/ShaderProgram.h"
#include "glfw/glfw3.h"
#include "glm/ext/vector_float3.hpp"
#include <cmath>
#include <memory>
#include "Mesh/MeshLib.h"
#include "Camera/Camera.h"



Main& Main::GetInstance(){
	static  Main s_Instance ;
	return s_Instance;
}

void Main::LoadUsedResources(){

	//加载的贴图
	T_WoodBox = std::shared_ptr<Texture2D>{new Texture2D("E:/study/LearnOpenGL/Art/Texture/T_WoodBox.jpg")};
	T_SmallFace = std::shared_ptr<Texture2D>{new Texture2D("E:/study/LearnOpenGL/Art/Texture/T_face.png")};

	//着色器程序
	PhoneShaderPrograme = std::make_shared<ShaderProgram>("src/Shader/PhoneShader/PhoneVertex.glsl","src/Shader/PhoneShader/PhoneFragment.glsl");
	BaseShaderPrograme = ShaderProgram::GetDefaultShaderProgram();
}


void Main::InitMesh(){

}

void Main::InitLight(){
	
	PointLight1.SetDiffuse(glm::vec3(1.0f, 1.0f, 1.0f));
	PointLight1.SetPosition(glm::vec3(2.0 * sin(0), 2.0*cos(0), 1.0f));
	PointLight1.AddShaderProgram(PhoneShaderPrograme);
	SM_PointLight1 = BoxMesh();
	SM_PointLight1->SetLocation(PointLight1.GetLightPosition());
	SM_PointLight1->SetShaderProgram(BaseShaderPrograme);
	SM_PointLight1->SetScale(glm::vec3(0.1f, 0.1f, 0.1f));

	AddUpdateFunction([this](){
		PointLight1.SetPosition(glm::vec3(2.0 * sin(glfwGetTime()), 2.0*cos(glfwGetTime()), 1.0f));
		SM_PointLight1->SetLocation(PointLight1.GetLightPosition());
		PointLight1.UpdateLight();
	});
	
}

int main()
{
	Window& window {Window::GetInstance()};
	Main& main = Main::GetInstance();
	main.LoadUsedResources();

	main.InitLight();

	TestFun();



	

	std::shared_ptr<StaticMesh> SM = TestMesh0();
	SM->SetShaderProgram(main.PhoneShaderPrograme);
	SM->SetLocation(glm::vec3(0.5,0,0));
	SM->SetScale(glm::vec3(0.5,0.5,0.5));
	SM->SetTexture(0,main.T_WoodBox);
	SM->SetTexture(1,main.T_SmallFace);

	std::shared_ptr<StaticMesh> SM1 = TestMesh0();
	// SM1->SetShaderProgram(BaseShaderPrograme);
	SM1->SetLocation(glm::vec3(-0.5,0,-0.9f));
	SM1->SetScale(glm::vec3(0.5,0.5,0.5));
	SM1->GetShaderProgram()->SetParamater("uBaseColor", glm::vec4(0.8,0.8,0.8,1));

	std::shared_ptr<StaticMesh> SM2 = BoxMesh();
	SM2->SetShaderProgram(main.PhoneShaderPrograme);
	SM2->SetLocation(glm::vec3(-0.0f,0,-1.5f));
	SM2->SetScale(glm::vec3(0.5,0.5,0.5));
	SM2->SetTexture(0,main.T_WoodBox);
	SM2->SetTexture(1,main.T_SmallFace);

	std::shared_ptr<StaticMesh> SM3 = PlaneMesh();
	SM3->SetShaderProgram(main.PhoneShaderPrograme);
	SM3->SetLocation(glm::vec3(0.0f,0.0f,-2.0f));
	SM3->SetScale(glm::vec3(2.5,2.5,2.5));


	MeshManager::GetInstance().BindData();


	

	window.SetRunFunction([&](){
		glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		main.Update();

		
		
		SM->SetRotation(glm::vec3{0.0f,0.0f,90 * std::fmod(glfwGetTime(),4)});
		SM->GetShaderProgram()->SetParamater<float>("Test", (sin(glfwGetTime())));


		// LOG(LOGTEMP,lyf::ToString(SM->GetModelMatrix()));
		MeshManager::GetInstance().Render();
	});
	window.Run();
	


	window.Close();	
	return 0;
}