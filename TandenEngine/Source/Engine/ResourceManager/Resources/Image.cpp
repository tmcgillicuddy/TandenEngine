//
// Created by thomas.mcgillicuddy on 11/3/2018.
//

#include "Image.h"
namespace TandenEngine {

    Image::Image() {
        mResourceType = ResourceType::IMAGE;
    }

    bool Image::CheckIfSupported(std::string extension) {
        return (extension == ".jpg" || extension == ".png");
    }

    Image::Image(MetaData *metaData) {
    }
}
