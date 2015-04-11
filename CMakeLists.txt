project("GLFW3_Demo_with_CMake")
cmake_minimum_required(VERSION 2.8.8)

# OpenGL
find_package(OpenGL REQUIRED)
IF(NOT OPENGL_FOUND)
    MESSAGE(FATAL_ERROR
      "OpenGL not found."
    )
ENDIF()

# include OpenGL
include_directories(${OPENGL_INCLUDE_DIR})

# GLFW3
# GLFW3 ist ein Sondefall und kann nicht mit normalen find_package gefunden werden.
# Es wird hierfür PkgConfig benötigt.
find_package(PkgConfig REQUIRED)
IF(NOT PKGCONFIG_FOUND)
    MESSAGE(
      FATAL_ERROR
        "PkgConfig not found."
    )
ENDIF()

pkg_search_module(GLFW REQUIRED glfw3)
IF(NOT GLFW_FOUND)
    MESSAGE(
      FATAL_ERROR
        "GLFW3 not found"
      )
ENDIF()
# include GLFW3
include_directories(${GLFW_INCLUDE_DIRS})

set(LIBRARIES_GLOBAL
    ${LIBRARIES_GLOBAL}
    ${GLFW_STATIC_LIBRARIES}
    ${OPENGL_LIBRARIES}
    # add other libs here
    # ${OPENGL_LIBRARIES} sind nach dem find_package() definiert.
    ${CMAKE_CURRENT_SOURCE_DIR}/_lib/vec3.cpp
)


add_subdirectory(Aufgabe1)
add_subdirectory(Aufgabe2)

# GLFW3 ist ein Sonderfall und man muss Xcode sagen wie es GLFW3 findet.
if(CMAKE_GENERATOR STREQUAL Xcode)
  message(STATUS "INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
  include_directories(${CMAKE_INSTALL_PREFIX}/include)
  set (CMAKE_EXE_LINKER_FLAGS "-L${CMAKE_INSTALL_PREFIX}/lib")    # the same as "Library Search Paths"
endif()

add_executable(GLFW3_Demo ${TASK1_SOURCES})
target_link_libraries(GLFW3_Demo ${TASK1_LIBS}) # link against all libs

add_executable(GLFW3_Demo_Aufgabe2 ${TASK2_SOURCES})
target_link_libraries(GLFW3_Demo_Aufgabe2 ${TASK2_LIBS}) # link against all libs