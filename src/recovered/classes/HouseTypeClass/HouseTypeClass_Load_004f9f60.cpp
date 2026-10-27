// HRESULT __stdcall HouseTypeClass::Load(IStream *stream) (0x004F9F60)
// Empties the veteran lists, loads the abstract type, restores the house
// type in place, rebuilds the three veteran lists from their saved counts
// and entries and swizzles them.
#include "shared/house_type.hpp"
// @ref ??_7?$DynamicVectorClass@PAVInfantryTypeClass@@@@6B@=007a3178
// @ref ??_G?$DynamicVectorClass@PAVInfantryTypeClass@@@@UAEPAXI@Z=004faaf0
// @ref ??_7?$DynamicVectorClass@PAVUnitTypeClass@@@@6B@=007a3198
// @ref ??_G?$DynamicVectorClass@PAVUnitTypeClass@@@@UAEPAXI@Z=004faec0
// @ref ?Load@AbstractClass@@UAGJPAUIStream@@@Z=00410120
// @ref ??0HouseTypeClass@@QAE@ABVNoInitClass@@@Z=004f9350
// @ref ??0?$DynamicVectorClass@PAVInfantryTypeClass@@@@QAE@IPBQAVInfantryTypeClass@@@Z=004faa90
// @ref ?Add@?$DynamicVectorClass@PAVInfantryTypeClass@@@@QAE_NABQAVInfantryTypeClass@@@Z=004fabf0
// @ref ??0?$DynamicVectorClass@PAVUnitTypeClass@@@@QAE@IPBQAVUnitTypeClass@@@Z=004fae60
// @ref ?Add@?$DynamicVectorClass@PAVUnitTypeClass@@@@QAE_NABQAVUnitTypeClass@@@Z=004fafc0
// @ref ??0?$TypeList@PAVAircraftTypeClass@@@@QAE@XZ=004fa630
// @ref ?Add@?$DynamicVectorClass@PAVAircraftTypeClass@@@@QAE_NABQAVAircraftTypeClass@@@Z=004fb390
// @ref ?Swizzle@SwizzleManagerClass@@QAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868

// Rebuilds a list in place from its saved count and elements.
template <class T>
static inline void Load_List(IStream *stream, TypeList<T> &list)
{
    new (&list) TypeList<T>;
    int count;
    stream->Read(&count, sizeof(count), 0);
    for (int index = 0; index < count; index++) {
        T value;
        stream->Read(&value, sizeof(value), 0);
        list.Add(value);
    }
}

HRESULT __stdcall HouseTypeClass::Load(IStream *stream)
{
    VeteranInfantry.Clear();
    VeteranUnits.Clear();
    VeteranAircraft.Clear();
    HRESULT result = AbstractTypeClass::Load(stream);
    if (FAILED(result)) {
        return result;
    }
    new (this) HouseTypeClass(NoInitClass());
    Load_List(stream, VeteranInfantry);
    Load_List(stream, VeteranUnits);
    Load_List(stream, VeteranAircraft);
    int index;
    for (index = 0; index < VeteranInfantry.Count(); index++) {
        Swizzle_Pointer(VeteranInfantry[index]);
    }
    for (index = 0; index < VeteranUnits.Count(); index++) {
        Swizzle_Pointer(VeteranUnits[index]);
    }
    for (index = 0; index < VeteranAircraft.Count(); index++) {
        Swizzle_Pointer(VeteranAircraft[index]);
    }
    return S_OK;
}
