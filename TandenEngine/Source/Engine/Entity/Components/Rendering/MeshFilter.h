//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef TANDENENGINE_MESHFILTER_H
#define TANDENENGINE_MESHFILTER_H

#include "../../../ResourceManager/Resources/Model/Model.h"
#include "../Component.h"
namespace TandenEngine {

    class MeshFilter : public Component {
    private:
        Model *mModelResource;

    public:
        Component * ConvertFromString(std::vector<std::string> input) override; //Takes in some string data and will output a Mesh Filter object
    };

}

#endif //TANDENENGINE_MESHFILTER_H
