# header
cmake_minimum_required	(VERSION 2.6)
project			(Cplusplus_OpenGL)

#find_package		(SDL2)
find_package		(GLEW)
find_package		(GLUT)

set	(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -ggdb -g3 -pipe")

# local libraries
add_library		(logger Logger.cpp)
add_library		(objloader ObjLoader.cpp)
add_library		(texture Texture.cpp)
add_library		(object Object.cpp)
add_library		(univers Univers.cpp)
add_library		(camera Camera.cpp)
add_library		(utilities utilities.cpp)
add_library		(eventHandler eventHandler.cpp)
add_library		(pixelsGenerator PixelsGenerator.cpp)
add_library		(simulator Simulator.cpp)
add_library		(sphere Sphere.cpp)

# link
target_link_libraries	(texture SDL2_image logger pixelsGenerator)
target_link_libraries	(object texture)
target_link_libraries	(camera utilities)
target_link_libraries	(objloader logger object)
target_link_libraries	(univers camera objloader sphere)

# main executable
add_executable		(main main.cpp)
target_link_libraries	(main logger objloader univers eventHandler simulator)
target_link_libraries	(main GLU glut GLEW GL SDL2)
