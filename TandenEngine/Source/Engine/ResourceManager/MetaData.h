//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef HWENGINE_METADATA_H
#define HWENGINE_METADATA_H

#include <string>

namespace TandenEngine {
    enum DataType
    {
        SCENE,
        MATERIAL,
        MODEL,
        AUDIO,
        IMAGE,
        SHADER
    };

    class MetaData {
        friend class Serilizer;
    public: //TODO make private
        MetaData() {mGuid = reinterpret_cast<uint32_t>(this); }
        std::string mFileDir;
        uint32_t mGuid;



        DataType mFileType;
    };
}

#endif //HWENGINE_METADATA_H
