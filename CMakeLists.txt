project("GLFW3_Demo_with_CMake")
cmake_minimum_required(VERSION 2.8.8)


#Setup compiler and c++ version
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/_cmake/SetupGLFW.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/_cmake/SetupGlut.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/_cmake/SetupOpenGl.cmake)


#Setup global libs
set(LIBRARIES_GLOBAL
    ${LIBRARIES_GLOBAL}
    ${GLFW_STATIC_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARIES}
    # add other libs here
    # ${OPENGL_LIBRARIES} sind nach dem find_package() definiert.
)

# Add sub projects
add_subdirectory(_lib)
add_subdirectory(Aufgabe1)
add_subdirectory(Aufgabe2)

add_executable(GLFW3_Demo ${TASK1_SOURCES})
target_link_libraries(GLFW3_Demo ${TASK1_LIBS}) # link against all libs

add_executable(GLFW3_Demo_Aufgabe2 ${TASK2_SOURCES})
target_link_libraries(GLFW3_Demo_Aufgabe2 ${TASK2_LIBS}) # link against all libs