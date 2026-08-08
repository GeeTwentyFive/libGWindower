cmake_minimum_required(VERSION 3.30...4.4)
project(GWindower)
set(CMAKE_CXX_EXTENSIONS OFF)

option(GWINDOWER_BUILD_EXAMPLE "Build example program" ON)

add_library(${PROJECT_NAME}
	"GWindower.cpp"
)
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_WAYLAND ON CACHE BOOL "" FORCE)
set(GLFW_BUILD_X11 OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_LIBRARY_TYPE "OBJECT" CACHE STRING "" FORCE)
add_subdirectory("libs/glfw")
target_link_libraries(${PROJECT_NAME} glfw)

if (GWINDOWER_BUILD_EXAMPLE)
        add_subdirectory(_EXAMPLE)
endif()
