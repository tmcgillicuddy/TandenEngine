//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef HWENGINE_METADATA_H
#define HWENGINE_METADATA_H

#include <string>

namespace TandenEngine {
    enum DataType
    {
        SCENE = 10,
        PREFAB = 1,
        MATERIAL = 2,
        MODEL = 3,
        AUDIO = 4,
        IMAGE = 5,
        SHADER = 6
    };

    class MetaData {
        friend class Serilizer;
    public: //TODO make private
        MetaData() {mGuid = reinterpret_cast<uint32_t>(this); }
        std::string mFileDir;
        uint32_t mGuid;

        DataType mFileType;

        std::string ConvertToString();
    };
}

#endif //HWENGINE_METADATA_H
