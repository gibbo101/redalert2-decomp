// bool ObjectClass::unknown_slot80() (0x005D2E70, slot 80)
// Selects the object (hypothesis): refused while the object is in limbo or
// already selected (+0x77) or slot 76 says no, and for a techno with +0x32C
// set while slot 39 holds; a selection of another house's objects (by
// HouseClass 0x004F52B0) is cleared first. Technos whose type has +0xAA8 set
// go to the head of the selection list 0x00A40C60, others to its end.
#include "shared/techno.hpp"
#include "shared/house.hpp"
#include "shared/techno_type.hpp"
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
extern int unknown_833684;    // 0x00833684
void __cdecl Clear_Selected_Objects_00482bc0();
void __fastcall Unknown_006f6780(unsigned int value);
// @ref ?unknown_833684@@3HA=00833684
// @ref ?unknown_flag_a40d13@@3_NA=00a40d13
// @ref ?Clear_Selected_Objects_00482bc0@@YAXXZ=00482bc0
// @ref ?Unknown_006f6780@@YIXI@Z=006f6780
// @ref ?As_Techno@AbstractClass@@QAEPAVTechnoClass@@XZ=0040dc20
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?unknown_objects_a40c60@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00a40c60

bool ObjectClass::unknown_slot80()
{
    if (!unknown_flag_a40d13 && (unknown_76 || unknown_77 || !unknown_slot76())) {
        return false;
    }
    TechnoClass *techno = As_Techno();
    if (!unknown_flag_a40d13 && unknown_slot39() && techno && techno->unknown_32c) {
        return false;
    }
    if (unknown_833684) {
        return false;
    }
    if (unknown_objects_a40c60.Count() > 0) {
        HouseClass *house = Owning_House();
        HouseClass *other = unknown_objects_a40c60[0]->Owning_House();
        if (other->Unknown_004F52B0() != house->Unknown_004F52B0() || !other->Unknown_004F52B0()) {
            Clear_Selected_Objects_00482bc0();
        }
    }
    bool techno_flag;
    if (this) {
        techno_flag = AbstractFlags.IsTechno;
    }
    if (this && techno_flag && static_cast<TechnoTypeClass *>(Class_Of())->unknown_aa8) {
        unknown_objects_a40c60.Add_Head(this);
    } else {
        unknown_objects_a40c60.Add(this);
    }
    Unknown_006f6780(0);
    unknown_77 = true;
    return true;
}
