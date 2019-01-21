cmake_minimum_required(VERSION 3.12)
project(TandenEngine)

set(CMAKE_CXX_STANDARD 17)

# Only necessary under Windows
include_directories("$ENV{VULKAN_SDK}/include")

# Disable glfw Documentation, Tests and Examples
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(IMGUI_DIR "Libraries/imgui")
set(IMGUI_SOURCES ${IMGUI_DIR}/imgui.cpp ${IMGUI_DIR}/imgui_demo.cpp ${IMGUI_DIR}/imgui_draw.cpp ${IMGUI_DIR}/imgui_widgets.cpp)

add_library(TandenEngine
        Source/Core/EventSystem/EventListener.cpp
        Source/Core/EventSystem/Events/Event.cpp
        Source/Core/EventSystem/Events/KeyboardEvent.cpp
        Source/Core/EventSystem/EventSystem.cpp
        Source/Core/Input/Input.cpp
        Source/Core/Input/Keyboard.cpp
        Source/Core/Math/Color.cpp
        Source/Core/Math/NilsMath.cpp
        Source/Core/Math/UUID.cpp
        Source/Core/Math/Vectors/Vector2.cpp
        Source/Core/Math/Vectors/Vector3.cpp
        Source/Core/Math/Vectors/Vector4.cpp
        Source/Core/Timer/Timer.cpp
        Source/Engine/Engine.cpp
        Source/Engine/Entity/Components/Audio/AudioListener.cpp
        Source/Engine/Entity/Components/Audio/AudioSource.cpp
        Source/Engine/Entity/Components/Component.cpp
        Source/Engine/Entity/Components/Physics/BoxCollider.cpp
        Source/Engine/Entity/Components/Physics/CapsuleCollider.cpp
        Source/Engine/Entity/Components/Physics/Collider.cpp
        Source/Engine/Entity/Components/Physics/MeshCollider.cpp
        Source/Engine/Entity/Components/Physics/ParticleSystem.cpp
        Source/Engine/Entity/Components/Physics/PhysicsComponent.cpp
        Source/Engine/Entity/Components/Physics/RigidBody.cpp
        Source/Engine/Entity/Components/Physics/SphereCollider.cpp
        Source/Engine/Entity/Components/Rendering/Camera.cpp
        Source/Engine/Entity/Components/Rendering/LightComponent.cpp
        Source/Engine/Entity/Components/Rendering/MeshFilter.cpp
        Source/Engine/Entity/Components/Rendering/MeshRenderer.cpp
        Source/Engine/Entity/Components/Rendering/Renderer.cpp
        Source/Engine/Entity/Components/Rendering/SpriteRenderer.cpp
        Source/Engine/Entity/Components/Transform.cpp
        Source/Engine/Entity/GameObject.cpp
        Source/Engine/PhysicsSystem/Medium.cpp
        Source/Engine/PhysicsSystem/PhysicsSystem.cpp
        Source/Engine/PhysicsSystem/Ray.cpp
        Source/Engine/PhysicsSystem/RayDifferential.cpp
        Source/Engine/RenderingSystem/GUI/GUIElements/Buttons/Button.cpp
        Source/Engine/RenderingSystem/GUI/GUIElements/Buttons/Checkbox.cpp
        Source/Engine/RenderingSystem/GUI/GUIElements/Buttons/RadioButton.cpp
        Source/Engine/RenderingSystem/GUI/GUIElements/Formatting/BeginMenuBar.cpp
        Source/Engine/RenderingSystem/GUI/GUIElements/Formatting/EndMenuBar.cpp
        Source/Engine/RenderingSystem/GUI/GUIElements/Formatting/Menu.cpp
        Source/Engine/RenderingSystem/GUI/GUIElements/Formatting/MenuItem.cpp
        Source/Engine/RenderingSystem/GUI/GUIElements/GUIElement.cpp
        Source/Engine/RenderingSystem/GUI/GUIElements/InputField/FloatField.cpp
        Source/Engine/RenderingSystem/GUI/GUIElements/InputField/IntField.cpp
        Source/Engine/RenderingSystem/GUI/GUIElements/InputField/TextField.cpp
        Source/Engine/RenderingSystem/GUI/GUIElements/Sliders/FloatSlider.cpp
        Source/Engine/RenderingSystem/GUI/GUIElements/Sliders/IntSlider.cpp
        Source/Engine/RenderingSystem/GUI/GUIElements/Util/ColorEditor.cpp
        Source/Engine/RenderingSystem/GUI/GUIElements/Util/ProgressBar.cpp
        Source/Engine/RenderingSystem/GUI/GUIElements/Util/Text.cpp
        Source/Engine/RenderingSystem/GUI/GUIElements/Util/ToolTip.cpp
        Source/Engine/RenderingSystem/GUI/GUISystem.cpp
        Source/Engine/RenderingSystem/RenderingSystem.cpp
        Source/Engine/RenderingSystem/Window.cpp
        Source/Engine/ResourceManager/MetaData.cpp
        Source/Engine/ResourceManager/ResourceManager.cpp
        Source/Engine/ResourceManager/Resources/AudioClip.cpp
        Source/Engine/ResourceManager/Resources/Font.cpp
        Source/Engine/ResourceManager/Resources/Image.cpp
        Source/Engine/ResourceManager/Resources/Material.cpp
        Source/Engine/ResourceManager/Resources/Model/MeshVertex.cpp
        Source/Engine/ResourceManager/Resources/Model/Model.cpp
        Source/Engine/ResourceManager/Resources/Prefab.cpp
        Source/Engine/ResourceManager/Resources/Resource.cpp
        Source/Engine/ResourceManager/Resources/Scene.cpp
        Source/Engine/ResourceManager/Resources/Shader.cpp
        Source/Engine/Serialization/ProjectSettings.cpp
        Source/Engine/Serialization/Serializer.cpp
        Source/main.cpp
        ${IMGUI_SOURCES}
        )

#Add imgui library
include_directories("Libraries/imgui")

#Add glfw headers
include_directories("Libraries/GLFW/include")

#Get all the source and header files from the main source code dir
file(GLOB_RECURSE TANDEN_SOURCE "Source/*.h" "Source/*.cpp")

#Put all the source file dirs into their proper place
#add_executable(TandenEngine ${TANDEN_SOURCE} ${IMGUI_SOURCES})

#Include Math lib headers
include_directories("Source/Core/Math")

#Link GLFW
target_link_libraries(TandenEngine glfw)

#Locate the Vulkan SDKs
find_package(Vulkan REQUIRED)

#Link the SDK using GLFW's macros
target_link_libraries(TandenEngine ${VULKAN_LIBRARY})

#Link tinyobj library
include_directories(Libraries/tinyobjloader)
add_subdirectory(Libraries/tinyobjloader)
target_link_libraries(TandenEngine tinyobjloader)

#Export Important content files
file(COPY  ${CMAKE_SOURCE_DIR}/ContentFiles
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/ )
