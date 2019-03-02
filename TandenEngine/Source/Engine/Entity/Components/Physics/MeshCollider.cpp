//
// Created by thomas.mcgillicuddy on 12/5/2018.
//

#include "MeshCollider.h"

namespace TandenEngine {
    MeshCollider::MeshCollider() {
    }

    void MeshCollider::ComputeBounds(vec3 v[], int numVerts) {
        int minX = 0, minY = 0, minZ = 0, maxX = 0, maxY = 0, maxZ = 0;

        for(int i = 1; i < numVerts; ++i) {
            if(v[i].x < v[minX].x) minX = i;
            if(v[i].y < v[minY].x) minY = i;
            if(v[i].z < v[minZ].x) minZ = i;
            if(v[i].x > v[maxX].x) maxX = i;
            if(v[i].y > v[maxY].x) maxY = i;
            if(v[i].z > v[maxZ].x) maxZ = i;
        }

        // more to do
    }

    // TODO(Nils) Rest of bound computation
    /*
    // Compute the squared distances for the three pairs of points
    float dist2x = Dot(pt[maxx] - pt[minx], pt[maxx] - pt[minx]);
    float dist2y = Dot(pt[maxy] - pt[miny], pt[maxy] - pt[miny]);
    float dist2z = Dot(pt[maxz] - pt[minz], pt[maxz] - pt[minz]);
    // Pick the pair (min,max) of points most distant
    min = minx;
    max = maxx;
    if (dist2y > dist2x && dist2y > dist2z) {
    max = maxy;
    min = miny;
    }
    if (dist2z > dist2x && dist2z > dist2y) {
    max = maxz;
    min = minz;
    }
    }
    void SphereFromDistantPoints(Sphere &s, Point pt[], int numPts)
    {
    // Find the most separated point pair defining the encompassing AABB
    int min, max;
    MostSeparatedPointsOnAABB(min, max, pt, numPts);
    // Set up sphere to just encompass these two points
    s.c = (pt[min] + pt[max]) * 0.5f;
    s.r = Dot(pt[max] - s.c, pt[max] - s.c);
    s.r = Sqrt(s.r);
    }
    */

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
