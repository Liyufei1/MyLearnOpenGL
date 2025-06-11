#include "CommonFunLib.h"

void lyf::Print(std::string log){
    std::cout << "Log:: " <<log << std::endl;
}
void lyf::PrintWarning(std::string log){
    std::cout << "Warning:: " <<log << std::endl;
}

void lyf::PrintError(std::string log){
    std::cout << "Error:: " <<log << std::endl;
}