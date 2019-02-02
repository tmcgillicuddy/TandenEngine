//
// Created by Thomas on 1/24/2019.
//

#ifndef TANDENENGINE_DEBUG_H
#define TANDENENGINE_DEBUG_H

#include <vector>

namespace TandenEngine {

    class Debug {
        static std::vector<std::string> buffer;
    public:
        static void Log(char* format, ...); //Basic log API
        static void LogError(char* format, ...);
        static void DumpBuffer(); //Dump buffer to log file //TODO call from seperate thread

    private:
        static std::string LogVector(char type, va_list arg);
        static std::string LogMatrix(char type, va_list arg);
    };

}
#endif //TANDENENGINE_DEBUG_H
