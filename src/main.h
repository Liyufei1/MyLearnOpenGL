#pragma once
#include "Common/CommonFunLib.h"
#include "Window/Window.h"
#include "Shader/ShaderBase.h"
#include "Shader/ShaderProgram.h"
#include "glm/ext/vector_float3.hpp"
#include "glm/glm.hpp"
#include <string>

int main()
{
	Window window(1920, 1080, "OpenGL");
	window.Init();

	ShaderBase ShaderTest{"src/Shader/PhoneShader/PhoneVertex.glsl",
						"src/Shader/PhoneShader/PhoneFragment.glsl"};

	ShaderProgram ShaderProgramTest(ShaderTest);

	
 	float vertices[] = {
        // first triangle
        -0.9f, -0.5f, 0.0f,  // left 
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top 
        // second triangle
         0.0f, -0.5f, 0.0f,  // left
         0.9f, -0.5f, 0.0f,  // right
         0.45f, 0.5f, 0.0f   // top 
    }; 

		unsigned int VBO, VAO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0); 

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0); 

	window.SetRunFunction([&](){
		glClearColor(0.9f,0.9f,0.8f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
		ShaderProgramTest.Use();
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 6); 
	});
	window.Run();


	window.Close();	
	return 0;
}
