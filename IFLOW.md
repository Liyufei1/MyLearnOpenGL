# LearnOpenGL 项目文档

## 项目概述

这是一个基于 OpenGL 的图形编程学习框架，旨在帮助开发者快速理解 OpenGL 的渲染流程和常用函数。项目采用 C++17 编写，使用 SCons 作为构建工具，封装了常用的 OpenGL 功能，提供了简洁易用的 API。

### 主要技术栈

- **语言**: C++17
- **构建工具**: SCons
- **图形 API**: OpenGL
- **窗口管理**: GLFW
- **OpenGL 加载器**: GLAD
- **数学库**: GLM (OpenGL Mathematics)

### 核心架构

项目采用面向对象设计，主要包含以下模块：

1. **Window** - 窗口管理和输入处理
2. **Shader** - 着色器管理和编译
3. **Mesh** - 网格数据和渲染管理
4. **Camera** - 相机系统和视图投影
5. **Light** - 光照系统（方向光、点光源、聚光灯）
6. **Material** - 材质和纹理管理
7. **Texture** - 纹理加载和管理

## 构建和运行

### 环境要求

- Windows 10 或更高版本
- Python 3.x（用于 SCons）
- Visual Studio 或支持 C++17 的编译器
- 已安装的外部依赖库（位于 `include/` 和 `lib/` 目录）

### 构建命令

```bash
# 编译项目
scons -Q

# 清理编译文件
scons -c
```

编译后的可执行文件位于 `build/app.exe`。

### 运行项目

```bash
cd build
./app.exe
```

## 项目结构

```
LearnOpenGL/
├── include/              # 头文件和外部依赖库
│   ├── glad/            # OpenGL 函数加载器
│   ├── glfw/            # 窗口管理库头文件
│   ├── glm/             # 数学库
│   ├── assimp/          # 3D 模型加载库
│   ├── imgui/           # 即时模式 GUI 库
│   ├── stb/             # 图像加载库
│   └── Common/          # 通用工具库
├── src/                 # 源代码
│   ├── main.cpp         # 主程序入口
│   ├── Window/          # 窗口管理
│   ├── Shader/          # 着色器系统
│   ├── Mesh/            # 网格和渲染管理
│   ├── Camera/          # 相机系统
│   ├── Light/           # 光照系统
│   └── Texture/         # 纹理管理
├── lib/                 # 静态库文件
├── Art/                 # 资源文件（纹理等）
├── build/               # 构建输出目录
└── SConstruct          # SCons 构建脚本
```

## 核心类说明

### Window 类

单例模式，封装了 GLFW 的窗口创建和输入管理。

**主要方法:**
- `GetInstance()` - 获取窗口单例实例
- `Init()` - 初始化 GLFW 和窗口
- `Run()` - 运行主循环
- `Close()` - 关闭窗口
- `SetRunFunction(std::function<void()>)` - 设置主循环函数

**使用示例:**
```cpp
Window& window = Window::GetInstance();
window.SetRunFunction([&](){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // 渲染代码
});
window.Run();
```

### ShaderBase 类

封装了 OpenGL 着色器的编译和管理。

**构造函数:**
```cpp
ShaderBase(const char* vertexPath, const char* fragmentPath);
```

### ShaderProgram 类

管理着色器程序的链接和使用。

**主要方法:**
- `Use()` - 激活着色器程序
- `SetParamater<T>(const std::string&, T)` - 设置着色器参数
- `GetDefaultShaderProgram()` - 获取默认着色器程序

### StaticMesh 类

静态网格类，管理顶点数据和渲染。

**主要方法:**
- `CreateMesh()` - 创建网格实例
- `SetMaterial()` - 设置材质
- `SetLocation()` - 设置位置
- `SetRotation()` - 设置旋转
- `SetScale()` - 设置缩放
- `GetModelMatrix()` - 获取模型矩阵

**顶点属性结构:**
```cpp
struct VertexAttrib {
    glm::vec3 vertex;    // 顶点位置
    glm::vec3 tangent;   // 切线
    glm::vec3 normal;    // 法线
    glm::vec3 color;     // 颜色
    glm::vec2 uv;        // 纹理坐标0
    glm::vec2 uv1s;      // 纹理坐标1
    glm::vec2 uv2s;      // 纹理坐标2
};
```

### RenderManager 类

渲染管理器单例，管理所有网格、光源和着色器程序。

**主要方法:**
- `GetInstance()` - 获取渲染管理器单例
- `Render()` - 执行渲染
- `BindData()` - 绑定 GPU 数据
- `AddMesh()` - 添加网格
- `AddLight()` - 添加光源
- `AddShaderProgram()` - 添加着色器程序

### Camera 类

相机系统，管理视图和投影矩阵。

**主要方法:**
- `GetViewProjectionMMatrix()` - 获取视图投影矩阵
- `GetPosition()` - 获取相机位置

### Light 类系统

光照系统基类及其派生类：

- **Light** - 光照基类
- **DirLight** - 方向光
- **PointLight** - 点光源
- **SpotLight** - 聚光灯

**常用方法:**
- `SetAmbient()` - 设置环境光
- `SetDiffuse()` - 设置漫反射
- `SetSpecular()` - 设置镜面反射
- `UpdateLight()` - 更新光照到着色器

### Material 类

材质管理，支持纹理和颜色设置。

**派生类:**
- **StdMaterial** - 标准材质
- **PhoneMaterial** - Phong 光照材质

**主要方法:**
- `SetDiffuseTexture()` - 设置漫反射纹理
- `SetSpecularTexture()` - 设置镜面反射纹理
- `SetDiffuseColor()` - 设置漫反射颜色
- `SetShininess()` - 设置高光强度
- `Use()` - 使用材质

### Texture2D 类

2D 纹理加载和管理。

**构造函数:**
```cpp
Texture2D(const std::string& path);
```

## 开发约定

### 编码规范

1. **命名约定**:
   - 类名使用帕斯卡命名法（PascalCase）：`Window`, `StaticMesh`
   - 成员变量使用匈牙利命名法前缀：`mWindow`, `bIsInit`
   - 函数名使用帕斯卡命名法：`GetInstance()`, `SetRunFunction()`

2. **单例模式**:
   - 主要管理类使用单例模式（Window、RenderManager）
   - 通过静态 `GetInstance()` 方法获取实例

3. **智能指针**:
   - 优先使用 `std::shared_ptr` 管理对象生命周期
   - 网格对象使用 `std::enable_shared_from_this`

4. **头文件保护**:
   - 使用 `#pragma once` 防止重复包含

### 着色器组织

着色器文件位于 `src/Shader/` 目录下，按类型组织：

- `BaseShader/` - 基础着色器
- `PhoneShader/` - Phong 光照着色器

着色器文件扩展名：`.glsl`

### 资源管理

- 纹理资源位于 `Art/Texture/` 目录
- 使用相对路径或绝对路径加载资源
- 建议使用 `std::shared_ptr` 管理资源生命周期

### 渲染流程

典型的渲染流程：

1. 初始化窗口和资源
2. 创建网格并设置材质
3. 添加光源到渲染管理器
4. 调用 `RenderManager::BindData()` 绑定 GPU 数据
5. 在主循环中调用 `RenderManager::Render()` 执行渲染

**示例:**
```cpp
// 1. 加载资源
auto texture = std::make_shared<Texture2D>("Art/Texture/container.png");
auto shader = std::make_shared<ShaderProgram>("vertex.glsl", "fragment.glsl");
auto material = std::make_shared<PhoneMaterial>();
material->SetDiffuseTexture(texture);
material->SetShaderPrograrm(shader);

// 2. 创建网格
auto mesh = BoxMesh();
mesh->SetMaterial(material);
mesh->SetLocation(glm::vec3(0.0f, 0.0f, 0.0f));

// 3. 添加光源
DirLight dirLight;
dirLight.SetDirection(glm::vec3(0.0f, -1.0f, -1.0f));
RenderManager::GetInstance().AddLight(&dirLight);

// 4. 绑定数据
RenderManager::GetInstance().BindData();

// 5. 渲染循环
window.SetRunFunction([&](){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    RenderManager::GetInstance().Render();
});
window.Run();
```

## 外部依赖

### GLFW
- **用途**: 窗口创建和输入管理
- **版本**: glfw3
- **库文件**: `lib/glfw3_mt.lib`

### GLAD
- **用途**: OpenGL 函数加载
- **文件**: `include/glad/glad.c`, `include/glad/glad.h`

### GLM
- **用途**: 数学运算（向量、矩阵）
- **版本**: header-only 库
- **位置**: `include/glm/`

### STB Image
- **用途**: 图像加载（支持 PNG、JPG 等）
- **文件**: `include/stb/stb_image.h`

### Assimp
- **用途**: 3D 模型加载
- **位置**: `include/assimp/`

## 配置文件

### SConstruct
SCons 构建脚本，配置编译选项：

- C++ 标准: C++17
- 包含路径: `include/`, `src/`, `Art/`
- 链接库: `glfw3_mt`, `shell32`, `User32`, `Gdi32`
- 输出目录: `build/`

### Config.h
全局配置文件：

```cpp
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
```

## 常见任务

### 添加新的着色器

1. 在 `src/Shader/` 下创建新目录（如 `MyShader/`）
2. 创建顶点着色器 `.glsl` 和片段着色器 `.glsl`
3. 在代码中使用：
   ```cpp
   auto shader = std::make_shared<ShaderProgram>(
       "src/Shader/MyShader/vertex.glsl",
       "src/Shader/MyShader/fragment.glsl"
   );
   ```

### 创建新的网格

使用 `MeshLib` 提供的辅助函数或手动创建：

```cpp
// 使用辅助函数
auto mesh = BoxMesh();
mesh->SetLocation(glm::vec3(0.0f, 0.0f, 0.0f));

// 手动创建
auto mesh = StaticMesh::CreateMesh();
// 填充 mesh->mMeshBatch
```

### 添加自定义光源

继承 `Light` 基类并实现 `UpdateLight` 方法：

```cpp
class MyLight : public Light {
public:
    void UpdateLight(std::shared_ptr<ShaderProgram> pShaderProgram) override {
        // 实现光照更新逻辑
    }
};
```

## 注意事项

1. **路径问题**: 注意 Windows 路径分隔符，建议使用正斜杠 `/` 或双反斜杠 `\\`
2. **资源加载**: 确保纹理和模型文件路径正确
3. **内存管理**: 使用智能指针管理对象生命周期，避免内存泄漏
4. **渲染顺序**: 确保在 `Render()` 之前调用 `BindData()`
5. **着色器参数**: 使用 `SetParamater<T>()` 设置着色器 uniform 变量

## 扩展阅读

- [OpenGL 官方文档](https://www.khronos.org/opengl/)
- [LearnOpenGL-CN](https://learnopengl-cn.github.io/)
- [GLFW 文档](https://www.glfw.org/documentation.html)
- [GLM 文档](https://github.com/g-truc/glm)