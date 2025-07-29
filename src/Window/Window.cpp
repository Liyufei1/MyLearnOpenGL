#include "Window.h"
#include "Common/CommonFunLib.h"
#include "InputEvent.h"

void Window::Init(){
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
	
	//depth test
	glEnable(GL_DEPTH_TEST);
}

void Window::Run(){
    if(!mRunFunction){
        LOG(LOGERROR,"Run function is not set");
        return;
    }
    while (!glfwWindowShouldClose(mWindow))
	{
		Input::InputEvents(mWindow);

        mRunFunction();

		glfwSwapBuffers(mWindow);
		glfwPollEvents();
	}
}

void Window::Close(){
    glfwTerminate();
}



void Window::SetRunFunction(std::function<void()> InFunction){
    mRunFunction = InFunction;
}