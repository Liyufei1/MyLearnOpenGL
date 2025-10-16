#pragma once
#include "Common/CommonFunLib.h"
#include "glad/glad.h"
#include "ShaderBase.h"
#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <sstream>

class ShaderProgram{
public:
    ShaderProgram() = delete;
    ShaderProgram(const ShaderBase& Shader);
    ShaderProgram(const char* vertexPath, const char* fragmentPath);
    ~ShaderProgram();
    void Use() const;

    int GetProgramID() const{return Program;}

    static std::shared_ptr<ShaderProgram> GetDefaultShaderProgram();

    template<typename T>
    void SetParamater(const char* name, T value) const{
        GLuint location = glGetUniformLocation(Program, name);
        Use();
        if constexpr (std::is_same_v<T, int>) {
            glUniform1i(location, value);
        }else if constexpr (std::is_same_v<T, float>) {
            glUniform1f(location, value);
        }else if constexpr (std::is_same_v<T, glm::vec3>) {
            glUniform3fv(location,1,glm::value_ptr(value));
        }else if constexpr (std::is_same_v<T, glm::mat4>) {
            glUniformMatrix4fv(location,1,false,glm::value_ptr(value));
        }else if constexpr (std::is_same_v<T, glm::vec4>) {
            glUniform4fv(location,1,glm::value_ptr(value));
        }else {
            std::ostringstream oss;
            oss << "ShaderPara type error :: " << typeid(T).name();
            LOG(LOGERROR,oss.str());    
        }
    }
private:
    GLuint Program = 0;
    bool bIsInit = false;

    static std::shared_ptr<ShaderProgram> DefaultShaderProgram;
};