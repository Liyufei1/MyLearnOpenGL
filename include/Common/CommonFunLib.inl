#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <sstream>
// #include "CommonFunLib.hpp"


namespace lyf {
    template<typename T>
    inline std::string ToString(T value){
        std::stringstream ss;
        ss << value;
        return ss.str();
    }

    inline std::string ToString(const glm::mat4& value){
        std::stringstream ss;
        ss << value[0][0] << " " << value[0][1] << " " << value[0][2] << " " << value[0][3] << std::endl;
        ss << value[1][0] << " " << value[1][1] << " " << value[1][2] << " " << value[1][3] << std::endl;
        ss << value[2][0] << " " << value[2][1] << " " << value[2][2] << " " << value[2][3] << std::endl;
        ss << value[3][0] << " " << value[3][1] << " " << value[3][2] << " " << value[3][3] << std::endl;
        return ss.str();
    }

}