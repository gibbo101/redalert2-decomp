#include "shared/vector_class.hpp"
// Original RTTI type descriptor 007d6120 identifies DynamicVectorClass<ButtonFadeEffect *>.
class ButtonFadeEffect;

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
template class DynamicVectorClass<ButtonFadeEffect *>;
