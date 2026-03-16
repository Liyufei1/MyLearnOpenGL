#include "ShaderProgram.h"
#include <fstream>
#include <string>
#include "Common/CommonFunLib.h"


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
