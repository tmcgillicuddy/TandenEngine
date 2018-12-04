//
// Created by rosser.martinez on 12/3/2018.
//

#ifndef TANDENENGINE_WINDOW_H
#define TANDENENGINE_WINDOW_H


#include "../../../Libraries/GLFW/include/GLFW/glfw3.h"
#include <string>

namespace TandenEngine {

    class Window {

    private:
        //reference to window
        GLFWwindow* windowRef;

        int height = 800;
        int width = 600;

        std::string name;

    public:

        Window();
        Window(int newWidth, int newHeight, std::string newName);
        ~Window();

        //getters
        int GetHeight(){return height;};
        int GetWidth(){return width;};
        std::string GetName(){return name;};
        GLFWwindow* GetWindowRef(){return windowRef;};


        //setters
        void SetHeight(int newHeight){height = newHeight;};
        void SetWidth(int newWidth){width = newWidth;};
        void SetName(std::string newName){name = newName;};
        void SetWindowRef(GLFWwindow* newWindowRef){windowRef = newWindowRef;};

        void initWindow();
    };

};


#endif //TANDENENGINE_WINDOW_H
