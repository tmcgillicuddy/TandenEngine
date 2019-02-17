//
// Created by Thomas on 1/24/2019.
//

#ifndef TANDENENGINE_DEBUG_H
#define TANDENENGINE_DEBUG_H

#include <vulkan/vulkan.h>
#include <string>
#include <vector>

namespace TandenEngine {

    class Debug {
        static std::vector<std::string> buffer;
     public:
        static void Log(char* format, ...);  // Basic log API
        static void LogError(char* format, ...);
        // TODO(Anyone) call from seperate thread
        static void DumpBuffer();   // Dump buffer to log file
        static void CheckVKResult(VkResult res);

     private:
        static std::string LogVector(char type, va_list arg);
        static std::string LogMatrix(char type, va_list arg);
        static std::string GetErrorString(VkResult res);
    };
}  // namespace TandenEngine

#endif  // TANDENENGINE_DEBUG_H
