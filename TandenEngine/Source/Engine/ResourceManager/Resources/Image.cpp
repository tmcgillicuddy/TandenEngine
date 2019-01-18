//
// Created by thomas.mcgillicuddy on 11/3/2018.
//

#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <vulkan/vulkan.h>

namespace TandenEngine {

    Image::Image() {
        mResourceType = ResourceType::IMAGE;
    }

    Image::Image(MetaData * inputMeta) {
        mResourceType = ResourceType::IMAGE;
        mMetaData = inputMeta;
        std::cout<<"Reading Meta Data at " << mMetaData->mFileDir;
        createTextureImage();
    }

    bool Image::CheckIfSupported(std::string extension) {
        return (extension == ".jpg" || extension == ".png");
    }

    void Image::createTextureImage() {
        int texWidth, texHeight, texChannels;
        stbi_uc* pixels = stbi_load(mMetaData->mFileDir.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
        VkDeviceSize imageSize = texWidth * texHeight * 4;

        if (!pixels) {
            throw std::runtime_error("failed to load texture image!");
        }
    }


}
