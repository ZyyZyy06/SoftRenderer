﻿# CMakeList.txt: SoftRender 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 将源代码添加到此项目的可执行文件。
add_executable (SoftRender "src/main.cpp"     "include/main.h" "include/Config.h"   "src/MathUtils/Vector.cpp" "include/Global.h"      "src/MathUtils/Matrix.cpp"   "include/Camera.h" "include/Object.h"   "src/Project/Mesh.cpp"     "projects/defaultProject.cpp" "include/Light.h" "src/MathUtils/Algorithm.cpp" "include/Algorithm.h" "src/Project/Object.cpp" "include/Math.h" "include/Render.h" "src/Display/WindowBuffer.cpp" "include/Buffer.h"  "src/Render/Render.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SoftRender PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
