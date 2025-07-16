#pragma once
#include <iostream>
#include <string>
#include "CommonFunLib.hpp"

namespace lyf {
    void Print(std::string log);
    void PrintWarning(std::string log);
    void PrintError(std::string log);

    void QueryMaxAttribVetxCount();
}