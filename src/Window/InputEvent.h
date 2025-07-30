#pragma once
#include "Common/CommonFunLib.hpp"
#include "glfw/glfw3.h"
#include "Common/CommonFunLib.h"


namespace Input {


    inline std::vector<std::function<void(GLFWwindow* window)>> InputEventArray{};
    inline std::vector<std::function<void(GLFWwindow* window,double xpos,double ypos)>> MouseEventArray{};
    inline std::vector<std::function<void(GLFWwindow* window,double xpos,double ypos)>> ScrollEventArray{};


    inline void RegisterInputEvent(std::function<void(GLFWwindow* window)> func){
        LOG(LOGTEMP,"RegisterInputEvent");
        InputEventArray.push_back(func);
    }
    inline void RegisterMouseEvent(std::function<void(GLFWwindow* window,double xpos,double ypos)> func){
        LOG(LOGTEMP,"RegisterMouseEvent");
        MouseEventArray.push_back(func);
    }
    inline void RegisterScrollEvent(std::function<void(GLFWwindow* window,double xoffset,double yoffset)> func){
        LOG(LOGTEMP,"RegisterScrollEvent");
        ScrollEventArray.push_back(func);
    }
    inline void InputEvents(GLFWwindow* window){
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
            glfwSetWindowShouldClose(window, true);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
            LOG(LOGTEMP,"AAAAAAAAAAAA");
        }
        for (auto it : InputEventArray) {
            it(window);
        }
    }

    inline void MouseEvents(GLFWwindow* window,double xpos,double ypos){
        for (auto it : MouseEventArray) {
            it(window,xpos,ypos);
        }
    }

    inline void ScrollEvents(GLFWwindow* window,double xoffset,double yoffset){
        for (auto it : ScrollEventArray) {
            it(window,xoffset,yoffset);
            // LOG(LOGTEMP,"ScrollEvents");
        }
    }
}