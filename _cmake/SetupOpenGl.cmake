find_package(OpenGL REQUIRED)
IF(NOT OPENGL_FOUND)
    MESSAGE(FATAL_ERROR
      "OpenGL not found."
    )
ENDIF()

# include OpenGL
include_directories(${OPENGL_INCLUDE_DIR})