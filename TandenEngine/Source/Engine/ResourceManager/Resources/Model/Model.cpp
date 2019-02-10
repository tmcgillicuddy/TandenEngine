#define TINYOBJLOADER_IMPLEMENTATION  // define this in only *one* .cc

#include <tiny_obj_loader.h>
#include <unordered_map>

#include "Model.h"
#include "../../BufferManager.h"


namespace TandenEngine {

    Model::Model() {
        mResourceType = ResourceType::MODEL;
    }

    bool Model::CheckIfSupported(std::string extension) {
        return (extension == ".fbx" || extension == ".obj");
    }

    void Model::CreateVertexBuffer() {
        // BufferManager::CreateVertexBufferForTargetModel(this);
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

        // Load model data into temporary buffer
        if (!::tinyobj::LoadObj(&attrib, &shapes, &materials,
                &warn, &err, mMetaData->mFileDir.c_str())) {
            std::cout <<"Error loading model\n";
            throw std::runtime_error(warn + err);
        }

        std::unordered_map<MeshVertex, uint32_t> uniqueVertices = {};

        // Iterate through all shapes and add their vertex data to main vector
        for (const auto &shape : shapes) {
            for (const auto &index : shape.mesh.indices) {
                MeshVertex vertex = MeshVertex();
                vertex.mPos = vec3(
                        attrib.vertices[3 * index.vertex_index + 0],
                        attrib.vertices[3 * index.vertex_index + 1],
                        attrib.vertices[3 * index.vertex_index + 2]);

                vertex.mUV = vec2(
                        attrib.texcoords[2 * index.texcoord_index + 0],
                        1.0f - attrib.texcoords[2 * index.texcoord_index + 1]);

                vertex.mColor = vec3(1, 1, 1);

                // If this is a unique vertex add to verticies vector
                if (uniqueVertices.count(vertex) == 0) {
                    uniqueVertices[vertex] = static_cast<uint32_t>(mVertices.size());
                    mVertices.push_back(vertex);
                }

                mIndices.push_back(mIndices.size());
            }
        }

        std::cout<< "Num verts " << mVertices.size();
        // TODO(Rosser) Create API to make buffer from model data
        // BufferManager::CreateVertexBufferForModel(this);
    }
}  // namespace TandenEngine
