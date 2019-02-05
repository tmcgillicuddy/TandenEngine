//
// Created by thomas.mcgillicuddy on 11/3/2018.
//

#ifndef TANDENENGINE_IMAGE_H
#define TANDENENGINE_IMAGE_H

#include <vulkan/vulkan.h>

#include "./Resource.h"
#include "../MetaData.h"

namespace TandenEngine {

    class Image : public Resource {
     public:
        Image();
        Image(MetaData * inputMeta);

        static bool CheckIfSupported(std::string extension);
        VkImageView mTextureImageView;
        VkSampler mTextureSampler;  // Sampling method
     private:
        void CreateTextureImage();  // Loads the file info and creates the base buffers

        // Binds the image data to the vulkan image data type
        void CreateImage(uint32_t width, uint32_t height, VkFormat format,
                VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties,
                VkImage& image, VkDeviceMemory& imageMemory);
    };

}  // namespace TandenEngine

#endif  // TANDENENGINE_IMAGE_H
