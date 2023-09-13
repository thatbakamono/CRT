add_subdirectory(glad)
add_subdirectory(glfw)
add_subdirectory(glm)

add_library(imgui imgui/imgui.cpp imgui/imgui_demo.cpp imgui/imgui_draw.cpp imgui/imgui_tables.cpp imgui/imgui_widgets.cpp)
target_include_directories(imgui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/imgui")

add_library(imgui-glfw imgui/backends/imgui_impl_glfw.cpp)
target_include_directories(imgui-glfw PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends")
target_link_libraries(imgui-glfw PUBLIC imgui glfw)

add_library(imgui-opengl imgui/backends/imgui_impl_opengl3.cpp)
target_include_directories(imgui-opengl PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends")
target_link_libraries(imgui-opengl PUBLIC imgui)
