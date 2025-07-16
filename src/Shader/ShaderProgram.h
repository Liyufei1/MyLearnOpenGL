#pragma once
#include "Common/CommonFunLib.h"
#include "glad/glad.h"
#include "ShaderBase.h"
#include <sstream>

class ShaderProgram{
public:
    ShaderProgram() = delete;
    ShaderProgram(const ShaderBase& Shader);
    ShaderProgram(const char* vertexPath, const char* fragmentPath);
    ~ShaderProgram();
    void Use() const;
    template<typename T>
    void SetParamater(const char* name, T value) const{
        GLuint location = glGetUniformLocation(Program, name);
        Use();
        if constexpr (std::is_same_v<T, int>) {
            glUniform1i(location, value);
        }else if constexpr (std::is_same_v<T, float>) {
            glUniform1f(location, value);
        }else {
            std::ostringstream oss;
            oss << "ShaderPara type error :: " << typeid(T).name();
            lyf::PrintError(oss.str());    
        }
    }
private:
    GLuint Program = 0;
    bool bIsInit = false;
};