//
// Created by thomas.mcgillicuddy on 2/25/2019.
//

#ifndef TANDENEDITOR_MATERIAL_H
#define TANDENEDITOR_MATERIAL_H

#include "../Component.h"

namespace TandenEngine {

    class MaterialComp : public Component {
    public:
        MaterialComp();

        void Update() override;
        std::unique_ptr<Component> Clone() override;
        std::string ToString() override;

        // Takes in some string data and will output a material object
        Component * ConvertFromString(std::vector<std::string> input) override;
    };

}  // namespace TandenEngine

#endif //TANDENEDITOR_MATERIAL_H
