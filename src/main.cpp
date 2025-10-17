#include "main.h"

#include "Common/CommonFunLib.hpp"
#include "Light/Light.h"
#include "Mesh/RenderManager.h"
#include "Shader/Material.h"
#include "Shader/ShaderProgram.h"
#include "glfw/glfw3.h"
#include "glm/ext/vector_float3.hpp"
#include <array>
#include <cmath>
#include <cstdlib>
#include <memory>
#include <vector>
#include "Mesh/MeshLib.h"
#include "Camera/Camera.h"

#include <random>



Main& Main::GetInstance(){
	static  Main s_Instance ;
	return s_Instance;
}

void Main::LoadUsedResources(){

	//加载的贴图
	T_WoodBox = std::shared_ptr<Texture2D>{new Texture2D("E:/study/LearnOpenGL/Art/Texture/T_WoodBox.jpg")};
	T_WoodBox2 = std::shared_ptr<Texture2D>{new Texture2D("E:/study/LearnOpenGL/Art/Texture/container2.png")};
	T_WoodBox2_Spacular  = std::shared_ptr<Texture2D>{new Texture2D("E:/study/LearnOpenGL/Art/Texture/container2_specular.png")};
	T_SmallFace = std::shared_ptr<Texture2D>{new Texture2D("E:/study/LearnOpenGL/Art/Texture/T_face.png")};

	//着色器程序
	PhoneShaderPrograme = std::make_shared<ShaderProgram>("src/Shader/PhoneShader/PhoneVertex.glsl","src/Shader/PhoneShader/PhoneFragment.glsl");
	BaseShaderPrograme = ShaderProgram::GetDefaultShaderProgram();
	RenderManager::GetInstance().AddShaderProgram(BaseShaderPrograme);
	RenderManager::GetInstance().AddShaderProgram(PhoneShaderPrograme);


	//材质
	M_Base = Material::GetDefaultMaterial();
	
	M_Phone = std::make_shared<PhoneMaterial>();
	M_Phone->SetShaderPrograrm(PhoneShaderPrograme);
	M_Phone->SetDiffuseTexture(T_WoodBox2);
	M_Phone->SetSpecularTexture(T_WoodBox2_Spacular);
	M_Phone->SetShininess(8);
}


void Main::InitMesh(){

}

void Main::InitLight(){
	RenderManager::GetInstance().AddLight(&L_DirLight);
	L_DirLight.SetDirection(glm::vec3(0.0f, 0.0f, -1.0f));
	L_DirLight.SetInstensity(0.1f);
	
	
	RenderManager::GetInstance().AddLight(&PointLight1);
	PointLight1.SetIndex(0);
	PointLight1.SetLocation(glm::vec3(2.0 * sin(0), 2.0*cos(0), 1.0f));
	// PointLight1.SetLinear(0.09);
	// PointLight1.SetQuadratic(0.0032);

	RenderManager::GetInstance().AddLight(&PointLight2);
	PointLight2.SetIndex(1);
	PointLight2.SetLocation(glm::vec3(2.0 * sin(0), 2.0*cos(0), 1.0f));
	// PointLight2.SetLinear(0.09);
	// PointLight2.SetQuadratic(0.0032);

	AddUpdateFunction([this](){
		PointLight1.SetLocation(glm::vec3(2.0 * sin(glfwGetTime()), 2.0*cos(glfwGetTime()), 1.0f));
		PointLight2.SetLocation(glm::vec3(1.0 * sin(glfwGetTime()*1.1+3.1415), 2.0*cos(glfwGetTime()*1.1+3.1415), 0.5f));
	});
	
}

int main()
{
	Window& window {Window::GetInstance()};
	Main& main = Main::GetInstance();
	main.LoadUsedResources();
	main.InitLight();

	TestFun();
	

	std::random_device rd;      
    std::mt19937 gen(rd());     
    std::uniform_real_distribution<double> dist(0.0, 1.0);

	std::vector<std::shared_ptr<StaticMesh>> SMArray;
	for(int i = 0; i < 10; i++){
		std::shared_ptr<StaticMesh> Temp = BoxMesh();
		Temp->SetMaterial(main.M_Phone);
		Temp->SetLocation(glm::vec3(dist(gen)*5 - 2.5,dist(gen)*5 - 2.5,dist(gen)*5 - 2.5));
		Temp->SetScale(glm::vec3(dist(gen)));
		Temp->SetRotation(glm::vec3(dist(gen) * 180,dist(gen) * 90,dist(gen) * 360));
		SMArray.push_back(Temp);
	}
	

	std::shared_ptr<StaticMesh> SM = TestMesh0();
	SM->SetMaterial(main.M_Phone);
	SM->SetLocation(glm::vec3(0.5,0,0));
	SM->SetScale(glm::vec3(0.5,0.5,0.5));


	std::shared_ptr<StaticMesh> SM1 = TestMesh0();
	SM1->SetLocation(glm::vec3(-0.5,0,-0.9f));
	SM1->SetScale(glm::vec3(0.5,0.5,0.5));

	std::shared_ptr<StaticMesh> SM2 = BoxMesh();
	SM2->SetMaterial(main.M_Phone);
	SM2->SetLocation(glm::vec3(-0.0f,0,-1.5f));
	SM2->SetScale(glm::vec3(0.5,0.5,0.5));


	std::shared_ptr<StaticMesh> SM3 = PlaneMesh();
	SM3->SetMaterial(main.M_Phone);
	SM3->SetLocation(glm::vec3(0.0f,0.0f,-2.0f));
	SM3->SetScale(glm::vec3(2.5,2.5,2.5));


	RenderManager::GetInstance().BindData();


	

	window.SetRunFunction([&](){
		glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		main.Update();

		
		SM->SetRotation(glm::vec3{0.0f,0.0f,90 * std::fmod(glfwGetTime(),4)});
		SM->GetMaterial()->GetShaderProgram()->SetParamater<float>("Test", (sin(glfwGetTime())));


		RenderManager::GetInstance().Render();
	});
	window.Run();
	


	window.Close();	
	return 0;
}