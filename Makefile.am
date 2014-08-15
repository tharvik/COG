bin_PROGRAMS	= COG
COG_SOURCES	= Camera.cpp Component.cpp Game.cpp Light.cpp Logger.cpp	\
		  Material.cpp Mesh.cpp Object.cpp Planet.cpp Shader.cpp	\
		  Simulator.cpp Sphere.cpp Texture.cpp Univers.cpp Vvector.cpp	\
		  eventHandler.cpp main.cpp utilities.cpp stb_image.c		\
		  								\
		  Camera.h Component.h Game.h Light.h Logger.h Material.h	\
		  Mesh.h Object.h Planet.h Shader.h Simulator.h Sphere.h	\
		  Texture.h Univers.h Vvector.h config.h eventHandler.h		\
		  opengl.h stb_image.h utilities.h

datadir		= $(datarootdir)/@PACKAGE_NAME@
nobase_dist_data_DATA =	Resources/fichier_2_objects.obj			\
			Resources/test/objectTest.png			\
			Resources/test/cube.obj				\
			Resources/test/PNM/test_RGB_ASCII.ppm		\
			Resources/test/PNM/test_RGB_Binary.ppm		\
			Resources/test/PNM/test_Gray_ASCII.pgm		\
			Resources/test/PNM/test_BW_ASCII.pbm		\
			Resources/test/PNM/test_ASCII.ppm		\
			Resources/test/PNM/test_Gray_Binary.pgm		\
			Resources/test/PNM/test_BW_Binary.pbm		\
			Resources/test/Mountain3_AO.png			\
			Resources/test/Mountain3.obj			\
			Resources/test/Mountain3_5.obj			\
			Resources/test/Mountain3.png			\
			Resources/test/objectTest.mtl			\
			Resources/test/Mountain3.mtl			\
			Resources/test/BMP/test_Web.bmp			\
			Resources/test/BMP/test_BW.bmp			\
			Resources/test/BMP/test_Palette.bmp		\
			Resources/test/BMP/test_ARGB.bmp		\
			Resources/test/BMP/test_RGB_6.bmp		\
			Resources/test/BMP/test_RGB_3.bmp		\
			Resources/test/BMP/test_Gray.bmp		\
			Resources/test/BMP/test_RGB_0.bmp		\
			Resources/test/BMP/test_XRGB.bmp		\
			Resources/test/BMP/test_RGB_2.bmp		\
			Resources/test/BMP/test_RGB_5.bmp		\
			Resources/test/BMP/test_RGB_4.bmp		\
			Resources/test/BMP/test_RGB_1.bmp		\
			Resources/test/Mountain3c.obj			\
			Resources/test/Mountain3c.mtl			\
			Resources/test/Mountain3d.obj			\
			Resources/test/cube.mtl				\
			Resources/test/objectTest.obj			\
			Resources/test/mountain2.obj			\
			Resources/test/cube.png				\
			Resources/test/JPG/test_RGB_2.jpg		\
			Resources/test/JPG/test_RGB_fast_integer.jpg	\
			Resources/test/JPG/test_RGB_floating_point.jpg	\
			Resources/test/JPG/test_RGB_3.jpg		\
			Resources/test/JPG/test_RGB_1.jpg		\
			Resources/test/JPG/test_RGB_bad_quality.jpg	\
			Resources/test/JPG/test_RGB_4.jpg		\
			Resources/test/JPG/test_Gray.jpg		\
			Resources/test/JPG/test_Palette.jpg		\
			Resources/test/Mountain3b.mtl			\
			Resources/test/PNG/test_PaletteA.png		\
			Resources/test/PNG/test_GrayA.png		\
			Resources/test/PNG/test_RGB.png			\
			Resources/test/PNG/test_Gray.png		\
			Resources/test/PNG/test_RGB_no_compression.png	\
			Resources/test/PNG/test_RGBA.png		\
			Resources/test/PNG/test_RGBA_offset_layer.png	\
			Resources/test/PNG/test_Palette.png		\
			Resources/test/PNG/test_RGBA_interlacing.png	\
			Resources/test/PNG/test_RGBA_no_alpha.png	\
			Resources/test/PNG/test_RGBA_gamma.png		\
			Resources/test/Mountain3b.obj			\
			Resources/test/Mountain3d.mtl			\
			Resources/test/GIF/test_RGB.gif			\
			Resources/test/GIF/test_PaletteA.gif		\
			Resources/test/GIF/test_Gray.gif		\
			Resources/test/GIF/test_RGBA.gif		\
			Resources/test/GIF/test_Palette.gif		\
			Resources/test/GIF/test_GrayA.gif		\
			Resources/test/mountain2.mtl			\
			Resources/test/plane.jpg			\
			Resources/test/Valid_images_format.txt		\
			Resources/test/TIF/test_Gray.tif		\
			Resources/test/TIF/test_RGBA_déflation.tif	\
			Resources/test/TIF/test_RGBA_LZW.tif		\
			Resources/test/TIF/test_RGB.tif			\
			Resources/test/TIF/test_GrayA.tif		\
			Resources/test/TIF/test_Palette.tif		\
			Resources/test/TIF/test_RGBA_pack_bits.tif	\
			Resources/test/TIF/test_RGBA_jpeg.tif		\
			Resources/test/TIF/test_RGBA_no_compression.tif	\
			Resources/test/plane.obj			\
			Resources/shaders/base.fs			\
			Resources/shaders/base.vs			\
			Resources/objects/Torus/up.mesh			\
			Resources/objects/Torus/up.mbf			\
			Resources/objects/Torus/Torus.object		\
			Resources/objects/axe/axe.pShader		\
			Resources/objects/axe/axe.vShader		\
			Resources/objects/axe/axe.mesh			\
			Resources/objects/axe/axe.png			\
			Resources/objects/Suzanne/suzanne.mesh		\
			Resources/objects/Suzanne/Suzanne.object	\
			Resources/objects/Suzanne/suzanne		\
			Resources/objects/mountain/mountain.mesh	\
			Resources/textures/cheveu.png			\
			Resources/materials/ground.mtl			\
			Resources/game_icon.bmp				\
			Resources/planet/terre.fs			\
			Resources/planet/verre.mtl			\
			Resources/planet/terre.vs			\
			Resources/planet/verre.fs


uninstall-local:
	rm -rf $(datadir)
