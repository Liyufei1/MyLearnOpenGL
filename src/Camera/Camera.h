#pragma once
#include "Common/Config.h"
#include "glfw/glfw3.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_projection.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/trigonometric.hpp"


class Camera
{
public:
    Camera();

    
    glm::mat4 GetViewProjectionMMatrix();

private:
    void InputEvents(GLFWwindow * pWindow);
    void MouseEvent(GLFWwindow* window,double xpos,double ypos);

    float mCameraSpeed = 1.0f;
    const float CAMERA_DEFAULT_SPEED = -0.05f;
    glm::vec3 mPosition{0.0f,0.0f,3.0f};
    glm::vec3 mRotation{0.0f,-90.0f,0.0f};
    glm::vec3 mCameraFwd{0.0f,1.0f,0.0f};
    glm::vec3 mCameraRight{1.0f,0.0f,0.0f};
    glm::vec3 mCameraUp{0.0f,0.0f,1.0f};
    glm::mat4 mViewMatrix;
    glm::mat4 mProjectionMatrix{glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f , 100.0f)};
    glm::mat4 mViewProjectionMatrix ;
    bool bIsDirty = true;


    double LastX = 0.0f;
    double LastY = 0.0f;
    bool bIsFirstMove = true;
    
};