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

# GLFW3 ist ein Sonderfall und man muss Xcode sagen wie es GLFW3 findet.
if(CMAKE_GENERATOR STREQUAL Xcode)
  message(STATUS "INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
  include_directories(${CMAKE_INSTALL_PREFIX}/include)
  set (CMAKE_EXE_LINKER_FLAGS "-L${CMAKE_INSTALL_PREFIX}/lib")    # the same as "Library Search Paths"
endif()


# include GLFW3
include_directories(${GLFW_INCLUDE_DIRS})


