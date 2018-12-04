//
// Created by rosser.martinez on 12/3/2018.
//

#include "Window.h"

namespace TandenEngine {


    Window::Window(){

        width = 0;
        height = 0;
        name = "EMPTY NAME";

    };

    Window::Window(int newWidth, int newHeight, std::string newName)
    {
        width = newWidth;
        height = newHeight;
        name = newName;
    };

    Window::~Window(){};

    void Window::initWindow()
    {
        windowRef = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

    }


}
