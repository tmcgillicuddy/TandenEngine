//
// Created by Thomas on 1/19/2019.
//

#include "CylinderModel.h"

namespace TandenEngine {
    CylinderModel::CylinderModel() {
        for (int i = 0; i < mSlices + 1; i++) {
            float iDivSlices = static_cast<float>(i) / static_cast<float>(mSlices);
            // TODO(Nils) add PI to math
            float alpha = (i == 0 || i == mSlices) ? 0.0f : iDivSlices * 2.0f * 3.14f;
            float xDir = std::cos(alpha);
            float zDir = std::sin(alpha);

            for (int j = 0; j < mStacks + 1; j++) {
                float jDivStacks = static_cast<float>(j) / static_cast<float>(mStacks);
                float radius = mRadius * (1.0f - jDivStacks) + mRadius * jDivStacks;

                vec3 position = vec3(xDir * radius, jDivStacks * mHeight - (mHeight / 2.0f),
                        zDir * radius);
                vec2 uvs = vec2(1.0f - iDivSlices, 1.0f - jDivStacks);
                vec3 normal = vec3(xDir, 0.0f, zDir);
                vec3 tangent = vec3();
                mVertices.emplace_back(MeshVertex(position, tangent));
            }
        }

        for (int i = 0; i < mSlices; i++) {
            for (int j = 0; j < mStacks; j++) {
                int first = j + ((mStacks + 1) * i);
                int second = j + ((mStacks + 1) * (i + 1));

                mIndices.emplace_back(first);
                mIndices.emplace_back(second);
                mIndices.emplace_back(second + 1);

                mIndices.emplace_back(first);
                mIndices.emplace_back(second + 1);
                mIndices.emplace_back(first + 1);
            }
        }
    }

    void CylinderModel::LoadModel() {
        CreateModelBuffers();
    }
}  // namespace TandenEngine
