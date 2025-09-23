#include "Camera.h"

#include "Common/CommonFunLib.h"
#include "Common/CommonFunLib.hpp"
#include "glfw/glfw3.h"
#include "glm/ext/vector_float3.hpp"
#include "glm/ext/vector_float4.hpp"
#include "glm/trigonometric.hpp"
#include "Window/InputEvent.h"
#include <algorithm>
#include <cmath>
#include <functional>




Camera::Camera(){
	Input::RegisterInputEvent(std::bind(&Camera::InputEvents,this,std::placeholders::_1));
	Input::RegisterMouseEvent(std::bind(&Camera::MouseEvent,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
    Input::RegisterScrollEvent(std::bind(&Camera::ScrollEvent,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
}
void Camera::InputEvents(GLFWwindow * pWindows){

    if (glfwGetKey(pWindows, GLFW_KEY_A) == GLFW_PRESS){
        mPosition += mCameraRight * CAMERA_DEFAULT_SPEED * mCameraSpeed;
        bIsDirty = true;
    }
    if (glfwGetKey(pWindows, GLFW_KEY_D) == GLFW_PRESS){
        mPosition -= mCameraRight * CAMERA_DEFAULT_SPEED * mCameraSpeed;
        bIsDirty = true;
    }
    if (glfwGetKey(pWindows, GLFW_KEY_S) == GLFW_PRESS){
        mPosition += mCameraFwd * CAMERA_DEFAULT_SPEED * mCameraSpeed;
        bIsDirty = true;
    }
    if (glfwGetKey(pWindows, GLFW_KEY_W) == GLFW_PRESS){
        mPosition -= mCameraFwd * CAMERA_DEFAULT_SPEED * mCameraSpeed;
        bIsDirty = true;
    }
    if (glfwGetKey(pWindows, GLFW_KEY_E) == GLFW_PRESS){
        mPosition -= mCameraUp * CAMERA_DEFAULT_SPEED * mCameraSpeed;
        bIsDirty = true;
    }
    if (glfwGetKey(pWindows, GLFW_KEY_Q) == GLFW_PRESS){
        mPosition += mCameraUp * CAMERA_DEFAULT_SPEED * mCameraSpeed;
        bIsDirty = true;
    }

}

void Camera::MouseEvent(GLFWwindow* window,double xpos,double ypos){
    // LOG(LOGTEMP, xpos,"::------::",ypos);
    if (bIsFirstMove) {
        LastX = xpos;
        LastY = ypos;
        bIsFirstMove = false;
    }else {
        double DertaX = (LastX - xpos)*0.05;
        double DertaY = (LastY - ypos)*0.02;
        LastX = xpos;
        LastY = ypos;
        double Picth = mRotation.y;
        double Yaw = mRotation.z;

        Picth = std::min(90.0,std::max(-90.0,(Picth + DertaY)));
        Yaw = std::fmod((Yaw + DertaX),360);
        mRotation  = glm::vec3(mRotation.x,Picth,Yaw);
        // LOG(LOGTEMP,"Rotation::",glm::to_string(mRotation));
        // LOG(LOGTEMP,"Position::",glm::to_string(mPosition));
        bIsDirty = true;
    }
    // mRotation.z += xpos * CAMERA_DEFAULT_SPEED;
    // mRotation.y += ypos * CAMERA_DEFAULT_SPEED;
}

void Camera::ScrollEvent(GLFWwindow* window,double xpos,double ypos){
    if(mFov >= 1.0f && mFov <= 45.0f){
        mFov -= ypos;
        mProjectionMatrix = glm::perspective(glm::radians(mFov), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f , 100.0f);
        bIsDirty = true;
    }
    if(mFov <= 1.0f)
        mFov = 1.0f;
    if(mFov >= 45.0f)
        mFov = 45.0f;
}



glm::mat4 Camera::GetViewProjectionMMatrix(){
    if (!bIsDirty) {
        return mViewProjectionMatrix;
    }
    bIsDirty = false;
    glm::vec3 Direction{ 0.0f, 1.0f, 0.0f };
    glm::vec3 Up{0.0f, 0.0f, 1.0f};
    glm::vec3 Right{1.0f, 0.0f, 0.0f};

    glm::mat4 RotMat(1.0f);
    RotMat = glm::rotate(RotMat, glm::radians(mRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    RotMat = glm::rotate(RotMat, glm::radians(mRotation.y), glm::vec3(1.0f, 0.0f, 0.0f));
    RotMat = glm::rotate(RotMat, glm::radians(mRotation.x), glm::vec3(0.0f, 1.0f, 0.0f));
    // yaw pitch roll   对应 
    mCameraFwd = glm::vec3(RotMat * glm::vec4(Direction, 1.0f));
    mCameraUp = glm::vec3(RotMat * glm::vec4(Up, 1.0f));
    mCameraRight = glm::vec3(RotMat * glm::vec4(Right, 1.0f));
    mViewMatrix = glm::lookAt(mPosition, mPosition + mCameraFwd, mCameraUp);
    mViewProjectionMatrix = mProjectionMatrix * mViewMatrix;

    return mViewProjectionMatrix;
}


void Light::UpdateLight(){
    for (auto it : UsedShaderPrograms) {
        if (bIsDirty) {
            bIsDirty = false;
            it->SetParamater("uLight.position",mPosition);
            it->SetParamater("uLight.ambient",mAmbient);
            it->SetParamater("uLight.diffuse",mDiffuse);
            it->SetParamater("uLight.specular",mSpecular);
        }

    }
}
