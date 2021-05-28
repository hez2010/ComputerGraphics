cmake_minimum_required (VERSION 3.15)

project (Assignment0)

find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)
find_package(OpenGL REQUIRED)

add_executable (Assignment0 "main.cpp" "shader.cpp" "texture.cpp")
target_link_libraries(Assignment0 glfw)
target_link_libraries(Assignment0 glad::glad)
target_link_libraries(Assignment0 OpenGL::GL)
