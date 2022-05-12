cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)

set(PROJECT_NAME TestOpenGL2)

project(${PROJECT_NAME})
add_executable(
	${PROJECT_NAME} 
	source/main.cpp
	source/Renderer/ShaderProgramm.cpp
	source/Renderer/ShaderProgramm.h
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(linking/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(linking/glad)
target_link_libraries(${PROJECT_NAME} glad)