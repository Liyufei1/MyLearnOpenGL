#pragma once
#include "glfw/glfw3.h"
#include "Common/CommonFunLib.h"


inline void InputEvents(GLFWwindow* window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        lyf::Print("AAAAAAAAAAAA");
    }
}