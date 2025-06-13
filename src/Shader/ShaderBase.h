#pragma once
#include <glad/glad.h>
#include <string>


class ShaderBase{
public:
    ShaderBase() = delete;
    ShaderBase(const char* vertexPath, const char* fragmentPath);
    ~ShaderBase();
    bool IsInit() const { return bIsInit; }

    GLuint GetVertexShader() const { return VertexShader; }

    GLuint GetFragmentShader()const { return FragmentShader; }

private:
    void InitShader(GLuint& Shader,GLenum type,const char* SourcePath);

    GLuint VertexShader = 0;
    GLuint FragmentShader = 0;
    bool bIsInit = false;
};