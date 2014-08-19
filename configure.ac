AC_PREREQ([2.69])
AC_INIT([COG], [0.0.0], [https://github.com/tharvik/COG/issues])
AM_INIT_AUTOMAKE([-Wall foreign])
AC_CONFIG_SRCDIR([Shader.h])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])

# To show some warnings
AM_MAINTAINER_MODE

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_MAKE_SET

# Check for C++11
m4_include([m4/ax_cxx_compile_stdcxx_11.m4])
AX_CXX_COMPILE_STDCXX_11([],[mandatory])

# Checks for libraries.
# Workaround for Apple
if test "$(uname -s)" = "Darwin"
then
	LDFLAGS="-framework OpenGL -framework GLUT ${LDFLAGS}"
else
	AC_SEARCH_LIBS([glBindTexture], [GL],
		       [], [AC_MSG_ERROR([Unable to find an OpenGL implementation])])
	AC_SEARCH_LIBS([gluPerspective], [GLU],
		       [], [AC_MSG_ERROR([Unable to find an OpenGL utility (GLU) implementation])])
	AC_SEARCH_LIBS([glutGet], [glut],
		       [], [AC_MSG_ERROR([Unable to find an OpenGL utility toolkit (GLUT) implementation])])
	AC_SEARCH_LIBS([glewInit], [GLEW],
		       [], [AC_MSG_ERROR([Unable to find an OpenGL extention wrangler (GLEW) implementation])])
fi

# Checks for header files.
AC_CHECK_HEADERS([memory.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([atexit memset pow sqrt strtol])

# Define
AC_DEFINE([WINDOW_WIDTH], [800], [Width of the window])
AC_DEFINE([WINDOW_HEIGHT], [450], [Height of the window])
AC_DEFINE([FULLSCREEN], [false], [Set to true if the game initial start in fullscreen])
AC_DEFINE([MIDDLE_SCREEN_X], [(glutGet(GLUT_SCREEN_WIDTH ) - WINDOW_WIDTH ) / 2], [TODO])
AC_DEFINE([MIDDLE_SCREEN_Y], [(glutGet(GLUT_SCREEN_HEIGHT) - WINDOW_HEIGHT) / 2], [TODO])

AC_DEFINE([FOV], [70.00], [TODO])
AC_DEFINE([NEAREST], [0.10], [TODO])
AC_DEFINE([FAREST], [1000.00], [TODO])

AC_DEFINE([MINIMUM_PPS], [25], [Minimum threshold where a lag occure])
AC_DEFINE([REPORT_PPS], [50], [TODO])
AC_DEFINE([REPORT_FPS], [50], [TODO])

AC_DEFINE([BACKGROUND_COLOR], [0.16F, 0.16F, 0.16F, 1], [Color of the background])
AC_DEFINE([KEY_REPEAT_PERIOD], [40], [Time between every check of keys])

AC_DEFINE([INITIAL_POSITION_X], [1.2F], [Initial position of the camera, x value])
AC_DEFINE([INITIAL_POSITION_Y], [1.2F], [Initial position of the camera, y value])
AC_DEFINE([INITIAL_POSITION_Z], [1.2F], [Initial position of the camera, z value])
AC_DEFINE([INITIAL_ORIENTATION_X], [-1], [Initial rotation of the camera, x value])
AC_DEFINE([INITIAL_ORIENTATION_Y], [-1], [Initial rotation of the camera, y value])
AC_DEFINE([INITIAL_ORIENTATION_Z], [-1], [Initial rotation of the camera, z value])

AC_DEFINE([ANGLE_PER_ROTATION], [0.1F], [Step of rotation for one strike of a rotation key])
AC_DEFINE([ANGLE_PER_PHYSIC], [ANGLE_PER_ROTATION], [TODO])
AC_DEFINE([DISTANCE_PER_MOVE], [0.30F], [Step of movement for one strike of a move key])
AC_DEFINE([DISTANCE_PER_PHYSIC], [DISTANCE_PER_MOVE], [TODO])

AC_DEFINE([LOAD_FROM], ["Resources/objects/"], [Path to load objects from])

AC_DEFINE([MESH_LEVEL_DISTANCES], [5.0F, 50.0F, 100.0F, 200.0F, 500.0f], [Distance for each level of detail of mesh])

AC_DEFINE([LOGGER_LEVEL], [0], [Minimum level of message to show in logs; TODO: have to be move to runtime variable])

AC_DEFINE([DELTA], [0.000001F], [Smallest value to differentiate two floats])

# Output
AC_OUTPUT
