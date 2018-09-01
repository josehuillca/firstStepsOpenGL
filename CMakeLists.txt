cmake_minimum_required(VERSION 3.10)
project(firstStepsOpenGL)

set(CMAKE_CXX_STANDARD 11)

find_package (OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package (GLEW REQUIRED STATIC)

if (APPLE)
    include_directories(/usr/local/include)
endif (APPLE)

add_executable(firstStepsOpenGL main.cpp ShaderCode.cpp ShaderCode.h)
target_link_libraries(firstStepsOpenGL
        glfw
        ${GLEW_LIBRARY}
        ${OPENGL_LIBRARIES})