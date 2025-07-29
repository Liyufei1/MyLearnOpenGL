#include "CommonFunLib.h"
#include "glad/glad.h"

void lyf::QueryMaxAttribVetxCount(){
    GLint maxAttribs = 0;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxAttribs);
	std::cout << "Max vertex attributes: " << maxAttribs << std::endl;
}