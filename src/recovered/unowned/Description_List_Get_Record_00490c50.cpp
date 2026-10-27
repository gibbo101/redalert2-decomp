#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#include "shared/unknown_description_list.hpp"
// Trial: leading 0x50 bytes match the existing CCINIClass size;
// its empty implicit derived destructor ends at the observed INIClass destructor.
// Composition is a layout hypothesis, not a recovered owning class name.
// @ref ??_7?$VectorClass@PAD@@6B@=0079e57c
// @ref ??1INIClass@@UAE@XZ=0050b8d0

bool UnknownDescriptionList_00490E00::Get_Record_00490C50(int index, UnknownDescriptionRecord_00490E00 **record)
{
    if (index >= 0 && index < Count) {
        *record = &Entries[index];
        return true;
    }
    *record = 0;
    return false;
}
