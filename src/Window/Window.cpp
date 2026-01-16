#include "glad/glad.h"
#include "Window.h"
#include "Common/CommonFunLib.h"
#include "InputEvent.h"
#include "ImGuiManager.h"
#include "glfw/glfw3.h"

void Window::Init(){
    LOG(LOGTEMP, "Window::Init -========================================= ");

    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
    mWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, mTitle.c_str(), NULL, NULL);

	if (mWindow == NULL)
	{
        LOG(LOGERROR,"Failed to create GLFW window");
		glfwTerminate();
		return;
	}

    glfwMakeContextCurrent(mWindow);
	glfwSetFramebufferSizeCallback(mWindow, [](GLFWwindow *window, int width, int height){
        glViewport(0, 0, width, height);
    });

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
        LOG(LOGERROR, "Failed to initialize GLAD");
		return;
	}

	
	glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
	glfwSetCursorPosCallback(mWindow,Input::MouseEvents);
	glfwSetScrollCallback(mWindow, Input::ScrollEvents);
	
	//depth test
	glEnable(GL_DEPTH_TEST);

    LOG(LOGTEMP, "Window::InitImGui - mWindow pointer 1 : ", (long long)mWindow);

    InitImGui();
}

void Window::Run(){
    if(!mRunFunction){
        LOG(LOGERROR,"Run function is not set");
        return;
    }
    while (!glfwWindowShouldClose(mWindow))
	{
		Input::InputEvents(mWindow);

        // ImGui 新帧
        if (mImGuiInitialized)
        {
            ImGuiManager::GetInstance().NewFrame();
        }

        mRunFunction();

        // ImGui 渲染
        if (mImGuiInitialized)
        {
            ImGuiManager::GetInstance().Render();
        }

		glfwSwapBuffers(mWindow);
		glfwPollEvents();
	}
}

void Window::Close(){
    // 清理 ImGui
    if (mImGuiInitialized)
    {
        ImGuiManager::GetInstance().Shutdown();
        mImGuiInitialized = false;
    }

    glfwTerminate();
}



void Window::SetRunFunction(std::function<void()> InFunction){
    mRunFunction = InFunction;
}

bool Window::InitImGui()
{
    if (mImGuiInitialized) {
        return true;
    }

    LOG(LOGTEMP, "Window::InitImGui - mWindow pointer 2 : ", (long long)mWindow);

    if (ImGuiManager::GetInstance().Init(mWindow)) {
        mImGuiInitialized = true;
        LOG(LOGTEMP, "ImGui initialized successfully");
        return true;
    } else {
        LOG(LOGERROR, "Failed to initialize ImGui");
        return false;
    }
}

void Window::ShutdownImGui()
{
    if (mImGuiInitialized)
    {
        ImGuiManager::GetInstance().Shutdown();
        mImGuiInitialized = false;
        LOG(LOGTEMP, "ImGui shutdown");
    }
}

void Window::SetCursorMode(bool enabled)
{
    mCursorMode = enabled;
    if (enabled) {
        glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    } else {
        glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}