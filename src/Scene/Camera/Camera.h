#pragma once
#include "Common/Config.h"
#include "glfw/glfw3.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/trigonometric.hpp"

// #include "Shader/ShaderProgram.h"

class ICamera{
    public:
        virtual glm::mat4 GetViewProjectionMMatrix() = 0;
        virtual glm::vec3 GetPosition() = 0;
};


class Camera :public ICamera
{
public:
    Camera();
    virtual glm::mat4 GetViewProjectionMMatrix() override;
    glm::vec3 GetPosition()override {return mPosition;}

private:
    void InputEvents(GLFWwindow * pWindow);
    void MouseEvent(GLFWwindow* window,double xpos,double ypos);
    void ScrollEvent(GLFWwindow* window,double xpos,double ypos);

    const float CAMERA_DEFAULT_SPEED = -0.05f;
    float mCameraSpeed = 1.0f;

    float mFov = 45.0f;
    glm::vec3 mPosition{0.0f,0.0f,3.0f};
    glm::vec3 mRotation{0.0f,-90.0f,0.0f};
    glm::vec3 mCameraFwd{0.0f,1.0f,0.0f};
    glm::vec3 mCameraRight{1.0f,0.0f,0.0f};
    glm::vec3 mCameraUp{0.0f,0.0f,1.0f};
    glm::mat4 mViewMatrix;
    glm::mat4 mProjectionMatrix{glm::perspective(glm::radians(mFov), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f , 100.0f)};
    glm::mat4 mViewProjectionMatrix ;
    bool bIsDirty = true;


    double LastX = 0.0f;
    double LastY = 0.0f;
    bool bIsFirstMove = true;
    
};


// class ShaderProgram;

