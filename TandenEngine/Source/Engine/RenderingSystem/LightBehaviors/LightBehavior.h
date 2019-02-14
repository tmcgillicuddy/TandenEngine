//
// Created by Thomas on 1/19/2019.
//

#ifndef TANDENENGINE_LIGHTBEHAVIOR_H
#define TANDENENGINE_LIGHTBEHAVIOR_H

namespace TandenEngine {

    enum LightType {
        POINTLIGHT,
        DIRECTIONALLIGHT
    };

    struct LightBehavior {
     public:
        LightType mLightType;

        LightBehavior(LightType type);
    };

}  // namespace TandenEngine

#endif  // TANDENENGINE_LIGHTBEHAVIOR_H
