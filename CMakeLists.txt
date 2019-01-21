cmake_minimum_required(VERSION 3.12)
project(Vastness)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
link_libraries(libsoil glew32s libglfw3 gdi32 opengl32)

add_compile_definitions(GLEW_STATIC)

add_executable(
        Vastness
        main.cpp
        Engine/Shader.cpp Engine/Shader.hpp
        Engine/Mesh.cpp Engine/Mesh.hpp
        Engine/AssetLoader.cpp Engine/AssetLoader.hpp
        Engine/Screen.hpp
        Engine/Transform.cpp Engine/Transform.hpp
        Engine/VectorsAndMatrices.hpp Engine/VectorsAndMatrices.cpp
        Engine/Input.cpp Engine/Input.hpp
        Engine/Renderer.cpp Engine/Renderer.hpp
        Engine/Collections/Array.hpp
        Engine/Camera.cpp Engine/Camera.hpp
        Engine/SceneLoader.hpp
        Engine/Actor.hpp
        Engine/Light.hpp

        Game/PlayerController.cpp Game/PlayerController.hpp
        Game/FishController.cpp Game/FishController.hpp
        Engine/Collections/Dictionary.hpp
        Engine/StringOperations.cpp Engine/StringOperations.hpp
        Engine/Scene.cpp Engine/Scene.hpp
        Engine/SceneLoader.cpp
)


