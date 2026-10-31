// BooleanVectorClass: a packed vector of bools (Westwood's VECTOR.H/VECTOR.CPP library class;
// the RA2 unit 0x0070EFC0-0x0070F3A2 keeps its member order: constructor, copy constructor,
// operator=, operator==, Resize, Clear, Reset, Set, Fixup). Not polymorphic, no RTTI.
//
// Layout (constructor 0x0070EFC0):
//   +0x00 unsigned BitCount   number of bools (Fixup and Resize compare it unsigned)
//   +0x04 bool Copy           the referential copy of element LastIndex
//   +0x08 int LastIndex       -1 when no element is fetched into Copy
//   +0x0C VectorClass<unsigned char> BitArray  (vtable 0x007AE6EC), (BitCount + 7) / 8 bytes
//
// The bit helpers come from the JSHELL unit (shared/jshell.hpp).
#ifndef RA2_SHARED_BOOLEAN_VECTOR_HPP
#define RA2_SHARED_BOOLEAN_VECTOR_HPP

#include "shared/jshell.hpp"
#include "shared/vector_class.hpp"

class BooleanVectorClass {
public:
    BooleanVectorClass(unsigned size = 0, unsigned char *array = 0);
    BooleanVectorClass(BooleanVectorClass const &vector);

    BooleanVectorClass &operator=(BooleanVectorClass const &vector);
    int operator==(BooleanVectorClass const &vector) const;

    int Length() { return BitCount; }
    void Reset();
    void Set();
    void Clear();
    int Resize(unsigned size);

    bool const &operator[](int index) const
    {
        if (LastIndex != index) {
            Fixup(index);
        }
        return Copy;
    }
    bool &operator[](int index)
    {
        if (LastIndex != index) {
            Fixup(index);
        }
        return Copy;
    }

protected:
    void Fixup(int index = -1) const;

    unsigned BitCount;                      // +0x00
    bool Copy;                              // +0x04
    int LastIndex;                          // +0x08
    VectorClass<unsigned char> BitArray;    // +0x0C
};

#endif
