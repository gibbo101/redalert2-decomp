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
    typedef DistributionObject<T *> DIST_OBJ;

    // FootClass 0x004CBB40 constructs one on the stack: the vector's
    // constructor (0x004CE710, out of line), then Clear (the virtual call).
    DiscreteDistributionClass() { Clear(); }
    ~DiscreteDistributionClass() {}

    void Add(T *object, unsigned weight)
    {
        DIST_OBJ entry;
        entry.Object = object;
        entry.Weight = weight;
        Objects.Add(entry);
        TotalWeight += weight;
    }
    void Clear()
    {
        TotalWeight = 0;
        Objects.Clear();
    }
    int Count() const { return Objects.Count(); }
    // A weighted random pick (Random_Pick from shared/id_source.hpp, looked
    // up where the template is used); null when empty.
    T *Sample()
    {
        unsigned cumulative = 0;
        if (TotalWeight >= 1 && Count() != 0) {
            unsigned pick = Random_Pick<unsigned>(1, TotalWeight);
            for (int index = 0; index < Objects.Count(); index++) {
                cumulative += Objects[index].Weight;
                if (cumulative >= pick) {
                    return Objects[index].Object;
                }
            }
            return 0;
        }
        return 0;
    }

    DynamicVectorClass<DIST_OBJ> Objects;   // +0x00
    unsigned TotalWeight;                   // +0x18
};

#endif
