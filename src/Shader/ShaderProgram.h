#pragma once
#include "glad/glad.h"
#include "ShaderBase.h"

class ShaderProgram{
public:
    ShaderProgram() = delete;
    ShaderProgram(const ShaderBase& Shader);
    ~ShaderProgram();
    void Use() const;

private:
    GLuint Program = 0;
    bool bIsInit = false;
};