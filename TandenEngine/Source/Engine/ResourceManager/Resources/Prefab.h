//
// Created by thomas.mcgillicuddy on 11/3/2018.
//

#ifndef TANDENENGINE_PREFAB_H
#define TANDENENGINE_PREFAB_H

#include <vector>

#include "./Resource.h"
#include "../../Entity/Components/Component.h"
#include "../../Entity/GameObject.h"

namespace TandenEngine {

    class Prefab : public Resource{
    private:
        std::vector<std::unique_ptr<Component>> mComponents; //TODO Use map instead of vector
    public:
        Prefab();
        Prefab(MetaData* metaData);
        void CreatePrefab(GameObject * sourceGO);
        void UpdatePrefab(GameObject * sourceGO);
        void SavePrefab();
        static bool CheckIfSupported(std::string extension);

    };

}

#endif //TANDENENGINE_PREFAB_H
