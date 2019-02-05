//
// Created by thomas.mcgillicuddy on 12/3/2018.
//

#ifndef TANDENENGINE_FONT_H
#define TANDENENGINE_FONT_H

#include "./Resource.h"
#include "../MetaData.h"

namespace TandenEngine {
    class Font : public Resource {
     public:
        Font();
        Font(MetaData* metaData);
        static bool CheckIfSupported(std::string extension);
    };
}  // namespace TandenEngine

#endif  // TANDENENGINE_FONT_H
