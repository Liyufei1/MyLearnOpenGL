#include "ShaderBase.h"
#include "Common/CommonFunLib.h"
#include "ShaderProgram.h"
#include <fstream>
#include <sstream>
#include <iostream>

ShaderBase::ShaderBase(const char* vertexPath, const char* fragmentPath){
    InitShader(VertexShader,GL_VERTEX_SHADER,vertexPath);
    InitShader(FragmentShader,GL_FRAGMENT_SHADER,fragmentPath);
}
ShaderBase::~ShaderBase(){
    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);
}

void ShaderBase::InitShader(GLuint& Shader,GLenum type,const char* SourcePath){
    std::ifstream file(SourcePath);
    if (!file.is_open()) {
        lyf::PrintError("Failed to open file: " + std::string(SourcePath));
        return;
    }

    std::stringstream buffer{};
    
    buffer << file.rdbuf();
    file.close();

    // lyf::PrintError("Successfully opened file: " + std::string(SourcePath));
    // lyf::PrintError(buffer.str());
    TempSourceBuffer = buffer.str();
    const char * TempSource = TempSourceBuffer.c_str();

    Shader = glCreateShader(type);
    glShaderSource(Shader, 1, &TempSource, NULL);
    glCompileShader(Shader);
    GLint Success = 0;
    glGetShaderiv(Shader, GL_COMPILE_STATUS, &Success);
    if (!Success) {
        char infoLog[512];
        glGetShaderInfoLog(Shader, 512, NULL, infoLog);
        lyf::PrintError("Init Shader Failed : " + std::string(TempSource));
        lyf::PrintError(infoLog);
    }else {
        lyf::Print("Init Shader Success : " + std::string(SourcePath));
        bIsInit = true;
    }
}



