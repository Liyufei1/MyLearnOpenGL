#pragma once

#include "Common/CommonFunLib.hpp"
#include "glfw/glfw3.h"
#include <string>
#include <functional>
#include "Common/Config.h"
#include <map>
#include <vector>


class Window
{
public:
    static Window& GetInstance(){
        static Window instance{SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL"};
        static bool bIsWindowInit = false;
        if (!bIsWindowInit) {
            LOG(LOGTEMP,"Window :: Init ");
            instance.Init();
            bIsWindowInit = true;
        }
        return instance;
    }
    Window(const Window& Other) = delete;
    Window operator=(const Window& Other) = delete;
    
    ~Window(){}
    void Run();
    void Close();
    void SetRunFunction(std::function<void()> InFunction);
    GLFWwindow* GetWindow() const{ return mWindow; }

    // ImGui 相关方法
    bool InitImGui();
    void ShutdownImGui();
    bool IsImGuiInitialized() const { return mImGuiInitialized; }

    // 鼠标输入模式控制
    bool GetCursorMode() const { return mCursorMode; }
    void SetCursorMode(bool enabled);
private:
    Window(int width, int height, const std::string& title)
    :SCR_WIDTH(width),SCR_HEIGHT(height),mTitle(title)
    {}

    void Init();

    GLFWwindow* mWindow = nullptr;
    int SCR_WIDTH = 1920;
    int SCR_HEIGHT = 1080;
    std::string mTitle = "OpenGL";
    std::function<void()> mRunFunction;
    bool mImGuiInitialized = false;
    bool mCursorMode = false;
};

