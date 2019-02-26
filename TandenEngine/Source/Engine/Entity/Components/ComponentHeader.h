//
// Created by thomas.mcgillicuddy on 12/7/2018.
//

#ifndef TANDENENGINE_COMPONENTHEADER_H
#define TANDENENGINE_COMPONENTHEADER_H

#include <unordered_map>

#include "Component.h"
#include "Transform.h"
#include "Audio/AudioListener.h"
#include "Audio/AudioSource.h"
#include "Physics/BoxCollider.h"
#include "Physics/SphereCollider.h"
#include "Physics/CapsuleCollider.h"
#include "Physics/MeshCollider.h"
#include "Physics/ParticleSystem.h"
#include "Physics/RigidBody.h"
#include "Rendering/MeshRenderer.h"
#include "Rendering/Camera.h"
#include "Rendering/LightComponent.h"
#include "Rendering/MeshFilter.h"
#include "Rendering/SpriteRenderer.h"

namespace TandenEngine {
    const std::unordered_map<ComponentType, const char *> CompNamesMap = {
            {ComponentType::AUDIOLISTENER,   "Audio Listener"},
            {ComponentType::AUDIOSOURCE,     "Audio Source"},
            {ComponentType::BOXCOLLIDER,     "Box Collider"},
            {ComponentType::SPHERECOLLIDER,  "Sphere Collider"},
            {ComponentType::CAPSULECOLLIDER, "Capsule Collider"},
            {ComponentType::MESHCOLLIDER,    "Mesh Collider"},
            {ComponentType::RIGIDBODY,       "Rigidbody"},
            {ComponentType::PARTICLESYSTEM,  "Particle System"},
            {ComponentType::CAMERA,          "Camera"},
            {ComponentType::LIGHTCOMPONENT,  "Light"},
            {ComponentType::MESHFILTER,      "Mesh Filter"},
            {ComponentType::SPRITERENDERER,  "Sprite Renderer"},
            {ComponentType::MESHRENDERER,    "Mesh Renderer"}
    };

//Function to check if a string is substring, case insensitive
    static size_t FindCaseInsensitive(std::string data, std::string toSearch, size_t pos = 0) {
        // Convert both strings to lowercase
        std::transform(data.begin(), data.end(), data.begin(), ::tolower);
        std::transform(toSearch.begin(), toSearch.end(), toSearch.begin(), ::tolower);

        // Regular find
        return data.find(toSearch, pos);
    }

}  // namespace TandenEngine

#endif  // TANDENENGINE_COMPONENTHEADER_H
