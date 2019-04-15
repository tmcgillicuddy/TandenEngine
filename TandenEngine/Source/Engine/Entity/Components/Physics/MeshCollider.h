//
// Created by thomas.mcgillicuddy on 12/5/2018.
//

#ifndef TANDENENGINE_MESHCOLLIDER_H
#define TANDENENGINE_MESHCOLLIDER_H

#include "Collider.h"
#include "SphereCollider.h"
#include <vector>

namespace TandenEngine {

    struct Triangle {
        // TODO(Nils) This is definitely not correct. Need to look into better.
        Triangle(vec3 p1, vec3 p2, vec3 p3) { mVert1 = p1; mVert2 = p2; mVert3 = p3; };
        ~Triangle() {};
        vec3 mVert1;
        vec3 mVert2;
        vec3 mVert3;
    };

    class MeshCollider : public Collider {
     public:
        MeshCollider(std::vector<vec3> v);
        SphereCollider mBoundingSphere;
        std::vector<Triangle> mTriangles;

        void ComputeBounds(std::vector<vec3> v, int numVerts);
        void ComputeTriangles(std::vector<vec3> v, int numVerts);

        // Component Overrides
        void Update() override;
        std::unique_ptr<Component> Clone() override;
        std::string ToString() override;
        // Takes in some string data and will output a mesh collider object
        Component * ConvertFromString(std::vector<std::string> input) override;

        // Collider Overrides
    };
}  // namespace TandenEngine

#endif  // TANDENENGINE_MESHCOLLIDER_H
