//
// Created by Thomas on 1/24/2019.
//
#include <assert.h>
#include <stdarg.h>
#include <iostream>
#include <string>

#include "NilsMath.h"
#include "Debug.h"

namespace TandenEngine {

    std::vector<std::string> Debug::buffer;

    void Debug::Log(char* input, ...) {
        std::string finalMessage = "";

        unsigned int i;
        char *s;
        bool b;
        int argCount = 0;
        // Validate input format to not include bad characters
        for (int index = 0; input[index] != '\0'; index++) {
            switch (input[index]) {
                case '%':
                    argCount++;
                    return;
                case '\n':
                    std::cout << "Invalid Format, dont use \\n in format\n";
                    return;
            }
        }

        if(argCount <= 0)
        {
            std::cout << input;  // Output to console
            buffer.push_back(input);  // Add input to buffer
            return;
        }

        // Module 1: Initializing Myprintf's arguments
        va_list arg;
        va_start(arg, input);

        for (int index = 0; input[index] != '\0'; index++) {
            while ( input[index] != '%' ) {
                finalMessage += input[index];
                index++;
            }

            index++;

            // Module 2: Fetching and executing arguments
            switch (input[index]) {
                case 'c' : i = va_arg(arg, int);  // Character Argument
                    finalMessage += i;
                    break;

                case 'd' : i = va_arg(arg, int);  // Decimal Argument
                    if (i < 0) {
                        i = -i;
                        finalMessage += '-';
                    }
                    finalMessage +=i;
                    break;
                case 's': s = va_arg(arg, char *);  // String Argument
                    finalMessage += s;
                    break;
                case 'v':  // Vector Argument
                    index++;
                    finalMessage += LogVector(input[index], arg);
                    break;
                case 'm':  // Matrix Argument
                    index++;
                    finalMessage += LogMatrix(input[index], arg);
                    break;
                case 'n':
                    index++;
                    finalMessage += '\n';
                case 'b':
                    b = va_arg(arg, bool);  // String Argument
                    if(b)
                        finalMessage += "True";
                    else
                        finalMessage += "False";
                    break;
            }
        }

        // Module 3: Closing argument list to necessary clean-up
        va_end(arg);

        std::cout << finalMessage;  // Output to console

        buffer.push_back(finalMessage);  // Add input to buffer
    }

    void Debug::DumpBuffer() {
        // Open log file

        for (std::string msg : buffer) {
            // Append to log file
        }
        // Close file

        // Clear buffer
    }

    std::string Debug::LogVector(char type, va_list arg) {
        vec2 vector2;
        vec3 vector3;
        vec4 vector4;
        switch (type) {
            case '2':
                vector2 = va_arg(arg, vec2);
                return vector2.ToString();
            case '3':
                vector3 = va_arg(arg, vec3);
                return vector3.ToString();
            case '4':
                vector4 = va_arg(arg, vec4);
                return vector4.ToString();
        }
        return "";
    }



    std::string Debug::LogMatrix(char type, va_list arg) {
        mat2 matrix2;
        mat3 matrix3;
        mat4 matrix4;
        switch (type) {
            case '2':
                matrix2 = va_arg(arg, mat2);
                return matrix2.ToString();
            case '3':
                matrix3 = va_arg(arg, mat3);
                return matrix3.ToString();
            case '4':
                matrix4 = va_arg(arg, mat4);
                return matrix4.ToString();
        }

        return "";
    }

    void Debug::LogError(char *format, ...) {
    }

    void Debug::CheckVKResult(VkResult res) {
        if (res != VK_SUCCESS) {
	    	std::cout << ("Fatal : VkResult is \" %s \" in %s at line %d",
	    	        GetErrorString(res).c_str(), __FILE__, __LINE__);
	    	assert(res == VK_SUCCESS);
	    }
    }

    std::string Debug::GetErrorString(VkResult errorCode) {
    switch (errorCode) {
#define STR(r) case VK_ ##r: return #r
        STR(NOT_READY);
        STR(TIMEOUT);
        STR(EVENT_SET);
        STR(EVENT_RESET);
        STR(INCOMPLETE);
        STR(ERROR_OUT_OF_HOST_MEMORY);
        STR(ERROR_OUT_OF_DEVICE_MEMORY);
        STR(ERROR_INITIALIZATION_FAILED);
        STR(ERROR_DEVICE_LOST);
        STR(ERROR_MEMORY_MAP_FAILED);
        STR(ERROR_LAYER_NOT_PRESENT);
        STR(ERROR_EXTENSION_NOT_PRESENT);
        STR(ERROR_FEATURE_NOT_PRESENT);
        STR(ERROR_INCOMPATIBLE_DRIVER);
        STR(ERROR_TOO_MANY_OBJECTS);
        STR(ERROR_FORMAT_NOT_SUPPORTED);
        STR(ERROR_SURFACE_LOST_KHR);
        STR(ERROR_NATIVE_WINDOW_IN_USE_KHR);
        STR(SUBOPTIMAL_KHR);
        STR(ERROR_OUT_OF_DATE_KHR);
        STR(ERROR_INCOMPATIBLE_DISPLAY_KHR);
        STR(ERROR_VALIDATION_FAILED_EXT);
        STR(ERROR_INVALID_SHADER_NV);
#undef STR
        default:
            return "UNKNOWN_ERROR";
    }
}

    void Debug::LogPause(char *input, ...) {
        std::string finalMessage = "";

        unsigned int i;
        char *s;
        bool b;
        int argCount = 0;
        // Validate input format to not include bad characters
        for (int index = 0; input[index] != '\0'; index++) {
            switch (input[index]) {
                case '%':
                    argCount++;
                    return;
                case '\n':
                    std::cout << "Invalid Format, dont use \\n in format\n";
                    return;
            }
        }

        if(argCount <= 0)
        {
            std::cout << input;  // Output to console
            buffer.push_back(input);  // Add input to buffer
            system("pause");
            return;
        }

        // Module 1: Initializing Myprintf's arguments
        va_list arg;
                va_start(arg, input);

        for (int index = 0; input[index] != '\0'; index++) {
            while ( input[index] != '%' ) {
                finalMessage += input[index];
                index++;
            }

            index++;

            // Module 2: Fetching and executing arguments
            switch (input[index]) {
                case 'c' : i = va_arg(arg, int);  // Character Argument
                    finalMessage += i;
                    break;

                case 'd' : i = va_arg(arg, int);  // Decimal Argument
                    if (i < 0) {
                        i = -i;
                        finalMessage += '-';
                    }
                    finalMessage +=i;
                    break;
                case 's': s = va_arg(arg, char *);  // String Argument
                    finalMessage += s;
                    break;
                case 'v':  // Vector Argument
                    index++;
                    finalMessage += LogVector(input[index], arg);
                    break;
                case 'm':  // Matrix Argument
                    index++;
                    finalMessage += LogMatrix(input[index], arg);
                    break;
                case 'n':
                    index++;
                    finalMessage += '\n';
                case 'b':
                    b = va_arg(arg, bool);  // String Argument
                    if(b)
                        finalMessage += "True";
                    else
                        finalMessage += "False";
                    break;
            }
        }

        // Module 3: Closing argument list to necessary clean-up
                va_end(arg);

        std::cout << finalMessage;  // Output to console
        buffer.push_back(finalMessage);  // Add input to buffer
        system("pause");
    }
}  // namespace TandenEngine
