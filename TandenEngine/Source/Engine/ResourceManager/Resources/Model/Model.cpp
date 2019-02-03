//
// Created by thomas.mcgillicuddy on 10/31/2018.
//
#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc

#include "Model.h"

#include <unordered_map>
#include <tiny_obj_loader.h>

namespace TandenEngine {

    Model::Model() {
        mResourceType = ResourceType::MODEL;
    }

    bool Model::CheckIfSupported(std::string extension) {
        return (extension == ".fbx" || extension == ".obj");
    }

    Model::Model(MetaData *inputData) {
        mMetaData = inputData;
        LoadModel();
    }

    void Model::LoadModel() {
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warn, err;
        //Load model data into temporary buffer
        if (!::tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, mMetaData->mFileDir.c_str())) { //TODO change model path to reference the meta data dir path
            std::cout<<"Error loading model\n";
            return;
            throw std::runtime_error(warn + err);
        }

        std::unordered_map<MeshVertex, uint32_t> uniqueVertices = {};

        //Iterate through all shapes and add their vertex data to main vector
        for (const auto &shape : shapes) {
            for (const auto &index : shape.mesh.indices) {
                MeshVertex vertex = {};
                vertex.mPos = vec3(
                        attrib.vertices[3 * index.vertex_index + 0],
                        attrib.vertices[3 * index.vertex_index + 1],
                        attrib.vertices[3 * index.vertex_index + 2]
                );

                vertex.mUV = vec2(
                        attrib.texcoords[2 * index.texcoord_index + 0],
                        1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
                );

                vertex.mColor = vec3(1, 1, 1);

                if (uniqueVertices.count(vertex) == 0) //If this is a unique vertex add to verticies vector
                {
                    uniqueVertices[vertex] = static_cast<uint32_t>(verticies.size());
                    verticies.push_back(vertex);
                }

                indices.push_back(indices.size());
            }
        }

        std::cout<< "Num verts " << verticies.size();
    }
}