//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef TANDENENGINE_MESHRENDERER_H
#define TANDENENGINE_MESHRENDERER_H

#include "Renderer.h"
#include "MeshFilter.h"
#include "../../../ResourceManager/BufferManager/Buffer.h"

namespace TandenEngine {

    class MeshRenderer : public Renderer {
     public:
        Buffer mUniformBuffer;
        VkDescriptorSet mDescriptorSet;

        MeshRenderer();

        ~MeshRenderer();

        std::string ToString() override;

        std::unique_ptr<Component> Clone() override;
        // Takes in some string data and will output a Mesh Renderer object
        Component * ConvertFromString(std::vector<std::string> input) override;

        MeshFilter *mpMesh{};  // Pointer to mesh component to draw (must be on the same gameobject)
    };

}  // namespace TandenEngine

#endif  // TANDENENGINE_MESHRENDERER_H
