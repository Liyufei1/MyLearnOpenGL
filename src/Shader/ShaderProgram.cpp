#include "ShaderProgram.h"
#include <string>
#include "Common/CommonFunLib.h"


ShaderProgram::ShaderProgram(const ShaderBase& Shader){
        Program = glCreateProgram();
        if (!Shader.IsInit()) {
            lyf::PrintError("Init ShaderProgram Failed : Shader Not Init");
            return;
        };
        glAttachShader(Program, Shader.GetVertexShader());
        glAttachShader(Program, Shader.GetFragmentShader());
        glLinkProgram(Program);
        GLint Success = 0;
        glGetProgramiv(Program, GL_LINK_STATUS, &Success);
        if(!Success) {
            GLchar  infoLog[512];
            glGetProgramInfoLog(Program, 512, NULL, infoLog);
            lyf::PrintError("Init ShaderProgram Failed : Link Failed" + std::string(infoLog));
        }
        bIsInit = true;
}
ShaderProgram::~ShaderProgram(){ 
    glDeleteProgram(Program); 
}

void ShaderProgram::Use() const{
    if (!bIsInit) {
        lyf::PrintError("ShaderProgram is not init");
        return;
    }
    glUseProgram(Program);
}