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
                    Vector2 vec2;
                    Vector3 vec3;
                    switch (input[index])
                    {
                        case '2':
                            vec2 = va_arg(arg, Vector2);
                            finalMessage += vec2.ToString();
                            break;
                        case '3':
                            vec3 = va_arg(arg, Vector3);
                            finalMessage += vec3.ToString();
                            break;
                    }
                    break;
            }
        }

        //Module 3: Closing argument list to necessary clean-up
        va_end(arg);

        std::cout << finalMessage <<std::endl; //Output to console

        buffer.push_back(finalMessage); //Add input to buffer
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