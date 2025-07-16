#pragma once
#include "Common/CommonFunLib.h"
#include "Window/Window.h"
#include "Mesh/Mesh.h"
#include "Mesh/MeshManager.h"
#include "Texture/Texture2D.h"
#include "glfw/glfw3.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include <memory>
#include <string>

#include "Test.h"

std::shared_ptr<StaticMesh> TestMesh0();
int main()
{
	Window window(1920, 1080, "OpenGL");
	window.Init();

	TestFun();

	std::shared_ptr<StaticMesh> SM = TestMesh0();
	

	MeshManager::GetInstance().BindData();
	window.SetRunFunction([&](){
		glClearColor(0.9f,0.9f,0.8f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
		SM->GetShaderProgram().SetParamater<float>("Test", (sin(glfwGetTime())));
		MeshManager::GetInstance().Render();
	});
	window.Run();


	window.Close();	
	return 0;
}
