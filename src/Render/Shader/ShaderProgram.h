#pragma once
#include "Common/CommonFunLib.h"
#include "glad/glad.h"
#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <sstream>

class ShaderBase {
public:
    ShaderBase() = delete;
    ShaderBase(const char* vertexPath, const char* fragmentPath);
    ~ShaderBase();
    
    bool IsInit() const { return bIsInit; }
    GLuint GetVertexShader() const { return VertexShader; }
    GLuint GetFragmentShader() const { return FragmentShader; }

private:
    void InitShader(GLuint& Shader, GLenum type, const char* SourcePath);

    GLuint VertexShader = 0;
    GLuint FragmentShader = 0;
    bool bIsInit = false;
    std::string TempSourceBuffer{};
};

class ShaderProgram {
public:
    ShaderProgram() = delete;
    ShaderProgram(const ShaderBase& Shader);
    ShaderProgram(const char* vertexPath, const char* fragmentPath);
    ~ShaderProgram();

    void Use() const;
    int GetProgramID() const { return Program; }

    // 获取默认着色器（通过 RenderService 管理）
    static std::shared_ptr<ShaderProgram> GetDefaultShaderProgram();

    template<typename T>
    void SetParamater(const char* name, T value) const {
        GLuint location = glGetUniformLocation(Program, name);
        Use();
        if constexpr (std::is_same_v<T, int>) {
            glUniform1i(location, value);
        } else if constexpr (std::is_same_v<T, float>) {
            glUniform1f(location, value);
        } else if constexpr (std::is_same_v<T, glm::vec3>) {
            glUniform3fv(location, 1, glm::value_ptr(value));
        } else if constexpr (std::is_same_v<T, glm::mat4>) {
            glUniformMatrix4fv(location, 1, false, glm::value_ptr(value));
        } else if constexpr (std::is_same_v<T, glm::vec4>) {
            glUniform4fv(location, 1, glm::value_ptr(value));
        } else {
            std::ostringstream oss;
            oss << "ShaderPara type error :: " << typeid(T).name();
            LOG(LOGERROR, oss.str());
        }
    }

private:
    GLuint Program = 0;
    bool bIsInit = false;
};
