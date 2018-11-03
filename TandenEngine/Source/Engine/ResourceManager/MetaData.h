//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef HWENGINE_METADATA_H
#define HWENGINE_METADATA_H

#include <string>

namespace TandenEngine {

    class MetaData {
        friend class Serilizer;
    public: //TODO make private
        MetaData() {mGuid = reinterpret_cast<uint32_t>(this); }
        std::string mFileDir;
        std::string mFileType;
        uint32_t mGuid;
    };

}

#endif //HWENGINE_METADATA_H
