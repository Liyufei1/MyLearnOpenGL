#pragma once
#include "Common/Config.h"
#include "Shader/ShaderProgram.h"
#include "glfw/glfw3.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_projection.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/trigonometric.hpp"
#include <memory>

// #include "Shader/ShaderProgram.h"

class ICamera{
    public:
        virtual glm::mat4 GetViewProjectionMMatrix() = 0;
};


class Camera :public ICamera
{
public:
    Camera();
    virtual glm::mat4 GetViewProjectionMMatrix() override;

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

class Light{
    glm::vec3 mPosition{0.0f, 0.0f, 0.0f};
    glm::vec3 mColor{1.0f, 1.0f, 1.0f};

    std::vector<std::shared_ptr<ShaderProgram>>  UsedShaderPrograms;
public:
    void UpdateLight();
    void SetLightColor(glm::vec3 color){mColor = color;}
    void SetLightPosition(glm::vec3 Position){mPosition = Position;}
    void AddShaderProgram(std::shared_ptr<ShaderProgram> pShaderProgram){UsedShaderPrograms.push_back(pShaderProgram);}

    glm::vec3 GetLightColor(){return mColor;}
    glm::vec3 GetLightPosition(){return mPosition;}

    
    // void SetLight(std::shared_ptr<ShaderProgram> pShaderProgram);
};