#pragma once

#include <memory>

struct GLFWwindow;

/**
 * @brief ImGui 管理器类，负责 ImGui 的生命周期管理
 *
 * 封装 ImGui 的初始化、渲染和清理逻辑，提供简洁的接口供 Window 类调用
 */
class ImGuiManager
{
private:
    ImGuiManager();
    ~ImGuiManager();

public:
    // 禁止拷贝和赋值
    ImGuiManager(const ImGuiManager&) = delete;
    ImGuiManager& operator=(const ImGuiManager&) = delete;

    /**
     * @brief 获取 ImGuiManager 单例实例
     * @return ImGuiManager& 单例引用
     */
    static ImGuiManager& GetInstance();

    /**
     * @brief 初始化 ImGui
     * @param window GLFW 窗口指针
     * @return true 初始化成功，false 初始化失败
     */
    bool Init(GLFWwindow* window);

    /**
     * @brief 开始新的一帧
     */
    void NewFrame();

    /**
     * @brief 渲染 ImGui 绘制命令
     */
    void Render();

    /**
     * @brief 清理 ImGui 资源
     */
    void Shutdown();

private:
    bool mIsInitialized;  // 是否已初始化
};