
set(TASK4_LIBS
    ${TASK4_LIBS}
    ${LIBRARIES_GLOBAL}
    PARENT_SCOPE
)

set(TASK4_SOURCES
    ${TASK4_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    # add new source files here
    ${CMAKE_CURRENT_SOURCE_DIR}/Playground.cpp
	PARENT_SCOPE
)
