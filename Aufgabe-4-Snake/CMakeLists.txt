
set(TASK4_LIBS
    ${TASK4_LIBS}
    ${LIBRARIES_GLOBAL}
    PARENT_SCOPE
)

set(TASK4_SOURCES
    ${TASK4_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GlObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Point.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Rectangle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Cuboid.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Snake.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SnakeHead.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SnakePart.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ScorePrinter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sphere.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Triangle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TriangleCuboid.cpp
    # add new source files here
    ${CMAKE_CURRENT_SOURCE_DIR}/Playground.cpp
	PARENT_SCOPE
)
