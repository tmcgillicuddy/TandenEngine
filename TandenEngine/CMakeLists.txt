cmake_minimum_required(VERSION 3.6.2)

#-DCMAKE_SH="CMAKE_SH-NOTFOUND"

project(TandenEngine)

set(CMAKE_CXX_STANDARD 17)

# Only necessary under Windows
include_directories("$ENV{VULKAN_SDK}/include")

# Disable glfw Documentation, Tests and Examples
# Disable glfw Documentation, Tests and Examples
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(IMGUI_DIR "Libraries/imgui")
set(IMGUI_SOURCES ${IMGUI_DIR}/imgui.cpp ${IMGUI_DIR}/imgui_demo.cpp ${IMGUI_DIR}/imgui_draw.cpp ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/examples/imgui_impl_vulkan.h ${IMGUI_DIR}/examples/imgui_impl_vulkan.cpp ${IMGUI_DIR}/examples/imgui_impl_glfw.h ${IMGUI_DIR}/examples/imgui_impl_glfw.cpp)

option(TANDENEXE "Wheter to build as exe or not" 1)

if(TANDENEXE)
    message("Building as EXE")
    #Get all the source and header files from the main source code dir
    file(GLOB_RECURSE TANDEN_SOURCE "Source/*.h" "Source/*.cpp")

    #Put all the source file dirs into their proper place
    add_executable(TandenEngine ${TANDEN_SOURCE} ${IMGUI_SOURCES})
else()
    message("Building as LIB")
    add_library(TandenEngine
        ./Source/Core/Debugger/Debug.cpp
        ./Source/Core/Debugger/Debug.h
        ./Source/Core/EventSystem/EventListener.cpp
        ./Source/Core/EventSystem/EventListener.h
        ./Source/Core/EventSystem/Events/Event.cpp
        ./Source/Core/EventSystem/Events/Event.h
        ./Source/Core/EventSystem/Events/KeyboardEvent.cpp
        ./Source/Core/EventSystem/Events/KeyboardEvent.h
        ./Source/Core/EventSystem/EventSystem.cpp
        ./Source/Core/EventSystem/EventSystem.h
        ./Source/Core/Input/Input.cpp
        ./Source/Core/Input/Input.h
        ./Source/Core/Input/Keyboard.cpp
        ./Source/Core/Input/Keyboard.h
        ./Source/Core/Math/Color.cpp
        ./Source/Core/Math/Color.h
        ./Source/Core/Math/Matrices/mat2.cpp
        ./Source/Core/Math/Matrices/mat2.h
        ./Source/Core/Math/Matrices/mat3.cpp
        ./Source/Core/Math/Matrices/mat3.h
        ./Source/Core/Math/Matrices/mat4.cpp
        ./Source/Core/Math/Matrices/mat4.h
        ./Source/Core/Math/NilsMath.cpp
        ./Source/Core/Math/NilsMath.h
        ./Source/Core/Math/UUID.cpp
        ./Source/Core/Math/UUID.h
        ./Source/Core/Math/Vectors/vec2.cpp
        ./Source/Core/Math/Vectors/vec2.h
        ./Source/Core/Math/Vectors/vec3.cpp
        ./Source/Core/Math/Vectors/vec3.h
        ./Source/Core/Math/Vectors/vec4.cpp
        ./Source/Core/Math/Vectors/vec4.h
        ./Source/Core/Math/Vectors/VectorHashing.h
        ./Source/Core/Timer/Timer.cpp
        ./Source/Core/Timer/Timer.h
        ./Source/Engine/Engine.cpp
        ./Source/Engine/Engine.h
        ./Source/Engine/Entity/Components/Audio/AudioListener.cpp
        ./Source/Engine/Entity/Components/Audio/AudioListener.h
        ./Source/Engine/Entity/Components/Audio/AudioSource.cpp
        ./Source/Engine/Entity/Components/Audio/AudioSource.h
        ./Source/Engine/Entity/Components/Component.cpp
        ./Source/Engine/Entity/Components/Component.h
        ./Source/Engine/Entity/Components/ComponentHeader.h
        ./Source/Engine/Entity/Components/Physics/BoxCollider.cpp
        ./Source/Engine/Entity/Components/Physics/BoxCollider.h
        ./Source/Engine/Entity/Components/Physics/CapsuleCollider.cpp
        ./Source/Engine/Entity/Components/Physics/CapsuleCollider.h
        ./Source/Engine/Entity/Components/Physics/Collider.cpp
        ./Source/Engine/Entity/Components/Physics/Collider.h
        ./Source/Engine/Entity/Components/Physics/MeshCollider.cpp
        ./Source/Engine/Entity/Components/Physics/MeshCollider.h
        ./Source/Engine/Entity/Components/Physics/ParticleSystem.cpp
        ./Source/Engine/Entity/Components/Physics/ParticleSystem.h
        ./Source/Engine/Entity/Components/Physics/PhysicsComponent.cpp
        ./Source/Engine/Entity/Components/Physics/PhysicsComponent.h
        ./Source/Engine/Entity/Components/Physics/RigidBody.cpp
        ./Source/Engine/Entity/Components/Physics/RigidBody.h
        ./Source/Engine/Entity/Components/Physics/SphereCollider.cpp
        ./Source/Engine/Entity/Components/Physics/SphereCollider.h
        ./Source/Engine/Entity/Components/Rendering/Camera.cpp
        ./Source/Engine/Entity/Components/Rendering/Camera.h
        ./Source/Engine/Entity/Components/Rendering/LightComponent.cpp
        ./Source/Engine/Entity/Components/Rendering/LightComponent.h
        ./Source/Engine/Entity/Components/Rendering/MeshFilter.cpp
        ./Source/Engine/Entity/Components/Rendering/MeshFilter.h
        ./Source/Engine/Entity/Components/Rendering/MeshRenderer.cpp
        ./Source/Engine/Entity/Components/Rendering/MeshRenderer.h
        ./Source/Engine/Entity/Components/Rendering/Renderer.cpp
        ./Source/Engine/Entity/Components/Rendering/Renderer.h
        ./Source/Engine/Entity/Components/Rendering/SpriteRenderer.cpp
        ./Source/Engine/Entity/Components/Rendering/SpriteRenderer.h
        ./Source/Engine/Entity/Components/Rendering/MaterialComp.cpp
        ./Source/Engine/Entity/Components/Rendering/MaterialComp.h
        ./Source/Engine/Entity/Components/Transform.cpp
        ./Source/Engine/Entity/Components/Transform.h
        ./Source/Engine/Entity/GameObject.cpp
        ./Source/Engine/Entity/GameObject.h
        ./Source/Engine/Game.h
        ./Source/Engine/PhysicsSystem/PhysicsSystem.cpp
        ./Source/Engine/PhysicsSystem/PhysicsSystem.h
        ./Source/Engine/PhysicsSystem/RayTracing/Medium.cpp
        ./Source/Engine/PhysicsSystem/RayTracing/Medium.h
        ./Source/Engine/PhysicsSystem/RayTracing/Ray.cpp
        ./Source/Engine/PhysicsSystem/RayTracing/Ray.h
        ./Source/Engine/PhysicsSystem/RayTracing/RayDifferential.cpp
        ./Source/Engine/PhysicsSystem/RayTracing/RayDifferential.h
        ./Source/Engine/PhysicsSystem/RayTracing/RayHit.cpp
        ./Source/Engine/PhysicsSystem/RayTracing/RayHit.h
        ./Source/Engine/RenderingSystem/GUI/GUIElements/Buttons/Button.cpp
        ./Source/Engine/RenderingSystem/GUI/GUIElements/Buttons/Button.h
        ./Source/Engine/RenderingSystem/GUI/GUIElements/Buttons/Checkbox.cpp
        ./Source/Engine/RenderingSystem/GUI/GUIElements/Buttons/Checkbox.h
        ./Source/Engine/RenderingSystem/GUI/GUIElements/Buttons/RadioButton.cpp
        ./Source/Engine/RenderingSystem/GUI/GUIElements/Buttons/RadioButton.h
        ./Source/Engine/RenderingSystem/GUI/GUIElements/Formatting/BeginMenuBar.cpp
        ./Source/Engine/RenderingSystem/GUI/GUIElements/Formatting/BeginMenuBar.h
        ./Source/Engine/RenderingSystem/GUI/GUIElements/Formatting/EndMenuBar.cpp
        ./Source/Engine/RenderingSystem/GUI/GUIElements/Formatting/EndMenuBar.h
        ./Source/Engine/RenderingSystem/GUI/GUIElements/Formatting/Menu.cpp
        ./Source/Engine/RenderingSystem/GUI/GUIElements/Formatting/Menu.h
        ./Source/Engine/RenderingSystem/GUI/GUIElements/Formatting/MenuItem.cpp
        ./Source/Engine/RenderingSystem/GUI/GUIElements/Formatting/MenuItem.h
        ./Source/Engine/RenderingSystem/GUI/GUIElements/GUIElement.cpp
        ./Source/Engine/RenderingSystem/GUI/GUIElements/GUIElement.h
        ./Source/Engine/RenderingSystem/GUI/GUIElements/GUIHeader.h
        ./Source/Engine/RenderingSystem/GUI/GUIElements/GUIWindow.cpp
        ./Source/Engine/RenderingSystem/GUI/GUIElements/GUIWindow.h
        ./Source/Engine/RenderingSystem/GUI/GUIElements/InputField/FloatField.cpp
        ./Source/Engine/RenderingSystem/GUI/GUIElements/InputField/FloatField.h
        ./Source/Engine/RenderingSystem/GUI/GUIElements/InputField/IntField.cpp
        ./Source/Engine/RenderingSystem/GUI/GUIElements/InputField/IntField.h
        ./Source/Engine/RenderingSystem/GUI/GUIElements/InputField/TextField.cpp
        ./Source/Engine/RenderingSystem/GUI/GUIElements/InputField/TextField.h
        ./Source/Engine/RenderingSystem/GUI/GUIElements/Sliders/FloatSlider.cpp
        ./Source/Engine/RenderingSystem/GUI/GUIElements/Sliders/FloatSlider.h
        ./Source/Engine/RenderingSystem/GUI/GUIElements/Sliders/IntSlider.cpp
        ./Source/Engine/RenderingSystem/GUI/GUIElements/Sliders/IntSlider.h
        ./Source/Engine/RenderingSystem/GUI/GUIElements/Util/ColorEditor.cpp
        ./Source/Engine/RenderingSystem/GUI/GUIElements/Util/ColorEditor.h
        ./Source/Engine/RenderingSystem/GUI/GUIElements/Util/ProgressBar.cpp
        ./Source/Engine/RenderingSystem/GUI/GUIElements/Util/ProgressBar.h
        ./Source/Engine/RenderingSystem/GUI/GUIElements/Util/Text.cpp
        ./Source/Engine/RenderingSystem/GUI/GUIElements/Util/Text.h
        ./Source/Engine/RenderingSystem/GUI/GUIElements/Util/ToolTip.cpp
        ./Source/Engine/RenderingSystem/GUI/GUIElements/Util/ToolTip.h
        ./Source/Engine/RenderingSystem/GUI/GUISystem.cpp
        ./Source/Engine/RenderingSystem/GUI/GUISystem.h
        ./Source/Engine/RenderingSystem/GUI/ComponentGUI.cpp
        ./Source/Engine/RenderingSystem/LightBehaviors/LightBehavior.cpp
        ./Source/Engine/RenderingSystem/LightBehaviors/LightBehavior.h
        ./Source/Engine/RenderingSystem/RayTracingSystem.cpp
        ./Source/Engine/RenderingSystem/RayTracingSystem.h
        ./Source/Engine/RenderingSystem/RenderingSystem.cpp
        ./Source/Engine/RenderingSystem/RenderingSystem.h
        ./Source/Engine/RenderingSystem/VulkanInfo.cpp
        ./Source/Engine/RenderingSystem/VulkanInfo.h
        ./Source/Engine/RenderingSystem/Window.cpp
        ./Source/Engine/RenderingSystem/Window.h
        ./Source/Engine/ResourceManager/BufferManager/BufferManager.cpp
        ./Source/Engine/ResourceManager/BufferManager/BufferManager.h
        ./Source/Engine/ResourceManager/BufferManager/Buffer.cpp
        ./Source/Engine/ResourceManager/BufferManager/Buffer.h
        ./Source/Engine/ResourceManager/MetaData.cpp
        ./Source/Engine/ResourceManager/MetaData.h
        ./Source/Engine/ResourceManager/ResourceManager.cpp
        ./Source/Engine/ResourceManager/ResourceManager.h
        ./Source/Engine/ResourceManager/Resources/AudioClip.cpp
        ./Source/Engine/ResourceManager/Resources/AudioClip.h
        ./Source/Engine/ResourceManager/Resources/Font.cpp
        ./Source/Engine/ResourceManager/Resources/Font.h
        ./Source/Engine/ResourceManager/Resources/Image.cpp
        ./Source/Engine/ResourceManager/Resources/Image.h
        ./Source/Engine/ResourceManager/Resources/Material.cpp
        ./Source/Engine/ResourceManager/Resources/Material.h
        ./Source/Engine/ResourceManager/Resources/Model/CubeModel.cpp
        ./Source/Engine/ResourceManager/Resources/Model/CubeModel.h
        ./Source/Engine/ResourceManager/Resources/Model/CylinderModel.cpp
        ./Source/Engine/ResourceManager/Resources/Model/CylinderModel.h
        ./Source/Engine/ResourceManager/Resources/Model/MeshVertex.cpp
        ./Source/Engine/ResourceManager/Resources/Model/MeshVertex.h
        ./Source/Engine/ResourceManager/Resources/Model/Model.cpp
        ./Source/Engine/ResourceManager/Resources/Model/Model.h
        ./Source/Engine/ResourceManager/Resources/Model/Primitive.cpp
        ./Source/Engine/ResourceManager/Resources/Model/Primitive.h
        ./Source/Engine/ResourceManager/Resources/Model/SphereModel.cpp
        ./Source/Engine/ResourceManager/Resources/Model/SphereModel.h
        ./Source/Engine/ResourceManager/Resources/Prefab.cpp
        ./Source/Engine/ResourceManager/Resources/Prefab.h
        ./Source/Engine/ResourceManager/Resources/Resource.cpp
        ./Source/Engine/ResourceManager/Resources/Resource.h
        ./Source/Engine/ResourceManager/Resources/ResourceHeader.h
        ./Source/Engine/ResourceManager/Resources/Scene.cpp
        ./Source/Engine/ResourceManager/Resources/Scene.h
        ./Source/Engine/ResourceManager/Resources/Shader.cpp
        ./Source/Engine/ResourceManager/Resources/Shader.h
        ./Source/Engine/Serialization/ProjectSettings.cpp
        ./Source/Engine/Serialization/ProjectSettings.h
        ./Source/Engine/Serialization/Serializer.cpp
        ./Source/Engine/Serialization/Serializer.h
        ./Source/main.cpp
      )
    endif()
#Add imgui library
include_directories("Libraries/imgui")
include_directories("Libraries/imgui/examples")

#Add glfw headers
include_directories("Libraries/GLFW/include")

add_subdirectory("Libraries/GLFW")

#Include Math lib headers
include_directories("Source/Core/Math")

#Include Debug header
include_directories("Source/Core/Debugger")

#Link GLFW
target_link_libraries(TandenEngine glfw)

#Link the SDK using GLFW's macros
target_link_libraries(TandenEngine ${VULKAN_LIBRARY})
#locate GLM
#find_package(glm REQUIRED)

#Link the SDK using GLFW's macros

#link glm
#target_link_libraries(TandenEngine glm)

#Include stb headers
include_directories("Libraries/stb")

#Link tinyobj library
add_subdirectory(Libraries/tinyobjloader)
target_link_libraries(TandenEngine tinyobjloader)
if (${CMAKE_SYSTEM_NAME} MATCHES "CYGWIN")
    #Locate the Vulkan SDKs
    target_link_libraries(${PROJECT_NAME} "$ENV{VULKAN_SDK}/Lib/vulkan-1.lib")


    target_link_libraries(${PROJECT_NAME} stdc++fs)
elseif(TANDENEXE)
    message("Building on VS")
    #Locate the Vulkan SDKs
    find_package(Vulkan REQUIRED)

    #Link the SDK using GLFW's macros
    target_link_libraries(TandenEngine ${VULKAN_LIBRARY})
endif()
#Export Important content files
file(COPY  ./ContentFiles
        DESTINATION ${CMAKE_BINARY_DIR}/ )

