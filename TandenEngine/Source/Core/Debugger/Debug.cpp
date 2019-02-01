//
// Created by Thomas on 1/24/2019.
//

#include "Debug.h"
#include <iostream>
#include<stdarg.h>

namespace TandenEngine {

    std::vector<std::string> Debug::buffer;

    void Debug::Log(char* input, ...) {
        std::string finalMessage = "";

        buffer.push_back(finalMessage); //Add input to buffer
        std::cout << input <<std::endl; //Output to console
    }

    void Debug::LogError(std::string input) {
        buffer.push_back(input); //Add input to buffer
        std::cout << input <<std::endl; //Output to console
    }

    void Debug::DumpBuffer() {
        //Open log file

        for(std::string msg : buffer)
        {
            //Append to log file
        }
        //Close file

        //Clear buffer
    }
}