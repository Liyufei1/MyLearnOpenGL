#include "main.h"

#include "Shader/ShaderProgram.h"
#include "glfw/glfw3.h"
#include "glm/ext/vector_float3.hpp"
#include <cmath>
#include <memory>
#include "Mesh/MeshLib.h"
#include "Camera/Camera.h"


int main()
{
	Window& window {Window::GetInstance()};
	TestFun();

	//加载的贴图
	std::shared_ptr<Texture2D> texture0{new Texture2D("E:/study/LearnOpenGL/Art/Texture/T_WoodBox.jpg")};
	std::shared_ptr<Texture2D> texture1{new Texture2D("E:/study/LearnOpenGL/Art/Texture/T_face.png")};

	//着色器程序
	std::shared_ptr<ShaderProgram> PhoneShaderPrograme = std::make_shared<ShaderProgram>("src/Shader/PhoneShader/PhoneVertex.glsl","src/Shader/PhoneShader/PhoneFragment.glsl");
	std::shared_ptr<ShaderProgram> BaseShaderPrograme = ShaderProgram::GetDefaultShaderProgram();
	PhoneShaderPrograme->SetParamater("uLightColor", glm::vec3(1,1,1));
	PhoneShaderPrograme->SetParamater("uLightPos", glm::vec3(0,0,5));

	//Light光照
	Light Light1;
	std::shared_ptr<StaticMesh> SMLight1 = BoxMesh();
	double lightR1 = 2.0f;
	Light1.SetLightColor(glm::vec3(1.0f, 1.0f, 1.0f));
	Light1.SetLightPosition(glm::vec3(lightR1 * sin(0), lightR1*cos(0), 1.0f));
	Light1.AddShaderProgram(PhoneShaderPrograme);
	SMLight1->SetLocation(Light1.GetLightPosition());
	SMLight1->SetShaderProgram(BaseShaderPrograme);
	SMLight1->SetScale(glm::vec3(0.1f, 0.1f, 0.1f));

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
	SM1->GetShaderProgram()->SetParamater("uBaseColor", glm::vec4(0.8,0.8,0.8,1));

	std::shared_ptr<StaticMesh> SM2 = BoxMesh();
	SM2->SetShaderProgram(PhoneShaderPrograme);
	SM2->SetLocation(glm::vec3(-0.0f,0,-1.5f));
	SM2->SetScale(glm::vec3(0.5,0.5,0.5));
	SM2->SetTexture(0,texture0);
	SM2->SetTexture(1,texture1);

	std::shared_ptr<StaticMesh> SM3 = PlaneMesh();
	SM3->SetShaderProgram(PhoneShaderPrograme);
	SM3->SetLocation(glm::vec3(0.0f,0.0f,-0.5f));
	SM3->SetScale(glm::vec3(2.5,2.5,2.5));


	MeshManager::GetInstance().BindData();


	

	window.SetRunFunction([&](){
		glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Light1.SetLightPosition(glm::vec3(lightR1 * sin(glfwGetTime()), lightR1*cos(glfwGetTime()), 1.0f));
		SMLight1->SetLocation(Light1.GetLightPosition());
		Light1.UpdateLight();
		
		SM->SetRotation(glm::vec3{0.0f,0.0f,90 * std::fmod(glfwGetTime(),4)});
		SM->GetShaderProgram()->SetParamater<float>("Test", (sin(glfwGetTime())));


		// LOG(LOGTEMP,lyf::ToString(SM->GetModelMatrix()));
		MeshManager::GetInstance().Render();
	});
	window.Run();
	


	window.Close();	
	return 0;
}