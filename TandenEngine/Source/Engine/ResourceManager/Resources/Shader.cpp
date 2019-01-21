//
// Created by thomas.mcgillicuddy on 11/3/2018.
//

#include "Shader.h"
#include "../../RenderingSystem/RenderingSystem.h"
namespace TandenEngine {

    Shader::Shader(){
        mResourceType = ResourceType::SHADER;
    }

    Shader::Shader(MetaData *metaData) {
        mResourceType = ResourceType::SHADER;
        std::ifstream file(metaData->mFileDir, std::ios::ate | std::ios::binary);

        if (!file.is_open()) {
            //throw std::runtime_error("failed to open file!");
            std::cout << "failed to open file!" << metaData->mFileDir << std::endl;
        }

        size_t fileSize = (size_t)file.tellg();
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        shaderData = CreateShaderModule(buffer);
    }

    bool Shader::CheckIfSupported(std::string extension) {
        return (extension == ".glsl" || extension == ".fs" || extension == ".vs" || extension == ".gs");
    }

    VkShaderModule Shader::CreateShaderModule(const std::vector<char> &code) {
        VkShaderModuleCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

        VkShaderModule shaderModule;
        if (vkCreateShaderModule(RenderingSystem::GetVulkanInfo()->logicalDevice, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) { //TODO get logical device from rendering system
            throw std::runtime_error("failed to create shader module!");
        }

        return shaderModule;
    }
}
