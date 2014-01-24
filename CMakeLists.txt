cmake_minimum_required	(VERSION 2.6)
project			(Cplusplus_OpenGL)

#find_package		(SDL2)
find_package		(GLEW)
find_package		(GLUT)

add_library		(utilities utilities.cpp)
add_library		(logger logger.cpp)
add_library		(objloader ObjLoader.cpp)
add_library		(image Image.cpp)
add_library		(object Object.cpp)

target_link_libraries	(image utilities)
target_link_libraries	(object image)
target_link_libraries	(objloader logger object)

add_executable		(main main.cpp)
target_link_libraries	(main utilities image logger objloader)
target_link_libraries	(main GLU glut GLEW GL SDL2)

set			(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -ggdb -g3 -pipe")
