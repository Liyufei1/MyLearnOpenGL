#include "ShaderProgram.h"
#include <string>
#include "Common/CommonFunLib.h"
#include "ShaderBase.h"

std::shared_ptr<ShaderProgram> ShaderProgram::DefaultShaderProgram = nullptr;
std::shared_ptr<ShaderProgram> ShaderProgram::GetDefaultShaderProgram(){
    if (DefaultShaderProgram == nullptr) {
        DefaultShaderProgram = std::make_shared<ShaderProgram>("src/Shader/BaseShader/BaseVertex.glsl","src/Shader/BaseShader/BaseFragment.glsl");
    }
    return DefaultShaderProgram;
}

int CurShaderProgram = 0;

ShaderProgram::ShaderProgram(const ShaderBase& Shader){
        Program = glCreateProgram();
        if (!Shader.IsInit()) {
            LOG(LOGERROR,"Init ShaderProgram Failed : Shader Not Init");
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
            LOG(LOGERROR,"Init ShaderProgram Failed : Link Failed" + std::string(infoLog));
        }
        bIsInit = true;
}
ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath)
:ShaderProgram(ShaderBase(vertexPath, fragmentPath))
{
}

ShaderProgram::~ShaderProgram(){ 
    glDeleteProgram(Program); 
}

void ShaderProgram::Use() const{
    if (!bIsInit) {
        LOG(LOGERROR,"ShaderProgram is not init");
        return;
    }
    // LOG(LOGERROR,"Use ShaderProgram :: ", Program);
    if (CurShaderProgram == Program) {
        return;
    }
    glUseProgram(Program);
}

// void ShaderProgram::SetParamater(const char* name, int value)const{
//     GLuint location = glGetUniformLocation(Program, name);
//     Use();
//     glUniform1i(location, value);
// }
