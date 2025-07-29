#pragma once
#include "Common/CommonFunLib.hpp"
#include "glfw/glfw3.h"
#include "Common/CommonFunLib.h"


namespace Input {


    inline std::vector<std::function<void(GLFWwindow* window)>> InputEventArray{};
    inline std::vector<std::function<void(GLFWwindow* window,double xpos,double ypos)>> MouseEventArray{};


    inline void RegisterInputEvent(std::function<void(GLFWwindow* window)> func){
        LOG(LOGTEMP,"RegisterInputEvent");
        InputEventArray.push_back(func);
    }
    inline void RegisterMouseEvent(std::function<void(GLFWwindow* window,double xpos,double ypos)> func){
        LOG(LOGTEMP,"RegisterMouseEvent");
        MouseEventArray.push_back(func);
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

    static void MouseEvents(GLFWwindow* window,double xpos,double ypos){
        for (auto it : MouseEventArray) {
            it(window,xpos,ypos);
        }
    }
}