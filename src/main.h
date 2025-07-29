#pragma once
#include "Common/CommonFunLib.h"
#include "Common/CommonFunLib.hpp"
#include "Common/Config.h"
#include "Window/Window.h"
#include "Mesh/Mesh.h"
#include "Mesh/MeshManager.h"
#include "Texture/Texture2D.h"
#include "Camera/Camera.h"


#include "glfw/glfw3.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include <cmath>
#include <functional>
#include <memory>
#include <string>

#include "Test.h"

std::shared_ptr<StaticMesh> TestMesh0();
// std::shared_ptr<StaticMesh> BoxMesh();

int main()
{
	Window& window {Window::GetInstance()};

	TestFun();

	Camera camera;

	std::shared_ptr<StaticMesh> SM = TestMesh0();
	SM->SetLocation(glm::vec3(0.5,0,0));
	SM->SetScale(glm::vec3(0.5,0.5,0.5));

	// std::shared_ptr<StaticMesh> SM1 = BoxMesh();
	// SM1->SetLocation(glm::vec3(-0.5,0,0));
	// SM1->SetScale(glm::vec3(0.5,0.5,0.5));


	MeshManager::GetInstance().BindData();



	window.SetRunFunction([&](){
		glClearColor(0.9f,0.9f,0.8f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
		
		SM->SetRotation(glm::vec3{0.0f,0.0f,90 * std::fmod(glfwGetTime(),4)});
		SM->GetShaderProgram().SetParamater<float>("Test", (sin(glfwGetTime())));
		SM->GetShaderProgram().SetParamater<glm::mat4>("uModelMatrix", SM->GetModelMatrix());
		// SM->GetShaderProgram().SetParamater<glm::mat4>("uViewProjectionMatrix", camera.GetViewProjectionMMatrix());
		// LOG(LOGTEMP,lyf::ToString(SM->GetModelMatrix()));
		MeshManager::GetInstance().Render();
	});
	window.Run();
	


	window.Close();	
	return 0;
}
