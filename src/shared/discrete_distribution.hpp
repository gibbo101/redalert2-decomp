// DiscreteDistributionClass<T> (Westwood's weighted random choice; RTTI names
// DiscreteDistributionClass<CellClass>::DistributionObject<CellClass *> as the
// element of VectorClass vtable 0x007A17D4 / DynamicVectorClass 0x007A17FC).
// Element layout from those vector members: +0x00 the object, +0x04 its
// weight; the default constructor sets only the weight to 0 (array new
// 0x004CE710 writes +4 only); equality compares the object, then the weight.
// Names are hypotheses.
#ifndef SHARED_DISCRETE_DISTRIBUTION_HPP
#define SHARED_DISCRETE_DISTRIBUTION_HPP

#include "shared/vector_class.hpp"

template <class T>
class DiscreteDistributionClass {
public:
    template <class U>
    class DistributionObject {
    public:
        DistributionObject() : Weight(0) {}
        DistributionObject(DistributionObject const &other) : Object(other.Object), Weight(other.Weight) {}
        ~DistributionObject() {}
        bool operator==(DistributionObject const &other) const
        {
            return Object == other.Object && Weight == other.Weight;
        }
        bool operator!=(DistributionObject const &other) const
        {
            return Object != other.Object || Weight != other.Weight;
        }

        U Object;          // +0x00
        unsigned Weight;   // +0x04
    };
};

#endif
