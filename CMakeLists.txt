# header
cmake_minimum_required	(VERSION 2.6)
project			(Cplusplus_OpenGL)

if(APPLE)
	set		(libs OpenGL glut)
else()
	set		(libs GL GLU glut GLEW)
endif()

set		(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -ggdb -g3 -pipe")
set			(CMAKE_CXX_COMPILER "clang")

# check for libraries
unset(links)
foreach(lib ${libs})
	unset(tmp CACHE)
	find_library	(tmp ${lib})
	if(NOT tmp)
		message(FATAL_ERROR "${lib} not found")
	endif()
	list(APPEND links ${tmp})
endforeach()

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
add_library		(mesh Mesh.cpp)
add_library		(stb stb_image.c)

add_library		(component Component.cpp)

# link
target_link_libraries	(object texture shader mesh stdc++)

target_link_libraries	(univers camera sphere light object)
target_link_libraries	(camera utilities m)
target_link_libraries	(light vector)
target_link_libraries	(game univers simulator eventHandler)

target_link_libraries	(texture logger)
target_link_libraries	(shader ${links})

# main executable
add_executable		(main main.cpp)
target_link_libraries	(main logger univers eventHandler simulator)
target_link_libraries	(main game object stdc++)
target_link_libraries	(main ${links})
