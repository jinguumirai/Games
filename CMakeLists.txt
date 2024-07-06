cmake_minimum_required(VERSION 3.12)

project(Alien_invasion)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(OpenCV REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})
file(GLOB sources *.cpp *.hpp)
add_executable(Alien_invasion glad.c ${sources})
target_link_libraries(${PROJECT_NAME} ${OpenGL_LIBRARIES} ${OpenCV_LIBS} glfw dl)