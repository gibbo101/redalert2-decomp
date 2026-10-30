// House004E6950: completed production placement, 1460 body bytes and 12 frozen NOPs.
// RA2 additions and call/storage order checked against the exact target; TS is shape evidence only.
#include "shared/house.hpp"
#include "shared/house_views.hpp"
#include "shared/map_view.hpp"
#include "shared/building_class.hpp"
#include "shared/building_type_class.hpp"
#include "shared/overlay_type.hpp"
#include "shared/factory_class.hpp"
#include "shared/tactical.hpp"
#include "shared/mouse.hpp"
#include "shared/radar_event.hpp"
#include "shared/sound_play.hpp"
#include "shared/vox_class.hpp"
#include "shared/rules.hpp"
#include "shared/debug_printf.hpp"
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ??_C@_0DG@ONPI@Failed?5to?5exit?5object?5from?5facto@=007da4e0
// @ref ??_C@_0O@HJPD@EVA_UnitReady?$AA@=007da4d0
// @ref ??_C@_0BF@JPJL@EVA_CannotDeployHere?$AA@=007d5ddc
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0056A480@MapClass@@QAEXABVCell@@PAVHouseClass@@PAVBuildingTypeClass@@@Z=0056a480
// @ref ?Unknown_0056A660@MapClass@@QAEXABVCell@@PAVHouseClass@@PAVBuildingTypeClass@@@Z=0056a660
// @ref ?Set_Cursor_Shape@DisplayClass@@QAEXPBVCell@@@Z=00499070

extern Rect unknown_rect_839630; // Existing shared/display.hpp view rectangle, 00839630.

bool HouseClass::Unknown_004E6950(int kind, int index, bool naval, Cell const &cell)
{
    bool placed = false;
    TechnoClass *tech = 0;
    int category = unknown_func_4eb550(kind, index);
    FactoryClass *factory = unknown_func_4eb580(kind, naval, category);
    if (factory && factory->Is_Complete_004B9900()) {
        tech = factory->Get_Object();
        if (cell == unknown_cell_a40f10 || cell == Cell(-1, -1)) {
            if (tech) {
                BuildingClass *builder = tech->Who_Can_Build_Me(false, true);
                if (!builder && tech->Kind_Of() == 2) {
                    builder = tech->Who_Can_Build_Me(true, true);
                }
                if (builder) {
                    int exit = builder->unknown_slot62(tech);
                    if (exit == 2 || (exit == 1 && builder->Kind_Of() == 6 && builder->unknown_41c != 0)) {
                        if (Is_Player_Control()) {
                            if (Unknown_0063B5B0(6, Coord_Cell(builder->Center_Coord()))) {
                                Speech_Play_Name("EVA_UnitReady", -1, -1);
                            }
                        }
                        factory->Release_Completed_004B9970();
                        Abandon_Production(kind, index, naval);
                        placed = true;
                    } else {
                        if (tech->Kind_Of() != 6) {
                            Debug_Printf("Failed to exit object from factory - refunding money\n");
                            Abandon_Production(kind, index, naval);
                        }
                        return placed;
                    }
                }
            }
        } else {
            Cell location = cell;
            if (tech) {
                BuildingClass *builder = tech->Who_Can_Build_Me(false, false);
                if (builder) {
                    builder->unknown_slot150(2, tech);
                    if (tech->unknown_slot53(&UnknownCoord434820(location.X * 256 + 128, location.Y * 256 + 128, 0), 0)) {
                        if (tech->Kind_Of() == 6) {
                            BuildingTypeClass *type = ((BuildingClass *)tech)->Type;
                            if (type->FirestormWall) {
                                Map.Unknown_0056A480(location, this, type);
                            } else if (type->ToOverlay && type->ToOverlay->Wall) {
                                Map.Unknown_0056A660(location, this, type);
                            }
                        }
                        factory->Release_Completed_004B9970();
                        tech->unknown_slot150(12, builder);
                        Abandon_Production(kind, index, naval);
                        placed = true;
                        if (unknown_player_a35db4 == this) {
                            if (tech->unknown_7d && !tech->unknown_373) tech->unknown_slot96(this);
                            Voc_Play(Rules->BuildingSlam, 1.0f, 0x2000, 0);
                            if (!unknown_a40d13) {
                                Map.Set_Cursor_Shape(0);
                                Map.unknown_118c = 0;
                                Map.unknown_1190 = 0;
                            }
                            Map.Unknown_00498F10(0);
                            Map.unknown_11a0 = 0;
                            Map.unknown_11a4 = 0;
                            Map.unknown_11a8 = -1;
                        }
                    } else {
                        placed = false;
                        if (this == unknown_player_a35db4) Speech_Play_Name("EVA_CannotDeployHere", -1, -1);
                        if (!unknown_a40d13 && this == unknown_player_a35db4) {
                            Map.unknown_11a0 = Map.unknown_118c;
                            Map.unknown_11a4 = Map.unknown_1190;
                            Map.unknown_11a8 = Map.unknown_1194;
                            Map.unknown_1170 = Map.unknown_117e;
                            Map.unknown_1174 = Map.unknown_1182;
                            Map.unknown_1178 = Map.unknown_1188;
                            if (Map.unknown_1190) {
                                Map.Unknown_00498F10(((ObjectTypeClass *)Map.unknown_1190)->unknown_slot36(1));
                                Point2D xy = WWMouse->Get_Mouse_XY();
                                unknown_tactical_83996c->Unknown_006A2B10(xy);
                                xy -= Point2D(unknown_rect_839630.X, unknown_rect_839630.Y);
                                Cell mouse_cell;
                                CoordStruct mouse_coord;
                                ObjectClass *object = 0;
                                bool shadow, small;
                                Map.Unknown_00669650(xy, mouse_cell, mouse_coord, object, shadow, small);
                                Map.Unknown_004994D0(mouse_cell);
                            }
                            Map.Set_Cursor_Shape(0);
                            Map.unknown_118c = 0;
                            Map.unknown_1190 = 0;
                        }
                    }
                    builder->unknown_slot149(3);
                }
            }
        }
        if (placed) {
            Just_Built(tech);
            BuildingClass *builder = tech->Who_Can_Build_Me(false, true);
            if (builder && builder->Kind_Of() == 6) {
                int sound = builder->Type->CreateUnitSound;
                if (sound != -1) Voc_Static_Add(sound, tech->Position_Coord_004f3f40(), 0);
            }
        }
    }
    return placed;
}
