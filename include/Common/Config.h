#pragma once

#include "glm/ext/vector_float3.hpp"
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

class Rotation : public glm::vec3{
    public:
        Rotation(float Roll, float Pitch, float Yaw) : glm::vec3(Roll, Pitch, Yaw) {}
        Rotation() : glm::vec3(0.0f, 0.0f, 0.0f) {}
        void SetRotation(float Roll, float Pitch, float Yaw) {
            this->mRoll = Roll;
            this->mPitch = Pitch;
            this->mYaw = Yaw;
        }

        float mRoll = 0.0f;
        float mPitch = 0.0f;
        float mYaw = 0.0f;
};