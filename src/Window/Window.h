#pragma once

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include <string>
#include <functional>

class Window
{
public:
    Window(){}
    Window(int width, int height, const std::string& title)
    :SCR_WIDTH(width),SCR_HEIGHT(height),mTitle(title)
    {}
    ~Window(){}
    void Init();
    void Run();
    void Close();
    void SetRunFunction(std::function<void()> InFunction);
private:
    void processInput(GLFWwindow *window);

    GLFWwindow* mWindow = nullptr;
    int SCR_WIDTH = 1920;
    int SCR_HEIGHT = 1080;
    std::string mTitle = "OpenGL";
    std::function<void()> mRunFunction;

};