//
// Created by thomas.mcgillicuddy on 12/3/2018.
//

#include "Font.h"

namespace TandenEngine {

    Font::Font() {
        mResourceType = ResourceType::FONT;
    }

    bool Font::CheckIfSupported(std::string extension) {
        return (extension == ".ttf");
    }

    Font::Font(MetaData *metaData) {
    }
}  // namespace TandenEngine
