//
// Created by thomas.mcgillicuddy on 11/3/2018.
//

#include "Shader.h"

TandenEngine::Shader::Shader(): Resource(ResourceType::SHADER) {

}

bool TandenEngine::Shader::CheckIfSupported(std::string extension) {
    return (extension == ".glsl" || extension == ".fs"|| extension == ".vs"|| extension == ".gs");
}
