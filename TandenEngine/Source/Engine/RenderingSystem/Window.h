//
//  Created by rosser.martinez on 12/3/2018.
//

#ifndef TANDENENGINE_WINDOW_H
#define TANDENENGINE_WINDOW_H

#include <string>
#include "../../../Libraries/GLFW/include/GLFW/glfw3.h"

namespace TandenEngine {

    class Window {
     private:
        // reference to window
        GLFWwindow* windowRef;

        uint32_t height = 800;
        uint32_t width = 600;

        std::string name;

     public:
        Window();
        Window(int newWidth, int newHeight, std::string newName);
        ~Window();

        // getters
        uint32_t GetHeight() {return height;}
        uint32_t GetWidth() {return width;}
        std::string GetName() {return name;}
        GLFWwindow* GetWindowRef() {return windowRef;}


        // setters
        void SetHeight(uint32_t newHeight) {height = newHeight;}
        void SetWidth(uint32_t newWidth) {width = newWidth;}
        void SetName(std::string newName) {name = newName;}
        void SetWindowRef(GLFWwindow* newWindowRef) {windowRef = newWindowRef;}

        void initWindow();
    };

}  // namespace TandenEngine

#endif  // TANDENENGINE_WINDOW_H
