// int LayerClass::Sorted_Add(ObjectClass *object) (0x00534980)
// Inserts the object before the first larger one (Westwood's LAYER.CPP).
#include "shared/layer.hpp"
#include "shared/object.hpp"
// @ref ??OObjectClass@@QBE_NABV0@@Z=005d4ae0

int LayerClass::Sorted_Add(ObjectClass *object)
{
    if (ActiveCount >= Length()) {
        if ((IsAllocated || !VectorMax) && GrowthStep > 0) {
            if (!Resize(Length() + GrowthStep)) {
                return false;
            }
        } else {
            return false;
        }
    }
    int index;
    for (index = 0; index < ActiveCount; index++) {
        if (*(*this)[index] > *object) {
            break;
        }
    }
    for (int i = ActiveCount - 1; i >= index; i--) {
        (*this)[i + 1] = (*this)[i];
    }
    (*this)[index] = object;
    ActiveCount++;
    return true;
}
