#pragma once
#include "glm/fwd.hpp"
#include <string>


namespace lyf {
    template<typename T>
    std::string ToString(T value);

    std::string ToString(const glm::mat4& value);
}



#include "CommonFunLib.inl"