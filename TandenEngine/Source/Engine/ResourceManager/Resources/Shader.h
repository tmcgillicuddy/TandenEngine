//
// Created by thomas.mcgillicuddy on 11/3/2018.
//

#ifndef TANDENENGINE_SHADER_H
#define TANDENENGINE_SHADER_H

#include "Resource.h"

#include <vulkan/vulkan.h>

namespace TandenEngine {

    class Shader : public Resource{
     public:
        VkShaderModule shaderData;
        Shader();
        Shader(MetaData * metaData);
        static bool CheckIfSupported(std::string extension);

     private:
        VkShaderModule CreateShaderModule(const std::vector<char>& code);
    };
}  // namespace TandenEngine

#endif  // TANDENENGINE_SHADER_H
