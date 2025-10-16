#pragma once
#include "Shader/ShaderProgram.h"
#include "glm/ext/vector_float3.hpp"
#include <memory>


class Light{

    glm::vec3 mAmbient{0.1f, 0.1f, 0.1f};
    glm::vec3 mDiffuse{0.8f, 0.8f, 0.8f};
    glm::vec3 mSpecular{1.0f, 1.0f, 1.0f};

public:
    virtual void UpdateLight(std::shared_ptr<ShaderProgram>) = 0;
    void SetAmbient(glm::vec3 pAmbient){bIsDirty = true ; mAmbient = pAmbient;}
    void SetDiffuse(glm::vec3 pDiffuse){bIsDirty = true ; mDiffuse= pDiffuse;}
    void SetSpecular(glm::vec3 pSpecular){bIsDirty = true ; mSpecular= pSpecular;}
    glm::vec3 GetAmbient(){return mAmbient;}
    glm::vec3 GetDiffuse(){return mDiffuse;}
    glm::vec3 GetSpecular(){return mSpecular;}

    bool  bIsDirty = true;
};

class DirLight : public Light
{
public:
    virtual void UpdateLight(std::shared_ptr<ShaderProgram> pShaderProgram) override;
    void SetDirection(glm::vec3 pDirection){bIsDirty = true ; mDirection= pDirection;}
private:
    glm::vec3 mDirection{0.0f, 0.0f, 0.0f};
};

class PointLight : public Light
{
public:
    virtual void UpdateLight(std::shared_ptr<ShaderProgram> pShaderProgram) override;
    void SetIndex(int pIndex){mIndex = pIndex;}
    int GetIndex(){return mIndex;}
    void SetLocation(glm::vec3 pLocation){bIsDirty = true ;mLocation = pLocation;}
    glm::vec3 GetLocation(){return mLocation;}
    void SetConstant(float pConstant){bIsDirty = true;mConstant = pConstant;}
    void SetLinear(float pLinear){bIsDirty = true;mLinear = pLinear;}
    void SetQuadratic(float pQuadratic){bIsDirty = true;mQuadratic = pQuadratic;}

private:
    int mIndex = 0;
    glm::vec3 mLocation{0.0f, 0.0f, 0.0f};
    float mConstant = 1.0f;     //常数项
    float mLinear = 0.22f;       //线性项
    float mQuadratic = 0.20f;    //二次项
};

class SpotLight : public Light
{
public:
    virtual void UpdateLight(std::shared_ptr<ShaderProgram> pShaderProgram) override;
    void SetIndex(int pIndex){mIndex = pIndex;}
    int GetIndex(){return mIndex;}
    void SetPosition(glm::vec3 pPosition){bIsDirty = true; mPosition = pPosition;}
    void SetDirection(glm::vec3 pDirection){bIsDirty = true; mDirection = pDirection;}
    void SetCutOff(float pCutOff){bIsDirty = true; mCutOff = pCutOff;}
    void SetOuterCutOff(float pOuterCutOff){bIsDirty = true; mOuterCutOff = pOuterCutOff;}

private:
    int mIndex = 0;
    glm::vec3 mPosition;      //点光源位置
    glm::vec3 mDirection;     //点光源方向
    float mCutOff;       //聚光 cutoff,角度制
    float mOuterCutOff;  //外聚光 cutoff，角度制
};