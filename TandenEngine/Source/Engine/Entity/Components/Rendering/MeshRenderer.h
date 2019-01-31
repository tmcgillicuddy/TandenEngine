//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef TANDENENGINE_MESHRENDERER_H
#define TANDENENGINE_MESHRENDERER_H

#include "Renderer.h"
#include "MeshFilter.h"

namespace TandenEngine {

    class MeshRenderer : public Renderer {
    public:
        MeshRenderer();

        ~MeshRenderer();

        void Draw() override;

        std::string ToString() override;

        std::unique_ptr<Component> Clone() override;

        Component * ConvertFromString(std::vector<std::string> input) override; //Takes in some string data and will output a Mesh Renderer object

    public:
        MeshFilter *mpMesh{}; //Pointer to mesh component to draw (must be on the same gameobject)
    };

}

#endif //TANDENENGINE_MESHRENDERER_H
