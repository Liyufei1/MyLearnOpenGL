env = Environment(tools=['default', 'compilation_db'])
env.CompilationDatabase('./compile_commands.json')

env.Append(CXXFLAGS=["/std:c++17"])

# # 让 SCons 使用 src/ 作为源码来源，build/ 作为构建输出
env.VariantDir('build', 'src', duplicate=0)

# # 添加 include/ 目录为头文件路径
env.Append(CPPPATH=['include'])

#添加依赖库
env.Append(LIBPATH=['lib'])
env.Append(LIBS=['glfw3_mt','shell32','User32','Gdi32'])

# # 搜集源文件（注意 glad.c 和 CommonFunLib.cpp 也需要加入）
sources = Glob("build/*.cpp") + Glob("build/**/*.cpp")
sources += Glob("include/**/*.cpp") + Glob("include/**/*.c")

# # 编译目标程序
program = env.Program(target='build/app', source=sources)

# Default(program)
