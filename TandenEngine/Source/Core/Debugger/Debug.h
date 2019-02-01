//
// Created by Thomas on 1/24/2019.
//

#ifndef TANDENENGINE_DEBUG_H
#define TANDENENGINE_DEBUG_H

#include <string>
#include <vector>

namespace TandenEngine {

    class Debug {
        static std::vector<std::string> buffer;
    public:
        static void Log(char* format, ...); //Basic log API
        static void LogError(std::string input);
        static void DumpBuffer(); //Dump buffer to log file //TODO call from seperate thread
    };

}

#endif //TANDENENGINE_DEBUG_H
