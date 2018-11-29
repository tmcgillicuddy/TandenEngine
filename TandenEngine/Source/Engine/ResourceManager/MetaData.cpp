//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#include "MetaData.h"

namespace TandenEngine {

    std::string MetaData::ConvertToString() {
        std::string data = "";
        data += mFileDir+ '\n';
        data += mGuid + '\n';
        data += mFileType + '\n';

        return data;
    }
}