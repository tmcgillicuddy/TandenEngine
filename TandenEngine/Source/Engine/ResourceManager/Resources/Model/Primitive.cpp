//
// Created by thomas.mcgillicuddy on 2/10/2019.
//

#include "Primitive.h"
#include "../../BufferManager/BufferManager.h"

namespace TandenEngine {

    CubeModel Primitive::Cube = CubeModel();
    SphereModel Primitive::Sphere = SphereModel();
    CylinderModel Primitive::Cylinder = CylinderModel();

    void Primitive::InitPrimitives() {
        BufferManager::AddModel(&Cube);
        BufferManager::AddModel(&Sphere);
        BufferManager::AddModel(&Cylinder);
    }
}  // namespace TandenEngine
