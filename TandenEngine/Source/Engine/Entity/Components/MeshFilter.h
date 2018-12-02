//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef HWENGINE_MESHFILTER_H
#define HWENGINE_MESHFILTER_H

#include "../../ResourceManager/Resources/Model/Model.h"
#include "Component.h"
namespace TandenEngine {

    class MeshFilter : public Component {
    private:
        Model *mModelResource;

    public:
        Component * ConvertFromString(std::vector<std::string> input) override; //Takes in some string data and will output a Mesh Filter object
    };

}

#endif //HWENGINE_MESHFILTER_H
