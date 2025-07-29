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
        ss << std::endl;
        for (int row = 0 ; row < 4 ; row++) {
            ss << "|";
            for (int col = 0 ; col < 4 ; col++) {
                ss << value[col][row] << " ";
            }
            ss << "|" <<std::endl;
        }
        return ss.str();
    }

}