//
// Created by thomas.mcgillicuddy on 11/3/2018.
//

#include "Shader.h"
namespace TandenEngine {


    Shader::Shader(){
        mResourceType = ResourceType::SHADER;
    }

    bool Shader::CheckIfSupported(std::string extension) {
        return (extension == ".glsl" || extension == ".fs" || extension == ".vs" || extension == ".gs");
    }
}
