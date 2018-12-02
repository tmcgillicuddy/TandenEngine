//
// Created by thomas.mcgillicuddy on 11/3/2018.
//

#include "Image.h"

TandenEngine::Image::Image(): Resource(ResourceType::IMAGE) {

}

bool TandenEngine::Image::CheckIfSupported(std::string extension) {
    return (extension == ".jpg"||extension == ".png");
}
