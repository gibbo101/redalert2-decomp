#ifndef RA2_COUNTER_CLASS_HPP
#define RA2_COUNTER_CLASS_HPP
#include "shared/vector_class.hpp"
#include "shared/com_persist.hpp"
// CounterClass has the VectorClass<int> layout (16 bytes), with Clear
// overridden to zero the slots while retaining storage (vtable 0x79e5ac).
class CounterClass : public VectorClass<int> {
public:
 CounterClass(); // 00491c00
 int Increment(int index); // 00491c50
 int Decrement(int index); // 00491cb0
 int Get(int index); // 00491d10
 virtual void Clear(); // 00491d70
 int Sum() const; // 00491d90
 HRESULT Save(IStream *stream); // 00491db0
 HRESULT Load(IStream *stream); // 00491e10
 bool Ensure_Index(int index); // 00491ea0
};
#endif

