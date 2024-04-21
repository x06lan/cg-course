cmake_minimum_required(VERSION 3.16)
project(cg-course)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# this two line don't work new.
set(INCLUDE_FILE)
set(SRC_FILES)
add_subdirectory(thirdparty/freeglut)
find_package(OpenGL REQUIRED)

# you need pre-install OpenGL, GLU, please google
set(INCLUDE_FILES
    ${INCLUDE_DIR}/stb_image.h
    ${INCLUDE_DIR}/obj.h
)
set(SRC_FILES
)


add_executable(${PROJECT_NAME}
    ${SRC_DIR}/main.cpp
    ${INCLUDE_FILES}
    ${SRC_FILES}
)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${OPENGL_glu_LIBRARY})
target_link_libraries(${PROJECT_NAME} freeglut)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/thirdparty/freeglut/include/GL
    ${INCLUDE_DIR})