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
        std::string mFileDir;
        std::string mFileType;
    };

}

#endif //HWENGINE_METADATA_H
