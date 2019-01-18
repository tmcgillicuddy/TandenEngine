//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#include "Model.h"

#include <tiny_obj_loader.h>

namespace TandenEngine {

    Model::Model() {
        mResourceType = ResourceType::MODEL;
    }

    bool Model::CheckIfSupported(std::string extension) {
        return (extension == ".fbx" || extension == ".obj");
    }

    Model::Model(MetaData *inputData) {


        LoadModel();
    }

    void Model::LoadModel() {
        tinyobj::attrib_t attrib; //ALL vertex data
        std::vector<tinyobj::shape_t> shapes; //All different objects in file
        std::vector<tinyobj::material_t> materials;
        std::string warn, err;
        //Load model data into temporary buffer
        if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, MODEL_PATH.c_str())) { //TODO change model path to reference the meta data dir path
            throw std::runtime_error(warn + err);
        }

        //Iterate through all shapes and add their vertex data to main vector
        for (const auto& shape : shapes) {
            for(const auto& index : shape.mesh.indices) {
                MeshVertex vertex = {};
                vertex.mPos = new Vector3(
                        attrib.vertices[3*index.vertex_index +0],
                        attrib.vertices[3*index.vertex_index +1],
                        attrib.vertices[3*index.vertex_index +2]
                        );

                vertex.mUV = new Vector2(
                        attrib.texcoords[2*index.texcoord_index +0],
                        attrib.texcoords[2*index.texcoord_index +1],
                );

                vertex.mColor = new Vector3(1,1,1);
                verticies.push_back(vertex);
                indices.push_back(indices.size());
            }
        }
    }
}