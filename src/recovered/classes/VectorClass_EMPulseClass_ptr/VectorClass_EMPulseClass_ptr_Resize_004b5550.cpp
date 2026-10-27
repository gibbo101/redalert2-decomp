#include "shared/vector_class.hpp"
// Original RTTI type descriptors at 0x7D6518 and 0x7D6548 identify
// VectorClass<EMPulseClass *> and DynamicVectorClass<EMPulseClass *>.
// Only the pointer type is needed by these storage methods.
class EMPulseClass;

template<class T> bool VectorClass<T>::Resize(int newsize, T const *array)
{
    if (newsize) {
        T *newptr;
        IsValid = false;
        if (!array) newptr = new T[newsize];
        else newptr = new ((void *)array) T[newsize];
        IsValid = true;
        if (!newptr) return false;
        if (Vector) {
            int copycount = newsize < VectorMax ? newsize : VectorMax;
            for (int i = 0; i < copycount; ++i) newptr[i] = Vector[i];
            if (IsAllocated) { delete[] Vector; Vector = 0; }
        }
        Vector = newptr;
        VectorMax = newsize;
        IsAllocated = (newptr && !array);
    } else {
        Clear();
    }
    return true;
}
template<class T> bool DynamicVectorClass<T>::Resize(int newsize, T const *array)
{
    if (VectorClass<T>::Resize(newsize, array)) {
        if (VectorMax < ActiveCount) ActiveCount = VectorMax;
        return true;
    }
    return false;
}
template class VectorClass<EMPulseClass *>;
template class DynamicVectorClass<EMPulseClass *>;
