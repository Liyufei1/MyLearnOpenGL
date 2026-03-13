# ImGui 学习文档

## 库概述
- **库名称**：Dear ImGui
- **版本**：1.90+
- **官方网站**：https://github.com/ocornut/imgui
- **一句话描述**：即时模式 GUI（Immediate Mode GUI）库，专为工具和调试界面设计，轻量级、高性能、易于集成

---

## 核心概念

### 设计思想
Dear ImGui 采用**即时模式**渲染范式，与传统的保留模式 GUI（如 Qt、MFC）完全不同：
- **即时模式**：每帧重新构建 UI，状态由用户代码管理，无复杂的事件循环
- **无依赖**：不依赖任何窗口系统，直接渲染到任意图形 API（OpenGL、DirectX、Vulkan 等）
- **工具导向**：专为开发工具、调试器、编辑器设计，而非最终用户应用

### 关键术语
- **Context（上下文）**：ImGui 的全局状态，每个窗口/线程需要一个独立的 Context
- **ID（标识符）**：用于区分控件的唯一标识，通常由标签字符串自动生成
- **Window（窗口）**：ImGui 的容器，可以嵌套、停靠、拖拽
- **Widget（控件）**：按钮、滑块、文本框等 UI 元素
- **Backend（后端）**：负责处理输入和渲染的平台适配层（如 imgui_impl_glfw.cpp）
- **Docking（停靠）**：允许窗口停靠到其他窗口或边缘的功能

### 主要特性
- 即时模式渲染，无复杂状态管理
- 支持停靠窗口（Docking）
- 丰富的控件集（按钮、滑块、树形视图、表格等）
- 高性能，适合实时渲染
- 轻量级，核心代码仅几千行
- 可定制主题和样式
- 支持多字体、多语言

---

## 主要类/接口

### 核心类

#### ImGuiContext
- **职责**：存储 ImGui 的全局状态
- **主要方法**：
  - `ImGui::CreateContext()` - 创建上下文
  - `ImGui::DestroyContext()` - 销毁上下文
  - `ImGui::GetCurrentContext()` - 获取当前上下文

#### ImGuiIO
- **职责**：输入输出配置，处理用户输入和渲染设置
- **主要属性**：
  - `DeltaTime` - 帧时间
  - `DisplaySize` - 显示尺寸
  - `MousePos` - 鼠标位置
  - `MouseDown` - 鼠标按键状态
  - `KeyMap` - 键盘映射

#### ImGuiStyle
- **职责**：控制 UI 的外观和样式
- **主要属性**：
  - `Alpha` - 全局透明度
  - `WindowPadding` - 窗口内边距
  - `ItemSpacing` - 控件间距
  - `Colors[]` - 颜色数组

### 关键接口
- `ImGui::Begin()` - 开始一个窗口
- `ImGui::End()` - 结束当前窗口
- `ImGui::Button()` - 创建按钮
- `ImGui::SliderFloat()` - 创建浮点滑块
- `ImGui::Checkbox()` - 创建复选框
- `ImGui::Text()` - 显示文本
- `ImGui::InputText()` - 文本输入框
- `ImGui::ColorEdit3()` - 颜色编辑器
- `ImGui::Render()` - 渲染绘制命令

---

## 典型使用模式

### 初始化流程
```cpp
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// 1. 创建 ImGui 上下文
IMGUI_CHECKVERSION();
ImGui::CreateContext();
ImGuiIO& io = ImGui::GetIO();
io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // 启用键盘导航
io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;       // 启用停靠功能

// 2. 设置样式
ImGui::StyleColorsDark();

// 3. 初始化后端
ImGui_ImplGlfw_InitForOpenGL(window, true);
ImGui_ImplOpenGL3_Init("#version 330");
```

### 基础用法
```cpp
// 在主循环中
ImGui_ImplOpenGL3_NewFrame();
ImGui_ImplGlfw_NewFrame();
ImGui::NewFrame();

// 创建窗口和控件
ImGui::Begin("Hello, World!");
ImGui::Text("This is some useful text.");
if (ImGui::Button("Click Me")) {
    // 按钮点击处理
}
ImGui::End();

// 渲染
ImGui::Render();
ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
```

### 进阶用法
```cpp
// 停靠窗口
ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

// 嵌套窗口
ImGui::Begin("Parent Window");
if (ImGui::BeginChild("Child Region", ImVec2(200, 100))) {
    ImGui::Text("Child content");
    ImGui::Button("Child Button");
}
ImGui::EndChild();
ImGui::End();

// 表格
if (ImGui::BeginTable("MyTable", 3)) {
    ImGui::TableSetupColumn("Name");
    ImGui::TableSetupColumn("Age");
    ImGui::TableSetupColumn("Score");
    ImGui::TableHeadersRow();

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0); ImGui::Text("Alice");
    ImGui::TableSetColumnIndex(1); ImGui::Text("25");
    ImGui::TableSetColumnIndex(2); ImGui::Text("95");

    ImGui::EndTable();
}

// 树形视图
if (ImGui::TreeNode("Root")) {
    ImGui::Text("Child 1");
    ImGui::Text("Child 2");
    if (ImGui::TreeNode("Subtree")) {
        ImGui::Text("Nested item");
        ImGui::TreePop();
    }
    ImGui::TreePop();
}
```

### 资源管理
- **创建**：`ImGui::CreateContext()`
- **释放**：`ImGui::DestroyContext()`
- **最佳实践**：
  - 程序启动时创建 Context
  - 程序退出时销毁 Context
  - 使用 RAII 包装器自动管理生命周期

### 错误处理
```cpp
// ImGui 不使用异常，通过返回值处理错误
bool opened = true;
if (ImGui::Begin("Window", &opened)) {
    // 窗口内容
}
ImGui::End();

// 检查窗口是否被关闭
if (!opened) {
    // 清理资源
}

// 检查控件状态
if (ImGui::Button("Action")) {
    // 执行操作
}
```

---

## 与本项目集成要点

### 集成步骤
1. **添加源文件**：将 `imgui.cpp`、`imgui_draw.cpp`、`imgui_widgets.cpp`、`imgui_tables.cpp` 添加到项目
2. **添加后端**：添加 `imgui_impl_glfw.cpp` 和 `imgui_impl_opengl3.cpp`
3. **配置 SConstruct**：更新构建脚本以包含 ImGui 源文件
4. **初始化**：在 `Window::Init()` 中初始化 ImGui
5. **渲染循环**：在主循环中调用 ImGui 的渲染函数

### 配置要求
- **编译选项**：`-std=c++17`
- **链接库**：无（静态链接）
- **头文件路径**：`include/imgui/`
- **定义宏**：`IMGUI_IMPL_OPENGL_LOADER_GLAD`（使用 GLAD）

### 常见陷阱
- ⚠️ **Context 管理**：确保只创建一个 Context，多线程需要独立 Context
- ⚠️ **渲染顺序**：必须在 OpenGL 清除缓冲区之前调用 `ImGui::NewFrame()`
- ⚠️ **输入处理**：确保后端正确捕获 GLFW 输入事件
- ⚠️ **ID 冲突**：相同标签的控件会自动生成相同 ID，使用 `PushID()`/`PopID()` 解决
- ⚠️ **内存分配**：ImGui 使用自定义内存分配器，不要直接 new/delete ImGui 对象

### 性能建议
- 减少控件数量，避免在循环中创建大量控件
- 使用 `BeginChild()` 分隔复杂界面
- 避免频繁的字符串操作（使用 `TextUnformatted()`）
- 启用 `io.ConfigFlags |= ImGuiConfigFlags_EnableLowRefreshMode` 降低刷新率
- 使用 `PushStyleVar()` 批量设置样式

---

## 学习路径

### 入门（必需）
1. 掌握即时模式渲染的概念
2. 理解 Context、IO、Style 的作用
3. 学会创建基本窗口和控件（Button、Text、Slider）
4. 掌握主循环的渲染流程

### 进阶（推荐）
1. 深入学习停靠窗口（Docking）功能
2. 理解控件 ID 生成机制
3. 掌握表格（Table）和树形视图（TreeNode）
4. 学会自定义样式和主题
5. 理解绘制命令（DrawList）和自定义渲染

### 精通（可选）
1. 研究 ImGui 的内存管理和性能优化
2. 掌握自定义控件和插件开发
3. 探索多窗口和多线程支持
4. 学习 ImGui 的调试和分析工具

---

## 参考资源
- **官方文档**：https://github.com/ocornut/imgui
- **Wiki**：https://github.com/ocornut/imgui/wiki
- **演示程序**：https://github.com/ocornut/imgui/tree/master/examples
- **OpenGL 示例**：`include/imgui/examples/example_glfw_opengl3/`
- **教程**：https://pthom.github.io/imgui_manual_online/

---

## 实际应用示例

### 示例 1：创建调试面板
```cpp
void ShowDebugPanel() {
    ImGui::Begin("Debug Panel");

    // FPS 显示
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

    // 场景统计
    ImGui::Separator();
    ImGui::Text("Scene Statistics");
    ImGui::Text("Meshes: %d", meshCount);
    ImGui::Text("Lights: %d", lightCount);

    // 性能监控
    ImGui::Separator();
    ImGui::Text("Performance");
    ImGui::PlotLines("Frame Time", frameTimes, IM_ARRAYSIZE(frameTimes));

    ImGui::End();
}
```

### 示例 2：对象属性编辑器
```cpp
void ShowObjectEditor(std::shared_ptr<StaticMesh> mesh) {
    ImGui::Begin("Object Properties");

    // 位置编辑
    ImGui::Text("Position");
    glm::vec3 pos = mesh->GetLocation();
    if (ImGui::SliderFloat("X", &pos.x, -10.0f, 10.0f)) mesh->SetLocation(pos);
    if (ImGui::SliderFloat("Y", &pos.y, -10.0f, 10.0f)) mesh->SetLocation(pos);
    if (ImGui::SliderFloat("Z", &pos.z, -10.0f, 10.0f)) mesh->SetLocation(pos);

    // 旋转编辑
    ImGui::Text("Rotation");
    glm::vec3 rot = mesh->GetRotation();
    if (ImGui::SliderFloat("Pitch", &rot.x, 0.0f, 360.0f)) mesh->SetRotation(rot);
    if (ImGui::SliderFloat("Yaw", &rot.y, 0.0f, 360.0f)) mesh->SetRotation(rot);
    if (ImGui::SliderFloat("Roll", &rot.z, 0.0f, 360.0f)) mesh->SetRotation(rot);

    // 缩放编辑
    ImGui::Text("Scale");
    glm::vec3 scale = mesh->GetScale();
    if (ImGui::SliderFloat("Scale X", &scale.x, 0.1f, 5.0f)) mesh->SetScale(scale);
    if (ImGui::SliderFloat("Scale Y", &scale.y, 0.1f, 5.0f)) mesh->SetScale(scale);
    if (ImGui::SliderFloat("Scale Z", &scale.z, 0.1f, 5.0f)) mesh->SetScale(scale);

    ImGui::End();
}
```

### 示例 3：光照控制面板
```cpp
void ShowLightControl(DirLight& light) {
    ImGui::Begin("Light Control");

    // 光照方向
    ImGui::Text("Direction");
    glm::vec3 dir = light.GetDirection();
    if (ImGui::SliderFloat("Dir X", &dir.x, -1.0f, 1.0f)) light.SetDirection(dir);
    if (ImGui::SliderFloat("Dir Y", &dir.y, -1.0f, 1.0f)) light.SetDirection(dir);
    if (ImGui::SliderFloat("Dir Z", &dir.z, -1.0f, 1.0f)) light.SetDirection(dir);

    // 光照颜色
    ImGui::Text("Colors");
    glm::vec3 ambient = light.GetAmbient();
    if (ImGui::ColorEdit3("Ambient", &ambient[0])) light.SetAmbient(ambient);

    glm::vec3 diffuse = light.GetDiffuse();
    if (ImGui::ColorEdit3("Diffuse", &diffuse[0])) light.SetDiffuse(diffuse);

    glm::vec3 specular = light.GetSpecular();
    if (ImGui::ColorEdit3("Specular", &specular[0])) light.SetSpecular(specular);

    ImGui::End();
}
```

---

## 总结

Dear ImGui 是一个强大而灵活的即时模式 GUI 库，特别适合用于：
- 开发工具和调试器
- 游戏编辑器
- 性能分析工具
- 实时参数调整

其即时模式的设计理念使得 UI 代码简洁直观，与 OpenGL 等图形 API 的集成也非常方便。通过掌握本文档中的核心概念和使用模式，您可以在 LearnOpenGL 项目中快速集成 ImGui，创建功能丰富的调试和开发工具。