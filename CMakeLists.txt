# header
cmake_minimum_required	(VERSION 2.6)
project			(Cplusplus_OpenGL)

# SDL2
include			(FindPkgConfig)
pkg_search_module	(SDL2 REQUIRED sdl2)
pkg_search_module	(SDL2_image REQUIRED SDL2_image)

find_package		(GLEW REQUIRED)
find_package		(GLUT REQUIRED)

set	(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -ggdb -g3 -pipe")

# local libraries
add_library		(utilities utilities.cpp)
add_library		(logger Logger.cpp)
add_library		(objloader ObjLoader.cpp)
add_library		(image Image.cpp)
add_library		(object Object.cpp)

# link
target_link_libraries	(image utilities)
target_link_libraries	(image SDL2_image)
target_link_libraries	(object image)
target_link_libraries	(objloader logger object)

# main executable
add_executable		(main main.cpp)
target_link_libraries	(main utilities logger objloader)
target_link_libraries	(main GLU glut GLEW GL SDL2 SDL2_image)
