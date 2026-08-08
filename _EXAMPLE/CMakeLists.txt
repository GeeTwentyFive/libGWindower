cmake_minimum_required(VERSION 3.30...4.4)
project(EXAMPLE)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(
	"$<$<CONFIG:Release>:-O2;-march=x86-64-v2>"
	"$<$<CONFIG:Debug>:-O0;-ggdb>"
)

add_executable(${PROJECT_NAME}
	"EXAMPLE.cpp"
)
if (MINGW)
	target_link_options(${PROJECT_NAME} PRIVATE "-mwindows")
endif()

target_link_libraries(${PROJECT_NAME} GWindower)
