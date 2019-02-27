//
// Created by thomas.mcgillicuddy on 2/25/2019.
//

#ifndef TANDENEDITOR_MATERIAL_H
#define TANDENEDITOR_MATERIAL_H

#include "../Component.h"
#include "../../../ResourceManager/Resources/Image.h"

namespace TandenEngine {

    class MaterialComp : public Component {
    public:
        MaterialComp();
        vec4 mColor = vec4(1,1,1,1);  // default color
        Image *mAlbedo = nullptr;  // overrides mColor when not null
        float mMetallicVal = 0.5;
        Image *mMetallic = nullptr;  // overrides mMetallicVal when not null
        float mRoughnessVal = 0.5;
        Image *mRoughness = nullptr;  // overrides mRoughnessVal when not null
        Image *mNormal = nullptr;  // don't use if null

        void Update() override;
        std::unique_ptr<Component> Clone() override;
        std::string ToString() override;

        // Takes in some string data and will output a material object
        Component * ConvertFromString(std::vector<std::string> input) override;

        void GenGUI() override;
    };

}  // namespace TandenEngine

#endif //TANDENEDITOR_MATERIAL_H
