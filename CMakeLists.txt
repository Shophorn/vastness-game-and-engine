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
        Engine/Loader.cpp Engine/Loader.hpp
        Engine/Input.cpp Engine/Input.hpp
        Engine/Camera.cpp Engine/Camera.hpp
        Engine/Light.hpp
        Engine/StringOperations.cpp Engine/StringOperations.hpp
        Engine/FileOperations.cpp Engine/FileOperations.hpp
        Engine/Serialization.hpp

        Engine/Maths/Maths.hpp
        Engine/Maths/vector3f.cpp Engine/Maths/vector3f.hpp
        Engine/Maths/matrix4f.cpp Engine/Maths/matrix4f.hpp
        Engine/Maths/vector4f.cpp Engine/Maths/vector4f.hpp
        Engine/Maths/OStreamOperators.cpp Engine/Maths/OStreamOperators.hpp

        Engine/DEBUG.hpp


        Engine/Engine.cpp Engine/Engine.hpp
        Engine/Rendering/RenderManager.cpp Engine/Rendering/RenderManager.hpp
        Engine/ECS/ECS.hpp Engine/ECS/Handle.hpp
        Engine/ECS/Component.hpp
        Engine/ECS/HandleManager.hpp
        Engine/ECS/OstreamOperators.hpp
        Engine/ECS/List.hpp 
        Engine/Rendering/RendererSystem.hpp 
        Engine/ECS.hpp 
        Engine/TransformComponent.hpp 
        Engine/ECSLoader.hpp 
        Engine/Maths/Basic.hpp 
        Engine/Maths/vector2f.hpp 
        Engine/ResourceManager.hpp 
        Engine/Stopwatch.hpp 
        Engine/Resources/Textures.cpp Engine/Resources/Textures.hpp 
        Engine/Resources/Shaders.cpp Engine/Resources/Shaders.hpp 
        Engine/Resources/Meshes.cpp Engine/Resources/Meshes.hpp

        Game/Scripts/PlayerControlSystem.hpp
        Game/Components.hpp
        Game/Scripts/FollowEntitySystem.hpp Engine/Maths/Quaternion.cpp Engine/Maths/Quaternion.hpp)

