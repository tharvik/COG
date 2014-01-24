cmake_minimum_required	(VERSION 2.6)
project			(Cplusplus_OpenGL)

#find_package		(SDL2)
find_package		(GLEW)
find_package		(GLUT)

add_library		(utilities utilities.cpp)
add_library		(logger logger.cpp)
add_library		(obj_loader obj_loader.cpp)
add_library		(images Images.cpp)
add_library		(object object.cpp)

target_link_libraries	(images utilities)
target_link_libraries	(obj_loader logger)
target_link_libraries	(obj_loader object)

add_executable		(main main.cpp)
target_link_libraries	(main utilities images logger obj_loader)
target_link_libraries	(main GLU glut GLEW GL SDL2)

set			(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -ggdb -g3 -pipe")
