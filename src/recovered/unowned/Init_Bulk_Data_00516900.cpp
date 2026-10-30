// bool __fastcall Init_Bulk_Data() -- 0x00516900
// Body 0x00516900-0x00516AF8 (505 bytes, nop padding to 0x00516B00). Called once from Init_Game (0x005125BE).
// Init_One_Time_Systems is TS's file-local helper; VC6 inlines it here (written out in this body the
// constant zero takes esi instead of ebx). 0x00521A90 is __fastcall: as __cdecl the CCFileClass address load
// follows the string push.
#include "shared/house.hpp"
#include "shared/cd.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/debug_printf.hpp"
#include "shared/mouse_class.hpp"
#include "shared/map_view.hpp"
#include "shared/options.hpp"
#include "shared/session_state.hpp"
#include "shared/object_type.hpp"
#include "shared/unit.hpp"
#include "shared/aircraft_type.hpp"
#include "shared/unknown_globals.hpp"

// @ref ?unknown_drop_pod_voxel_a40c80@@3VUnknownObjectPair@@A=00a40c80
// @ref ?Unknown_00458370@@YAXXZ=00458370
// @ref ?Unknown_004E2E30@@YAXXZ=004e2e30
// @ref ?Unknown_005DD760@@YAXXZ=005dd760
// @ref ?Unknown_00521A90@@YIXXZ=00521a90
// @ref ??_C@_08PKHB@DPOD?4VXL?$AA@=007dc070
// @ref ??_C@_08DBAB@DPOD?4HVA?$AA@=007dc048
// @ref ??_C@_0BK@JCLG@Failed?5to?5create?5VoxLib?$CB?6?$AA@=007dc054
// @ref ??_C@_0BK@HCNJ@Failed?5to?5create?5MotLib?$CB?6?$AA@=007dc02c

extern UnknownObjectPair unknown_drop_pod_voxel_a40c80;    // 0x00A40C80 the drop pod voxel and motion (TS's DropPodVoxel)
void unknown_481fb0();                  // 0x00481FB0 once per frame
void Unknown_00458370();                // 0x00458370 empty (a type class One_Time in TS's order)
void Unknown_004E2E30();                // 0x004E2E30 empty (TS: HouseClass::One_Time)
void Unknown_005DD760();                // 0x005DD760 (TS order: SpotLightClass::One_Time)
void __fastcall Unknown_00521A90();                // 0x00521A90 (TS order: IonBlastClass::One_Time)

// Runs the one-time system initialisations and loads the drop pod voxel (TS's Init_One_Time_Systems;
// inlined into its only caller).
static bool Init_One_Time_Systems()
{
    unknown_481fb0();
    Map.One_Time();
    Options.One_Time();
    unknown_session_a3d298.One_Time();
    ObjectTypeClass::One_Time();
    Unknown_00458370();
    ObjectTypeClass::One_Time();
    ObjectTypeClass::One_Time();
    ObjectTypeClass::One_Time();
    UnitTypeClass::One_Time();
    ObjectTypeClass::One_Time();
    ObjectTypeClass::One_Time();
    AircraftTypeClass::Init();
    Unknown_004E2E30();
    Unknown_005DD760();
    Unknown_00521A90();

    CCFileClass dropvxl("DPOD.VXL");
    unknown_drop_pod_voxel_a40c80.unknown_00 = new UnknownPairFirst(&dropvxl, 0);
    if (unknown_drop_pod_voxel_a40c80.unknown_00 == 0) {
        Debug_Printf("Failed to create VoxLib!\n");
        return false;
    }
    CCFileClass dropmot("DPOD.HVA");
    unknown_drop_pod_voxel_a40c80.unknown_04 = new UnknownPairSecond(&dropmot);
    if (unknown_drop_pod_voxel_a40c80.unknown_04 == 0) {
        Debug_Printf("Failed to create MotLib!\n");
        return false;
    }
    return true;
}

// Caches CONQUER.MIX and CAMEO.MIX, then runs the one-time system initialisations
// (Red Alert's Init_Bulk_Data).
bool __fastcall Init_Bulk_Data()
{
    if (ConquerMix == 0 || !ConquerMix->Cache()) {
        return false;
    }
    if (CameoMix == 0 || !CameoMix->Cache()) {
        return false;
    }
    unknown_481fb0();
    return Init_One_Time_Systems();
}
