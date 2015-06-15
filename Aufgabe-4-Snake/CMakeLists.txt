
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
    # add new source files here
	PARENT_SCOPE
)
