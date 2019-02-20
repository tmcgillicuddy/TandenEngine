//
// Created by Thomas on 1/19/2019.
//

#include "SphereModel.h"

namespace TandenEngine {
    SphereModel::SphereModel() {
        for (int i = 0; i < mSlices + 1; i++) {
            float iDivLong = static_cast<float>(i) / static_cast<float>(mSlices);
            // TODO(Nils) add PI to math
            float theta = (i == 0 || i == mSlices) ? 0.0f : iDivLong * 2.0f * 3.14f;

            for (int j = 0; j < mStacks + 1; j++) {
                float jDivLat = static_cast<float>(j) / static_cast<float>(mStacks);
                // TODO(Nils) add PI to math
                float phi = jDivLat * 2.0f * 3.14f;

                vec3 normal = vec3(std::cos(phi) * std::sin(theta),
                        std::cos(theta), std::sin(phi) * std::sin(theta));
                // TODO(Nils) fix inplace multiplication
                vec3 position = vec3(mRadius * normal.x, mRadius * normal.y, mRadius * normal.z);
                vec2 uvs = vec2(1.0f - jDivLat, 1.0f - iDivLong);
                vec3 tangent = vec3();
                mVertices.emplace_back(MeshVertex(position, tangent));
            }
        }

        for (int i = 0; i < mSlices; i++) {
            for (int j = 0; j < mStacks; j++) {
                int first = j + ((mStacks + 1) * i);
                int second = j + ((mStacks + 1) * (i + 1));

                mIndices.emplace_back(first);
                mIndices.emplace_back(second + 1);
                mIndices.emplace_back(second);

                mIndices.emplace_back(first);
                mIndices.emplace_back(first + 1);
                mIndices.emplace_back(second + 1);
            }
        }
    }

    void SphereModel::LoadModel() {
        CreateModelBuffers();
    }
}  // namespace TandenEngine
