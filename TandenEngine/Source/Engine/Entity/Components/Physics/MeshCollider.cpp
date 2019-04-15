//
// Created by thomas.mcgillicuddy on 12/5/2018.
//

#include "MeshCollider.h"

namespace TandenEngine {
    MeshCollider::MeshCollider(std::vector<vec3> v) {
        ComputeBounds(v, v.size());
        ComputeTriangles(v, v.size());
    }

    void MeshCollider::ComputeTriangles(std::vector<vec3> v, int numVerts) {
        for(int i = 2; i < numVerts; ++i) {
            // Not sure if I'm taking the data in correctly, but we'll see
            Triangle tempTri(v[i-2], v[i-1], v[1]);
            mTriangles.push_back(tempTri);
        }
    }

    // Ritter Formula, adapted from Real-Time Collision Detection by Christer Ericson
    void MeshCollider::ComputeBounds(std::vector<vec3> v, int numVerts) {
        mBoundingSphere.isMeshBound = true;
        int minX = 0, minY = 0, minZ = 0, maxX = 0, maxY = 0, maxZ = 0;

        // Find min and max points in all dimensions
        for(int i = 1; i < numVerts; ++i) {
            if(v[i].x < v[minX].x) minX = i;
            if(v[i].y < v[minY].x) minY = i;
            if(v[i].z < v[minZ].x) minZ = i;
            if(v[i].x > v[maxX].x) maxX = i;
            if(v[i].y > v[maxY].x) maxY = i;
            if(v[i].z > v[maxZ].x) maxZ = i;
        }

        // Distances between opposing points
        float distX = NilsMath::Dot(v[maxX] - v[minX], v[maxX] - v[minX]);
        float distY = NilsMath::Dot(v[maxY] - v[minY], v[maxY] - v[minY]);
        float distZ = NilsMath::Dot(v[maxZ] - v[minZ], v[maxZ] - v[minZ]);

        int min = minX, max = maxX;
        if(distY > distX && distY > distZ)
        {
            min = minY, max = maxY;
        }
        else if(distZ > distX && distZ > distY)
        {
            min = minZ, max = maxZ;
        }

        // Create approximate Sphere
        mBoundingSphere.mGlobalPosition = ((v[min] + v[max]) * 0.5f);
        mBoundingSphere.mRadius = mBoundingSphere.mGlobalPosition.Distance(v[max]);

        // Second Pass to Expand Sphere
        for(int i = 1; i < numVerts; ++i) {
            vec3 pointToSphere = v[i] - mBoundingSphere.mGlobalPosition;
            float distSqd = NilsMath::Dot(pointToSphere, pointToSphere);
            if(distSqd > mBoundingSphere.mRadius * mBoundingSphere.mRadius) {
                float dist = sqrt(distSqd);
                float newRad = (mBoundingSphere.mRadius + dist) * 0.5f;
                float change = (newRad - mBoundingSphere.mRadius) / dist;
                mBoundingSphere.mRadius = newRad;
                mBoundingSphere.mGlobalPosition += pointToSphere * change;
            }
        }
    }

    void MeshCollider::Update() {
    }

    std::unique_ptr<Component> MeshCollider::Clone() {
        return std::unique_ptr<MeshCollider>(this);
    }

    std::string MeshCollider::ToString() {
        return "";
    }

    Component *MeshCollider::ConvertFromString(std::vector<std::string> input) {
        return nullptr;
    }
}  // namespace TandenEngine
