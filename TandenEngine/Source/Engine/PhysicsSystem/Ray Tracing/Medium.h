//
// Created by Thomas on 2018-12-25.
//

#ifndef TANDENENGINE_MEDIUM_H
#define TANDENENGINE_MEDIUM_H

namespace TandenEngine {

    class Medium {
     public:
      //  virtual Spectrum Tr(const Ray &ray, Sampler &sampler) const =0;
    };

    struct MediumInterface {
        MediumInterface(const Medium *medium)
        : inside(medium), outside(medium) { }

        MediumInterface(const Medium *inside, const Medium *outside)
        : inside(inside), outside(outside) {}

        bool IsMediumTransition() const {return inside !=outside; }

        const Medium *inside, *outside;
    };

}  // namespace TandenEngine

#endif  // TANDENENGINE_MEDIUM_H
