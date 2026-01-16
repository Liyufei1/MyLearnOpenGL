#include "ImGuiManager.h"
#include "Common/CommonFunLib.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>

ImGuiManager::ImGuiManager()
    : mIsInitialized(false)
{
}

ImGuiManager::~ImGuiManager()
{
    if (mIsInitialized)
    {
        Shutdown();
    }
}

ImGuiManager& ImGuiManager::GetInstance()
{
    static ImGuiManager instance;
    return instance;
}

bool ImGuiManager::Init(GLFWwindow* window)
{
    LOG(LOGTEMP, "====================== ImGuiManager::Init :: Begin ======================");

    // check
    if (mIsInitialized) return true;
    if (!window){
        LOG(LOGERROR, "ImGuiManager::Init - Window pointer is null");
        return false;
    }

    // 1. 创建 ImGui 上下文
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // 启用键盘导航

    // 2. 设置样式
    ImGui::StyleColorsDark();

    // 3. 初始化平台/渲染后端
    if (!ImGui_ImplGlfw_InitForOpenGL(window, true))
    {
        LOG(LOGERROR, "ImGuiManager::Init - Failed to initialize GLFW backend");
        ImGui::DestroyContext();
        return false;
    }

    if (!ImGui_ImplOpenGL3_Init("#version 330"))
    {
        LOG(LOGERROR, "ImGuiManager::Init - Failed to initialize OpenGL3 backend");
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        return false;
    }

    mIsInitialized = true;
    LOG(LOGTEMP, "ImGuiManager initialized successfully");
    LOG(LOGTEMP, "====================== ImGuiManager::Init :: End ======================");
    return true;
}

void ImGuiManager::NewFrame()
{
    if (!mIsInitialized){
        return;
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiManager::Render()
{
    if (!mIsInitialized)
    {
        return;
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiManager::Shutdown()
{
    if (!mIsInitialized)
    {
        return;
    }

    // 清理后端
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    // 清理上下文
    ImGui::DestroyContext();

    mIsInitialized = false;
}