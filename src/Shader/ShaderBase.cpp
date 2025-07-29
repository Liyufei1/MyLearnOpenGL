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
        LOG(LOGERROR,"Failed to open file: " + std::string(SourcePath));
        return;
    }

    std::stringstream buffer{};
    
    buffer << file.rdbuf();
    file.close();

    // LOG(LOGERROR,"Successfully opened file: " + std::string(SourcePath));
    // LOG(LOGERROR,buffer.str());
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
        LOG(LOGTEMP,"Init Shader Failed : " + std::string(TempSource));
        LOG(LOGTEMP,infoLog);
    }else {
        LOG(LOGTEMP,"Init Shader Success : " + std::string(SourcePath));
        bIsInit = true;
    }
}



