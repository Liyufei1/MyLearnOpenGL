#include "CommonFunLib.h"
#include "glad/glad.h"

void lyf::Print(std::string log){
    std::cout << "Log:: " <<log << std::endl;
}
void lyf::PrintWarning(std::string log){
    std::cout << "Warning:: " <<log << std::endl;
}

void lyf::PrintError(std::string log){
    std::cout << "Error:: " <<log << std::endl;
}

void lyf::QueryMaxAttribVetxCount(){
    GLint maxAttribs = 0;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxAttribs);
	std::cout << "Max vertex attributes: " << maxAttribs << std::endl;
}