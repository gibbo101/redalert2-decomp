// BuildingClass and BuildingTypeClass as far as House.cpp reads them
// (views until their headers exist).
#ifndef RA2_SCENARIO_HOUSE_VIEWS_HPP
#define RA2_SCENARIO_HOUSE_VIEWS_HPP

#include "shared/techno.hpp"

class BuildingTypeClass;
// BuildingClass as far as this unit reads it (until its header exists).
struct UnknownBuildingView : public TechnoClass {
    BuildingTypeClass *Type;                // +0x418

    int unknown_func_4532f0();              // 0x004532F0
    void unknown_func_452f50(int arg1);     // 0x00452F50
};
struct UnknownBuildingTypeView {
    char unknown_0000[0x6FC];
    int Storage;                            // +0x06FC tiberium storage (hypothesis)
    char unknown_0700[0xC44 - 0x700];
    int unknown_c44;                        // +0x0C44
    char unknown_0c48[0xC68 - 0xC48];
    int unknown_c68;                        // +0x0C68
    char unknown_0c6c[0x1348 - 0xC6C];
    bool unknown_1348;                      // +0x1348 (shows the storage level; hypothesis)
};

// SuperWeaponTypeClass as far as this unit reads it (view).
struct UnknownSuperTypeView : public AbstractClass {
    char unknown_24[0xE1 - 0x24];
    bool unknown_e1;                        // +0xE1 (linked to another super weapon)
    int unknown_e4;                         // +0xE4 the linked one's index
};
// SuperClass as far as this unit reads it (view).
struct UnknownSuperView {
    char unknown_00[0x24];
    UnknownSuperTypeView *Type;             // +0x24 (SuperWeaponTypeClass)
    char unknown_28[0x4A - 0x28];
    Cell unknown_4a;                  // +0x4A
    char unknown_4e[0x55 - 0x4E];
    bool unknown_55;                        // +0x55

    bool unknown_func_69d390(bool is_player);   // 0x0069D390
    void unknown_func_69d090(bool is_player, Cell const *cell);   // 0x0069D090
    void unknown_func_69cfb0(int arg1);     // 0x0069CFB0
    void unknown_func_69cfc0(bool is_player);   // 0x0069CFC0
};

// SuperClass and SuperWeaponTypes (0x00A40338): shared/super.hpp.
#include "shared/super.hpp"

#include "shared/connection_points.hpp"
extern "C" GUID const IID_IConnectionPoint;     // 0x007AFD10 (UUID.LIB)
extern "C" GUID const unknown_iid_7a1ac0;       // 0x007A1AC0 (the house's outgoing interface)

// The scenario (0x00A3D290) as the house constructor reads it (view): its
// random generator at +0x218 (Random2Class, 0x006388A0 picks in a range).
struct UnknownHouseRandomView {
    int operator()(int minval, int maxval);     // 0x006388A0
    char unknown_000[0x3F4];
};
struct UnknownHouseScenarioView {
    char unknown_000[0x218];
    UnknownHouseRandomView RandomNumber;        // +0x218
    char unknown_60c[0x610 - 0x60C];
    int unknown_610;                            // +0x610 (the computer difficulty; hypothesis)
};

// FactoryClass as far as this unit calls it (RTTI FactoryClass; view).
struct UnknownFactoryView {
    void unknown_func_4b9630(bool arg1);    // 0x004B9630 (suspends production; hypothesis)
};
// The type of an object kind by index (0x00482C00; 0 for other kinds).
TechnoTypeClass *__fastcall Unknown_00482C00(int kind, int index);
// The +0xBA0 member of a building type (view).
struct UnknownBuildingTypeBA0View {
    char unknown_0000[0xBA0];
    int unknown_ba0;                        // +0x0BA0 (5 picks the second building factory; hypothesis)
};
int __fastcall Unknown_006818D0(int kind, int id, int arg3);   // 0x006818D0
// The sidebar redraw (0x0067C2D0) is SidebarClass::Unknown_0067C2D0 on Map
// (shared/map_view.hpp).

#endif
