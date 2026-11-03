// @ref ?unknown_44d900@BuildingClass@@QAE_NPBVBuildingTypeClass@@PAVHouseClass@@@Z=0044d900
// @ref ?Passes_Proximity_Check_004991D0@DisplayClass@@QBE_NPBVObjectTypeClass@@HPBVCell@@ABV3@@Z=004991d0
// @ref ?Active_Click_0049E870@DisplayClass@@QAEXPAVObjectClass@@VCell@@H@Z=0049e870
// @ref ?Clear_Selected_Objects_00482bc0@@YAXXZ=00482bc0
// @ref ?Unknown_0042E370@Unknown84E8D0@@QAEXHUCoordStruct@@H@Z=0042e370
// @ref ?Unknown_0042E740@Unknown84E8D0@@QAE_NUCoordStruct@@@Z=0042e740
// @ref ?Unknown_006F7020@@YIXPBD@Z=006f7020
// @ref ?Unknown_Click_End_006F6770@@YAXXZ=006f6770
// @ref ?Unknown_Planning_00615DE0@@YI_NXZ=00615de0
// @ref ?unknown_height_step_852948@@3HA=00852948
// @ref ??_R0?AVObjectTypeClass@@@8=007ce9c8
#include "shared/display.hpp"
#include "shared/map_view.hpp"
#include "shared/house_screen.hpp"
#include "shared/techno.hpp"
#include "shared/building_type_class.hpp"
#include "shared/map_cell.hpp"
#include "shared/event.hpp"
#include "shared/keyboard.hpp"
#include "shared/super_weapon_type.hpp"
#include "shared/vox_class.hpp"

// Existing machine contracts, source identities pending separate signature audit.
void Unknown_Click_End_006F6770();
void __fastcall Unknown_006F7020(char const *id);
bool __fastcall Unknown_Planning_00615DE0();
bool __fastcall Planning_Can_Add();
void __cdecl Clear_Selected_Objects_00482bc0();
void __fastcall Unknown_0049C3F0(ObjectClass *object);
extern bool unknown_flag_a40d45;
extern int unknown_height_step_852948;

void DisplayClass::unknown_slot48(CoordStruct const &coord, Cell const &cell, ObjectClass *object, int action, bool small_mouse)
{
    if (object && unknown_flag_a40d04 && unknown_flag_a40958 && !unknown_flag_a40d13 &&
        object->unknown_slot25(false, 0) == 5) object = 0;
    if (unknown_11a0) {
        if (unknown_11a4->Kind_Of() == 7) {
            TPoint2D<short> const *placement=&cell;
            Cell const where=placement->operator+(unknown_1174);
            unknown_117c = Passes_Proximity_Check_004991D0(unknown_11a4, unknown_11a8, unknown_1178, where);
        }
        if (unknown_11a4->Kind_Of() == 7 && object && object->Kind_Of() == 6 &&
            static_cast<BuildingClass *>(object)->unknown_44d900(static_cast<BuildingTypeClass const *>(unknown_11a4), unknown_player_a35db4))
            unknown_117c = true;
        if (unknown_117c && unknown_117d) {
            TechnoTypeClass const *techno_type = dynamic_cast<TechnoTypeClass const *>(unknown_11a4);
            bool naval = techno_type && techno_type->Naval;
            ObjectClass *pending = unknown_11a0;
            OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, 0xb, pending->Kind_Of(),
                unknown_11a4->unknown_slot16(), naval, cell + unknown_1174));
            pending = unknown_11a0;
            BuildingClass *placed;
            if (!pending) placed = 0;
            else placed = pending->Kind_Of() == 6 ? static_cast<BuildingClass *>(pending) : 0;
            Unknown_006F8A20(placed);
            if (!unknown_flag_a40d13) {
                unknown_1190 = reinterpret_cast<int>(unknown_11a4);
                unknown_118c = reinterpret_cast<int>(unknown_11a0);
                unknown_117e = cell;
                unknown_1182 = unknown_1174;
                unknown_1188 = unknown_1178;
                unknown_1194 = unknown_11a8;
                if (unknown_11a4) Map.Set_Cursor_Shape(unknown_11a4->unknown_slot36(true));
                Map.Unknown_00498F10(0);
                Map.unknown_11a0 = 0;
                Map.unknown_11a4 = 0;
                Map.unknown_11a8 = -1;
            }
        } else {
            Speech_Play_Name("EVA_CannotDeployHere", -1, -1);
        }
    } else {
        int continue_select = 0;
        if (unknown_11cb) {
            unknown_tactical_83996c->unknown_d7d = true;
            if (!WWKeyboard->Down(0x10)) {
                if (unknown_tactical_83996c->Unknown_006AA6A0()) Clear_Selected_Objects_00482bc0();
                else continue_select = 1;
            }
            unknown_tactical_83996c->Unknown_006AA610(Unknown_0049C3F0);
            TechnoClass::unknown_6d7990();
            unknown_11cb = false;
            Set_Default_Mouse(0, small_mouse);
            unknown_11cc = false;
            unknown_flag_a40d45 = true;
            if (!continue_select) { Unknown_Click_End_006F6770(); return; }
        }
        {
            if (action == 8) {
                if (!object || !unknown_objects_a40c60.Count() || !unknown_objects_a40c60[0]->Owning_House()->Unknown_004F52B0()) {
                    action = 7;
                } else if (object->unknown_77) {
                    if (Unknown_006F76B0()) Unknown_006F7020(object->Class_Of()->ID);
                    else object->unknown_slot81();
                } else {
                    if (Unknown_006F76B0()) Unknown_006F71E0(object->Class_Of()->ID);
                    else object->unknown_slot80();
                }
            }
            if ((action == 7 && object) || (action == 0 && object && object->unknown_slot76() && !object->unknown_77)) {
                if (object->Kind_Of() != 6 || static_cast<BuildingClass *>(object)->House->Unknown_004F52B0() ||
                    static_cast<BuildingClass *>(object)->unknown_5bd != 15 || static_cast<TechnoClass *>(object)->unknown_slot191()) {
                    Clear_Selected_Objects_00482bc0();
                    if (Unknown_006F76B0()) Unknown_006F71E0(object->Class_Of()->ID);
                    else object->unknown_slot80();
                    Set_Default_Mouse(0, small_mouse);
                    TechnoClass::unknown_6d7990();
                }
            }
            if (action == 0x3d) {
                CoordStruct point = cell.As_Coord(Map[cell].unknown_11b * unknown_height_step_852948);
                unknown_object_84e8d0.Unknown_0042E740(point);
            } else if (action != 0 && action != 7) {
                bool allowed = true;
                if (action != 8 && action != 10 && action != 12 && action != 13 && action != 14 && action != 15 &&
                    action != 0x21 && action != 0x22 && action != 0x14 && action != 0x25 && action != 0x26 &&
                    action != 0x27 && action != 0x28 && action != 0x29 && action != 0x41 && action != 0x3a && action != 0x3c) {
                    bool execute = Unknown_Planning_00615DE0();
                    bool add = Planning_Can_Add();
                    allowed = execute && add;
                }
                if (allowed) {
                    Active_Click_0049E870(object, cell, action);
                    TechnoClass::unknown_6d7990();
                    if (action == 0x21) {
                        if (object->Kind_Of() == 6) {
                            if (static_cast<BuildingClass *>(object)->unknown_530)
                                OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, 2, TargetClass(object)));
                            else OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, 1, TargetClass(object)));
                        }
                    } else if (action == 0x3c) {
                        if (unknown_int_a3d548 == 0) {
                            CoordStruct point = cell.As_Coord(Map[cell].unknown_11b * unknown_height_step_852948);
                            unknown_object_84e8d0.Unknown_0042E370(unknown_player_a35db4->ArrayIndex, point, -1);
                        }
                        Map.Unknown_0049CAC0(0);
                        Set_Default_Mouse(0, small_mouse);
                    } else if (action == 10) {
                        if (object->Kind_Of() == 6) OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, 0x15, TargetClass(object)));
                    } else if (action == 13) {
                        if (object) {
                            int kind = object->Kind_Of();
                            if (kind > 0 && kind <= 2) OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, 0x16, TargetClass(object)));
                        }
                    } else if (action == 12) {
                        if (object) OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, 0x16, TargetClass(object)));
                        else OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, static_cast<unsigned char>(0x17), cell));
                    }
                    SuperWeaponTypeClass *type = SuperWeaponTypeClass::From_Action(action);
                    if (type) OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, static_cast<unsigned char>(0x12), type->ArrayIndex, cell));
                }
            }
            unknown_11cc = false;
        }
    }
    Unknown_Click_End_006F6770();
}
// @ref ??_C@_0BF@JPJL@EVA_CannotDeployHere?$AA@=007d5ddc
// @ref ??_R0?AVTechnoTypeClass@@@8=007ce9e8
// @ref ??_7type_info@@6B@=007b15e4
