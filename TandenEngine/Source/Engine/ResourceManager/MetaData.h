//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef TANDENENGINE_METADATA_H
#define TANDENENGINE_METADATA_H

#include <string>
#include <iostream>

namespace TandenEngine {
    enum ResourceType {
        SCENE = 1,
        PREFAB = 2,
        MATERIAL = 3,
        MODEL = 4,
        AUDIO = 5,
        IMAGE = 6,
        SHADER = 7,
        FONT = 8,
        INVALID = 1000
    };

    class MetaData {
        friend class Serilizer;
     public:  // TODO(Thomas) make private
        MetaData() {
            mGuid = reinterpret_cast<uint32_t>(this);
            mFileType = ResourceType::INVALID;
        }

        std::string mFileDir, mFileName;
        uint32_t mGuid;

        ResourceType mFileType;

        std::string ConvertToString();
    };
}  // namespace TandenEngine

#endif  // TANDENENGINE_METADATA_H
