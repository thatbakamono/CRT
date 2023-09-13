cmake_minimum_required(VERSION 3.26)

project(CRT)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_subdirectory(thirdparty)

add_executable(
        CRT
        src/CRT.cpp src/gfx/Shader.cpp src/gfx/ShaderStage.cpp src/gfx/Texture2D.cpp src/math/Ray.cpp
)
target_include_directories(CRT PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(CRT PRIVATE glad glfw glm imgui imgui-glfw imgui-opengl)

if (MSVC)
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /O2 /Oi /Ot /Oy /GL")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /Oi /Ot /Oy /GL")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG")
endif()
