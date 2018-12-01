//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef HWENGINE_MESHRENDERER_H
#define HWENGINE_MESHRENDERER_H

#include "Renderer.h"
#include "MeshFilter.h"

namespace TandenEngine {

    class MeshRenderer : public Renderer {
    public:
        MeshRenderer();

        ~MeshRenderer();

        void Draw() override;

        std::string ToString() override;
    private:
        MeshFilter *mpMesh{}; //Pointer to mesh component to draw (must be on the same gameobject)
    };

}

#endif //HWENGINE_MESHRENDERER_H
