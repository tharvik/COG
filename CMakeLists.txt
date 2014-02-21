# header
cmake_minimum_required	(VERSION 2.6)
project			(Cplusplus_OpenGL)

#find_package		(SDL2)
find_package		(GLEW)
find_package		(GLUT)

set		(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -ggdb -g3 -pipe")
set			(CMAKE_CXX_COMPILER "clang")

# local libraries
add_library		(utilities utilities.cpp)
add_library		(logger Logger.cpp)

add_library		(object Object.cpp)

add_library		(univers Univers.cpp)
add_library		(camera Camera.cpp)
add_library		(eventHandler eventHandler.cpp)
add_library		(simulator Simulator.cpp)
add_library		(sphere Sphere.cpp)
add_library		(light Light.cpp)
add_library		(vector Vvector.cpp)
add_library		(game Game.cpp)

add_library		(texture Texture.cpp)
add_library		(shader Shader.cpp)
add_library		(pixelsGenerator PixelsGenerator.cpp)
add_library		(textureManager TextureManager.cpp)
add_library		(mesh Mesh.cpp)
add_library		(meshManager MeshManager.cpp)
add_library		(objectManager ObjectManager.cpp)
add_library		(shaderManager ShaderManager.cpp)
add_library		(stb stb_image.c)

add_library		(component Component.cpp)

# link
target_link_libraries	(object texture shader mesh)

target_link_libraries	(univers camera sphere light objectManager object)
target_link_libraries	(camera utilities m)
target_link_libraries	(light vector)
target_link_libraries	(game univers simulator eventHandler)

target_link_libraries	(textureManager texture stb)
target_link_libraries	(texture SDL2_image logger pixelsGenerator)
target_link_libraries	(shader GL GLU glut GLEW)

target_link_libraries	(objectManager meshManager textureManager shaderManager)
target_link_libraries	(meshManager stdc++)
target_link_libraries	(shaderManager shader)

# main executable
add_executable		(main main.cpp)
target_link_libraries	(main logger univers eventHandler simulator)
target_link_libraries	(main textureManager game object)
target_link_libraries	(main GLU glut GLEW GL SDL2)
