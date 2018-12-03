cmake_minimum_required(VERSION 3.12)
project(TandenEngine)

set(CMAKE_CXX_STANDARD 17)

# Only necessary under Windows
include_directories("$ENV{VULKAN_SDK}/include")

# Disable glfw Documentation, Tests and Examples
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_executable(TandenEngine Source/main.cpp Source/Engine/Entity/GameObject.cpp Source/Engine/Entity/GameObject.h Source/Engine/Entity/Components/Component.cpp Source/Engine/Entity/Components/Component.h Source/Engine/ResourceManager/Resources/Scene.cpp Source/Engine/ResourceManager/Resources/Scene.h Source/Engine/Entity/Components/Transform.cpp Source/Engine/Entity/Components/Transform.h Source/Core/Math/Vector4.cpp Source/Core/Math/Vector4.h Source/Core/Input/Input.cpp Source/Core/Input/Input.h Source/Core/Input/Keyboard.cpp Source/Core/Input/Keyboard.h Source/Engine/Engine.cpp Source/Engine/Engine.h Source/Core/Timer/Timer.cpp Source/Core/Timer/Timer.h Source/Core/EventSystem/EventSystem.cpp Source/Core/EventSystem/EventSystem.h Source/Core/EventSystem/Events/Event.cpp Source/Core/EventSystem/Events/Event.h Source/Core/EventSystem/EventListener.cpp Source/Core/EventSystem/EventListener.h Source/Core/EventSystem/Events/KeyboardEvent.cpp Source/Core/EventSystem/Events/KeyboardEvent.h Source/Core/Math/Vector3.cpp Source/Core/Math/Vector3.h Source/Engine/Serialization/Serializer.cpp Source/Engine/Serialization/Serializer.h Source/Engine/Serialization/ProjectSettings.cpp Source/Engine/Serialization/ProjectSettings.h Source/Engine/ResourceManager/MetaData.cpp Source/Engine/ResourceManager/MetaData.h Source/Engine/ResourceManager/Resources/Resource.cpp Source/Engine/ResourceManager/Resources/Resource.h Source/Engine/Entity/Components/Renderer.cpp Source/Engine/Entity/Components/Renderer.h Source/Engine/Entity/Components/MeshFilter.cpp Source/Engine/Entity/Components/MeshFilter.h Source/Engine/Entity/Components/MeshRenderer.cpp Source/Engine/Entity/Components/MeshRenderer.h Source/Engine/Entity/Components/SpriteRenderer.cpp Source/Engine/Entity/Components/SpriteRenderer.h Source/Engine/ResourceManager/Resources/Model/Model.cpp Source/Engine/ResourceManager/Resources/Model/Model.h Source/Engine/ResourceManager/Resources/Model/MeshVertex.cpp Source/Engine/ResourceManager/Resources/Model/MeshVertex.h Source/Core/Math/Vector2.cpp Source/Core/Math/Vector2.h Source/Engine/RenderingSystem/RenderingSystem.cpp Source/Engine/RenderingSystem/RenderingSystem.h Source/Engine/PhysicsSystem/PhysicsSystem.cpp Source/Engine/PhysicsSystem/PhysicsSystem.h Source/Engine/Entity/Components/PhysicsComponent.cpp Source/Engine/Entity/Components/PhysicsComponent.h Source/Engine/ResourceManager/ResourceManager.cpp Source/Engine/ResourceManager/ResourceManager.h Source/Engine/ResourceManager/Resources/Prefab.cpp Source/Engine/ResourceManager/Resources/Prefab.h Source/Engine/ResourceManager/Resources/Material.cpp Source/Engine/ResourceManager/Resources/Material.h Source/Engine/ResourceManager/Resources/AudioClip.cpp Source/Engine/ResourceManager/Resources/AudioClip.h Source/Engine/ResourceManager/Resources/Image.cpp Source/Engine/ResourceManager/Resources/Image.h Source/Engine/ResourceManager/Resources/Shader.cpp Source/Engine/ResourceManager/Resources/Shader.h Source/Core/Math/UUID.cpp Source/Core/Math/UUID.h Source/Core/Math/NilsMath.h Source/Core/Math/NilsMath.cpp Source/Core/Math/Matrix3.h Source/Core/Math/Matrix4.h Source/Engine/ResourceManager/Resources/Font.cpp Source/Engine/ResourceManager/Resources/Font.h)

#GLFW Build through CMake (Loads and links Vulkan as well)
add_subdirectory("Libraries/GLFW" )

target_link_libraries(TandenEngine glfw)

find_package(Vulkan REQUIRED)

target_link_libraries(TandenEngine ${VULKAN_LIBRARY})