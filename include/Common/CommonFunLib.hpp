#pragma once
#include "glm/fwd.hpp"
#include <string>
#include <iostream>

#define LOGTEMP lyf::LogLevel::LogTemp
#define LOGWARNING lyf::LogLevel::Warning
#define LOGERROR lyf::LogLevel::Error

#define LOG(level, ...) lyf::Log<level>(__FILE__,"(",__LINE__,")   ",__VA_ARGS__);

namespace lyf {
    enum class LogLevel : uint8_t{
        None = 0,
        LogTemp = 1,
        Warning = 2,
        Error = 3
    };
    constexpr LogLevel TempLevel = LogLevel::LogTemp;
    constexpr LogLevel WarningLevel = LogLevel::Warning;
    constexpr LogLevel ErrorLevel = LogLevel::Error;

    template <lyf::LogLevel Level ,typename ...Args>
    void Log(Args ...args){
        if constexpr (Level <= TempLevel){
            std::cout << "LogTemp  ";
        }else if constexpr (Level == WarningLevel){
            std::cout << "Warning  ";
        }else {
            std::cout << "Error  ";
        }
        (std::cout <<  ... << args) << std::endl;
    }

    template<typename T>
    std::string ToString(T value);

    std::string ToString(const glm::mat4& value);
}



#include "CommonFunLib.inl"