
# 1.项目介绍
这是一个LearnOpengl的代码学习框架。主旨是学习OpenGL，通过学习这个框架，可以快速了解OpenGL的流程，以及一些常用的函数。
# 1.1 本项目使用scons作为构建工具。
1. `scons -Q` 编译代码，并在build中生成可执行文件。
2. `scons -c` 清理编译文件。

# 2.外部库
## 2.1 glfw
glfw用于创建一个窗口，并管理输入。即window类的底层接口。


## 2.2 glad
glad是对OpenGL函数指针的封装，提供了可调用的openGL函数。

## 2.3 glm
glm是一个轻量化的线性代数数学运算库，对glsl的适配度较高。

# 3.内部类
## 3.1 Window
Window类封装了glfw的创建窗口，管理输入，以及注册主体函数等功能。
1. `Init()` 初始化glfw，并创建窗口。
2. `Run()`  运行主函数。
3. `Close()` 关闭窗口。
4. `std::function<void()> InFunction` 主函数。
5. 在`Window/InputEvent.h` 中定义了输入事件，可进行输入事件的添加。

示例：
```cpp
Window window(1920, 1080, "OpenGL");
window.Init();
window.SetRunFunction([&](){
		glClearColor(0.9f,0.9f,0.8f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
	});
window.Run();
window.Close();	
```

## 3.2 ShaderBase
Shader类封装了OpenGl的着色器，并管理着色器的生命周期。它删除了默认构造函数，并定义了需要两个文件路径构造函数。
```cpp
//着色器创建示例
ShaderBase ShaderTest{"src/Shader/PhoneShader/PhoneVertex.glsl",
						"src/Shader/PhoneShader/PhoneFragment.glsl"};
```

## 3.3 ShaderProgram
ShaderProgram类封装了OpenGL的着色器程序，并管理着色器程序的生命周期。通过它，我们可以在窗口中使用着色器程序。
```cpp
//着色器程序示例
ShaderProgram ShaderProgramTest(ShaderTest);
ShaderProgramTest.Use();
glBindVertexArray(VAO);
glDrawArrays(GL_TRIANGLES, 0, 6); 
```
