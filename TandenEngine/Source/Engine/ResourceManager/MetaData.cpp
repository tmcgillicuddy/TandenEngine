//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#include "MetaData.h"
#include <iostream>
namespace TandenEngine {

    std::string MetaData::ConvertToString() {
        std::string data = "";
        data += mFileDir+ '\n';
        data += mGuid + '\n';
        std::cout<< "Converting " + (int)mFileType;
        data += (int)mFileType + '\n';

        return data;
    }
}