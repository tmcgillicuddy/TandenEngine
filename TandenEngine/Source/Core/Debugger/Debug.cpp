//
// Created by Thomas on 1/24/2019.
//

#include <iostream>
#include <stdarg.h>
#include <string>

#include "NilsMath.h"
#include "Debug.h"

namespace TandenEngine {

    std::vector<std::string> Debug::buffer;

    void Debug::Log(char* input, ...) {
        std::string finalMessage = "";

        unsigned int i;
        char *s;

        //Module 1: Initializing Myprintf's arguments
        va_list arg;
        va_start(arg, input);

        for(int index =0; input[index] != '\0'; index++)
        {
            while( input[index] != '%' )
            {
                finalMessage += input[index];
                index++;
            }

            index++;

            //Module 2: Fetching and executing arguments
            switch(input[index])
            {
                case 'c' : i = va_arg(arg,int); //Character Argument
                    finalMessage += i;
                    break;

                case 'd' : i = va_arg(arg,int); //Decimal Argument
                    if(i<0)
                    {
                        i = -i;
                        finalMessage += '-';
                    }
                    finalMessage +=i;
                    break;

                case 's': s = va_arg(arg,char *); //String Argument
                    finalMessage += s;
                    break;
                case 'v': //Vector Argument
                    index++;
                    finalMessage += LogVector(input[index], arg);
                    break;
                case 'm':
                    index++;
                    finalMessage += LogMatrix(input[index], arg);
                    break;
            }
        }

        //Module 3: Closing argument list to necessary clean-up
        va_end(arg);

        std::cout << finalMessage <<std::endl; //Output to console

        buffer.push_back(finalMessage); //Add input to buffer
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
    
    std::string Debug::LogVector(char type, va_list arg)
    {
        vec2 vector2;
        vec3 vector3;
        vec4 vector4;
        switch (type)
        {
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
        switch (type)
        {
            case '2':
                matrix2 = va_arg(arg, mat2);
                return matrix2.ToString(); //TODO add 2x2 matrix to string
            case '3':
                matrix3 = va_arg(arg, mat3);
                return matrix3.ToString();
            case '4':
                matrix4 = va_arg(arg, mat4);
                return matrix4.ToString();
        }

        return "";
    }
}