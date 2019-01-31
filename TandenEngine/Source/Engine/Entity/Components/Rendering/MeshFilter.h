//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef TANDENENGINE_MESHFILTER_H
#define TANDENENGINE_MESHFILTER_H

#include "../../../ResourceManager/Resources/Model/Model.h"
#include "../Component.h"
namespace TandenEngine {

    class MeshFilter : public Component {
    public:
        Model *mModelResource;

    public:

         void Update() override {};
         std::unique_ptr<Component> Clone() override {return nullptr;};
         void Register() override {};
         std::string ToString() override {return nullptr;};

        Component * ConvertFromString(std::vector<std::string> input) override; //Takes in some string data and will output a Mesh Filter object
    };

}

#endif //TANDENENGINE_MESHFILTER_H
