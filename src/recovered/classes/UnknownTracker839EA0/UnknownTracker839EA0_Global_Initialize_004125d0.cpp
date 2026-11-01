// The tracker global and its genuine vector lifetime.
// Full extent is independently adjacent to unknown_geometry_angle45 at83C438.
#define VECTOR_IMPLEMENT_ALL
#include "shared/vector_class.hpp"
#include "shared/foot.hpp"
// Clear each airborne bin and its working list, preserving capacities.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/foot.hpp"
void UnknownTracker839EA0::Clear_00413540()
{
    for (int i=0;i<400;++i) {
        int capacity=Bins[i].Length();
        Bins[i].Clear();
        Bins[i].Resize(capacity,0);
    }
    int capacity=Working.Length();
    Working.Clear();
    Working.Resize(capacity,0);
}

inline UnknownTracker839EA0::~UnknownTracker839EA0()
{
    Clear_00413540();
}
UnknownTracker839EA0 unknown_tracker_839ea0;

// Original-evidenced vector vtables, their slots, constructor and global lifetime.
// @ref ??0?$VectorClass@PAVTechnoClass@@@@QAE@IPBQAVTechnoClass@@@Z=0040bc10
// @ref ??8?$VectorClass@PAVTechnoClass@@@@UBE_NABV0@@Z=0040b870
// @ref ??_7?$DynamicVectorClass@PAVTechnoClass@@@@6B@=0079a79c
// @ref ??_7?$VectorClass@PAVTechnoClass@@@@6B@=0079a7fc
// @ref ??_E?$DynamicVectorClass@PAVTechnoClass@@@@UAEPAXI@Z=0040bbc0
// @ref ??_E?$VectorClass@PAVTechnoClass@@@@UAEPAXI@Z=0040bb70
// @ref ??_G?$DynamicVectorClass@PAVTechnoClass@@@@UAEPAXI@Z=0040bbc0
// @ref ??_G?$VectorClass@PAVTechnoClass@@@@UAEPAXI@Z=0040bb70
// @ref ?Clear@?$DynamicVectorClass@PAVTechnoClass@@@@UAEXXZ=0040b5b0
// @ref ?Clear@?$VectorClass@PAVTechnoClass@@@@UAEXXZ=0040b960
// @ref ?Clear_00413540@UnknownTracker839EA0@@QAEXXZ=00413540
// @ref ?Fetch@?$VectorClass@PAVTechnoClass@@@@UBEPAVTechnoClass@@H@Z=0040b600
// @ref ?ID@?$DynamicVectorClass@PAVTechnoClass@@@@UAEHABQAVTechnoClass@@@Z=0040baa0
// @ref ?ID@?$DynamicVectorClass@PAVTechnoClass@@@@UAEHPBQAVTechnoClass@@@Z=0040b5e0
// @ref ?ID@?$VectorClass@PAVTechnoClass@@@@UAEHABQAVTechnoClass@@@Z=0040b990
// @ref ?ID@?$VectorClass@PAVTechnoClass@@@@UAEHPBQAVTechnoClass@@@Z=0040b9d0
// @ref ?Resize@?$DynamicVectorClass@PAVTechnoClass@@@@UAE_NHPBQAVTechnoClass@@@Z=0040b9f0
// @ref ?Resize@?$VectorClass@PAVTechnoClass@@@@UAE_NHPBQAVTechnoClass@@@Z=0040b8b0
// @ref ?unknown_tracker_839ea0@@3UUnknownTracker839EA0@@A=00839ea0
// @ref _$E44=00412650
