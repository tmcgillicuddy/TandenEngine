//
// Created by thomas.mcgillicuddy on 11/3/2018.
//

#ifndef TANDENENGINE_AUDIOCLIP_H
#define TANDENENGINE_AUDIOCLIP_H

#include "./Resource.h"
#include "../MetaData.h"

namespace TandenEngine {

    class AudioClip : public Resource {
    public:
        AudioClip();
        AudioClip(MetaData* metaData);
        static bool CheckIfSupported(std::string extension);
    };

}

#endif //TANDENENGINE_AUDIOCLIP_H
