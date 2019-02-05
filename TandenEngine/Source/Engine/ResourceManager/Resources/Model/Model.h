//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef TANDENENGINE_MODEL_H
#define TANDENENGINE_MODEL_H

#include <vulkan/vulkan.h>
#include <vector>

#include "MeshVertex.h"
#include "../Resource.h"
#include "../../MetaData.h"


namespace TandenEngine {

    class Model : public Resource{
     public:
        std::vector<MeshVertex> verticies;
        std::vector<uint32_t> indices;

        VkBuffer  vertexBuffer;
        VkDeviceMemory vertexBufferMemory;

        Model();
        Model(MetaData* inputData);  // Create a model resource from meta data input

        static bool CheckIfSupported(std::string extension);

     private:
<<<<<<< HEAD
        void LoadModel(MetaData* data);
=======
        void LoadModel();
>>>>>>> develop
    };

}  // namespace TandenEngine

<<<<<<< HEAD
#endif  // HWENGINE_MODEL_H
=======
#endif  // TANDENENGINE_MODEL_H
>>>>>>> develop
