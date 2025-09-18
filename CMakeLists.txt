cmake_minimum_required(VERSION 3.15)
project(VisLL)

set(CMAKE_CXX_STANDARD 17)

# Find packages
find_package(OpenGL REQUIRED)
# find_package(glfw3 3.3 REQUIRED)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
add_subdirectory(extern/glfw)
#testing

# Add executable with all sources manually listed
add_executable(VisLL
        main.cpp
        linkedlist.h

        # ImGui core
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp

        # ImGui backends
        backend/imgui_impl_glfw.cpp
        backend/imgui_impl_opengl3.cpp
        )

# Include headers
target_include_directories(VisLL PRIVATE
        imgui
        backends
        )

# Link with GLFW and OpenGL
target_link_libraries(VisLL PRIVATE glfw OpenGL::GL)