//
// Created by thomas.mcgillicuddy on 11/3/2018.
//
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Image.h"
#include "../../RenderingSystem/RenderingSystem.h"

namespace TandenEngine {

    Image::Image() {
        mResourceType = ResourceType::IMAGE;
    }

    Image::Image(MetaData *inputMeta) {
        mResourceType = ResourceType::IMAGE;
        mMetaData = inputMeta;
        CreateTextureImage();
    }

    bool Image::CheckIfSupported(std::string extension) {
        return (extension == ".jpg" || extension == ".png" || extension == ".bmp");
    }

    void Image::CreateTextureImage() {
        int texWidth, texHeight, texChannels;
        stbi_uc *pixels = stbi_load(mMetaData->mFileDir.c_str(), &texWidth, &texHeight, &texChannels,
                                    STBI_rgb_alpha); //Load image file data into stb pixels
        VkDeviceSize imageSize = texWidth * texHeight * 4;

        if (!pixels) {
            throw std::runtime_error("failed to load texture image!");
        }

        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;

        //Create a the buffer to hold the texture data
        //CreateBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        //             VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT  //TODO Require create buffer method
        //             | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

        void *data;
        vkMapMemory(RenderingSystem::GetVulkanInfo()->logicalDevice, stagingBufferMemory, 0, imageSize, 0, &data);
        memcpy(data, pixels, static_cast<size_t>(imageSize));
        vkUnmapMemory(RenderingSystem::GetVulkanInfo()->logicalDevice, stagingBufferMemory);

        stbi_image_free(pixels); //Free pixels

        VkImage textureImage;
        VkDeviceMemory textureImageMemory;

        CreateImage(texWidth, texHeight, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_OPTIMAL,
                    VK_IMAGE_USAGE_TRANSFER_DST_BIT
                    | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, textureImage,
                    textureImageMemory);
    }

    void
    Image::CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage,
                       VkMemoryPropertyFlags properties, VkImage &image, VkDeviceMemory &imageMemory) {
        VkImageCreateInfo imageInfo = {};
        imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageInfo.imageType = VK_IMAGE_TYPE_2D;
        imageInfo.extent.width = width;
        imageInfo.extent.height = height;
        imageInfo.extent.depth = 1;
        imageInfo.mipLevels = 1;
        imageInfo.arrayLayers = 1;
        imageInfo.format = format;
        imageInfo.tiling = tiling;
        imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        imageInfo.usage = usage;
        imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if (vkCreateImage(RenderingSystem::GetVulkanInfo()->logicalDevice, &imageInfo, nullptr, &image) !=
            VK_SUCCESS) {
            throw std::runtime_error("failed to create image!");
        }

        //Get memory requirements for image
        VkMemoryRequirements memRequirements;
        vkGetImageMemoryRequirements(RenderingSystem::GetVulkanInfo()->logicalDevice, image,
                                     &memRequirements);

        //Get allocation info for image
        VkMemoryAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        //allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits,
        //                                           properties); //TODO Require find memory type

        if (vkAllocateMemory(RenderingSystem::GetVulkanInfo()->logicalDevice, &allocInfo, nullptr, &imageMemory) !=
            VK_SUCCESS) {
            throw std::runtime_error("failed to allocate image memory!");
        }

        //Bind image to memory device
        vkBindImageMemory(RenderingSystem::GetVulkanInfo()->logicalDevice, image, imageMemory,
                          0);
    }
}  // namespace TandenEngine
