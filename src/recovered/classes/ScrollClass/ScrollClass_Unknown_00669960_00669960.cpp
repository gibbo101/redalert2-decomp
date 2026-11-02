// int ScrollClass::Unknown_00669960(Cell const &cell, ObjectClass *object, bool arg3) (0x00669960)
// The action a left click would take on the object or cell under the mouse (TibSun What_Action):
// the selected object's answer, else the select/beacon/repair/sell/power/waypoint/super/pending modes.
#include "shared/scroll.hpp"
#include "shared/mouse_class.hpp"
#include "shared/cell.hpp"
#include "shared/building_class.hpp"
#include "shared/techno.hpp"
#include "shared/techno_type.hpp"
#include "shared/building_type_class.hpp"
#include "shared/house.hpp"
#include "shared/overlay_type.hpp"
#include "shared/super_weapon_type.hpp"
#include "shared/waypoint_path.hpp"
#include "shared/keyboard.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/map_view.hpp"
// The modifier globals are ints (pushed as dwords); WWKeyboardClass::Down takes a KeyNumType.
inline bool Scroll_Key_Down(int key)
{
    return WWKeyboard->Down(key);
}
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?unknown_objects_a40c60@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00a40c60
// @ref ?Unknown_0051A690@@YIPAVObjectClass@@PBVCell@@PAV1@@Z=0051a690
// @ref ?As_Techno_0040dbd0@@YIPAVTechnoClass@@PAVAbstractClass@@@Z=0040dbd0
// @ref ?unknown_47c2e0@CellClass@@QBE_NH@Z=0047c2e0
// @ref ?Unknown_0042E860@Unknown84E8D0@@QAEPAVUnknownBeacon@@UCoordStruct@@@Z=0042e860
// @ref ?unknown_object_84e8d0@@3VUnknown84E8D0@@A=0084e8d0
// @ref ?Unknown_004F3120@HouseClass@@QBE_NXZ=004f3120
// @ref ?OverlayTypes@@3V?$DynamicVectorClass@PAVOverlayTypeClass@@@@A=00a35de8
// @ref ?Houses@@3V?$DynamicVectorClass@PAVHouseClass@@@@A=00a32298
// @ref ?SuperWeaponTypes@@3V?$DynamicVectorClass@PAVSuperWeaponTypeClass@@@@A=00a40338
// @ref ?KeyForceMove1@@3HA=00a40bb4
// @ref ?KeyForceMove2@@3HA=00a40bb8
// @ref ?WWKeyboard@@3PAVWWKeyboardClass@@A=00832468
// @ref _unknown_geometry_g=00ab70c8
// @ref ?Next_Waypoint@WaypointPathClass@@QAEPAVWaypointClass@@PBV2@@Z=00724f80
// @ref ?unknown_func_4ed2b0@HouseClass@@QAE_NPAVWaypointClass@@PAHPAD@Z=004ed2b0

int ScrollClass::Unknown_00669960(Cell const &cell, ObjectClass *object, bool arg3)
{
    int action = 0;
    if (unknown_objects_a40c60.Count()) {
        if (object != 0) {
            action = Unknown_0051A690(0, object)->unknown_slot28(object, false);
        } else {
            action = Unknown_0051A690(&cell, 0)->unknown_slot27(&cell, arg3, false);
        }
    } else {
        bool visible = true;
        TechnoClass *techno = As_Techno_0040dbd0(object);
        if (techno != 0 && !techno->unknown_372) {
            if ((techno->unknown_1b8 == 2 && !Map[techno->Center_Coord()].unknown_47c2e0(unknown_player_a35db4->ArrayIndex))
                    || techno->unknown_slot32()->Invisible) {
                visible = false;
            }
        }

        if (object != 0 && object->Kind_Of() == 6 && !((BuildingClass *)object)->unknown_372
                && ((BuildingClass *)object)->unknown_5bd == 15
                && !Map[techno->Center_Coord()].unknown_47c2e0(unknown_player_a35db4->ArrayIndex)) {
            visible = false;
        }
        if (visible) {
            if (object != 0 && object->unknown_slot76()
                    && (object->Kind_Of() != 6 || !((BuildingClass *)object)->unknown_5b7)
                    && (techno == 0 || !techno->unknown_32c)) {
                action = 7;
            }
            if (unknown_object_84e8d0.Unknown_0042E860(CoordStruct(cell.X * 256 + 128, cell.Y * 256 + 128, Map[cell].unknown_11b * unknown_geometry_g))) {
                action = 0x3D;
            }
        }

        if (Map.unknown_11ac) {
            if (object != 0 && object->Owning_House() != 0 && object->Owning_House()->Unknown_004F52B0() && object->unknown_slot36()) {
                action = 10;
            } else {
                action = 15;
            }
        }

        if (Map.unknown_11ae) {
            action = 0x22;
            if (object != 0 && object->Owning_House() != 0 && object->Owning_House()->Unknown_004F52B0()
                    && object->Kind_Of() == 6 && object->unknown_slot76() && !object->unknown_slot31()) {
                BuildingTypeClass *type = ((BuildingClass *)object)->Type;
                if (type->TogglePower && (type->PowerDrain_c6c > 0 || type->Powered)) {
                    action = 0x21;
                }
            }
        }

        WaypointClass *waypoint = unknown_player_a35db4->unknown_func_4ed200(cell);
        if (Map.unknown_11af) {
            bool force = Scroll_Key_Down(KeyForceMove1) || Scroll_Key_Down(KeyForceMove2);
            int path = -1;
            char position;
            if (waypoint != 0) {
                unknown_player_a35db4->unknown_func_4ed2b0(waypoint, &path, &position);
            }
            if (Map.unknown_11b8 != 0) {
                action = 0x30;
            } else if (force && waypoint != 0 && path == unknown_player_a35db4->unknown_154
                    && unknown_player_a35db4->Unknown_004F3120()
                    && unknown_player_a35db4->WaypointPaths[path]->Next_Waypoint(waypoint) != 0) {
                action = 0x2F;
            } else if (waypoint != 0) {
                action = 0x2E;
            } else if (unknown_player_a35db4->unknown_154 != -1 && unknown_player_a35db4->Unknown_004F3120()
                    && Map.Unknown_0055A660(cell, true)) {
                action = 0x2A;
            } else {
                action = 0x2B;
            }
        }

        if (Map.unknown_11b0) {
            action = 0x3C;
        }

        if (Map.unknown_11ad) {
            if (object != 0 && object->Owning_House() != 0 && object->Owning_House()->Unknown_004F52B0() && object->unknown_slot37()) {
                if (object->Kind_Of() == 6) {
                    action = object->unknown_slot31() ? 14 : 12;
                } else {
                    action = 13;
                }
            } else {
                CoordStruct coord(cell.X * 256 + 128, cell.Y * 256 + 128, 0);
                coord.Z = Map.Unknown_0055A280(coord);
                if (!Map.Unknown_00568140(coord) && !Map.Unknown_005683C0(coord)
                        && Map[cell].OverlayIndex != -1 && OverlayTypes[Map[cell].OverlayIndex]->Wall
                        && Map[cell].unknown_50 != -1 && Houses[Map[cell].unknown_50]->Unknown_004F52B0()) {
                    action = 12;
                } else {
                    action = 14;
                }
            }
        }

        if (Map.unknown_11b4 != -1) {
            int super_action = SuperWeaponTypes[Map.unknown_11b4]->unknown_slot27(&cell, object);
            if (super_action != 0) {
                action = super_action;
            }
        }
        if (action == 0 && waypoint != 0) {
            action = 0x2C;
        }
        if (Map.unknown_11a4 != 0) {
            action = 0;
        }
    }
    return action;
}
