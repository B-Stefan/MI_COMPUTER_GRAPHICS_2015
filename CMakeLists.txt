project("GLFW3_Demo_with_CMake")
cmake_minimum_required(VERSION 2.8.8)

add_subdirectory(Aufgabe1)

# GLFW3 ist ein Sonderfall und man muss Xcode sagen wie es GLFW3 findet.
if(CMAKE_GENERATOR STREQUAL Xcode)
  message(STATUS "INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
  include_directories(${CMAKE_INSTALL_PREFIX}/include)
  set (CMAKE_EXE_LINKER_FLAGS "-L${CMAKE_INSTALL_PREFIX}/lib")    # the same as "Library Search Paths"
endif()

add_executable(GLFW3_Demo ${SOURCES})
target_link_libraries(GLFW3_Demo ${LIBRARIES}) # link against all libs