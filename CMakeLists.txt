cmake_minimum_required(VERSION 3.13)
project(Vastness)

set(LIBRARIES_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIBRARIES_DIRECTORY})

include_directories(${INCLUDE_DIRECTORY})
link_directories(${LIBRARIES_DIRECTORY})

# Build Engine
add_library(engine "")
target_link_libraries(engine libsoil glew32s libglfw3 gdi32 opengl32)
add_compile_definitions(GLEW_STATIC)
add_subdirectory(Engine)
set_target_properties(
	engine
	PROPERTIES 
		PREFIX lib
		OUTPUT_NAME VastnessEngine
		SUFFIX .lib
)	


# Build Game
add_executable(game main.cpp)
target_link_libraries(game libVastnessEngine libsoil glew32s libglfw3 gdi32 opengl32)
add_subdirectory(Game)
set_target_properties (
	game
	PROPERTIES
		OUTPUT_NAME Vastness
)