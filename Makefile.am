bin_PROGRAMS	= COG
COG_SOURCES	= Camera.cpp Game.cpp Light.cpp Material.cpp Mesh.cpp		\
		  Object.cpp Planet.cpp Shader.cpp Renderer.cpp Texture.cpp	\
		  Universe.cpp eventHandler.cpp main.cpp			\
		  utilities.cpp stb_image.c Event.cpp KeyboardEvent.cpp		\
		  MouseEvent.cpp GUI.cpp Point.cpp RefreshEvent.cpp		\
		  								\
		  Camera.h Game.h Light.h Logger.h Material.h Mesh.h Object.h	\
		  Planet.h Shader.h Renderer.h Texture.h Universe.h 		\
		  config.h eventHandler.h opengl.h stb_image.h utilities.h	\
		  Event.h KeyboardEvent.h MouseEvent.h GUI.h Point.h		\
		  RefreshEvent.h rapidxml/rapidxml.hpp				\		
		  rapidxml/rapidxml_iterators.hpp rapidxml/rapidxml_print.hpp
AM_CXXFLAGS	= -I /usr/include/bullet
datadir		= $(datarootdir)/@PACKAGE_NAME@
nobase_dist_data_DATA =	Resources/objects/house/AO.jpg

uninstall-local:
	rm -rf $(datadir)
