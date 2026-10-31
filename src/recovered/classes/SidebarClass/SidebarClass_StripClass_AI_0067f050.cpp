// bool SidebarClass::StripClass::AI(int &input, Point2D const &xy) (0x0067F050)
// The strip's per-frame update: scrolling, the flash, the tab flash and the build clocks.
#include "shared/sidebar.hpp"
#include "shared/sidebar_screen.hpp"
#include "shared/sidebar_building.hpp"
#include "shared/event.hpp"
#include "shared/house.hpp"
#include "shared/super.hpp"
#include "shared/techno.hpp"
#include "shared/techno_type.hpp"
#include "shared/vox_class.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_004B9420@UnknownFactory@@QAE_NXZ=004b9420
// @ref ?Unknown_004B9430@UnknownFactory@@QAE_NXZ=004b9430
// @ref ?Unknown_004B9900@UnknownFactory@@QAE_NXZ=004b9900
// @ref ?Unknown_0069D820@SuperClass@@QAE_NXZ=0069d820
// @ref ?Unknown_006F8A00@@YIXPAVBuildingClass@@@Z=006f8a00
// @ref ?unknown_cell_ab9698@@3VCell@@A=00ab9698
// @ref ??_C@_0BJ@IPHE@EVA_ConstructionComplete?$AA@=007f3e5c

bool SidebarClass::StripClass::AI(int &input, Point2D const &xy)
{
    bool redraw = false;

    if (!unknown_3b && unknown_44) {
        int rows = Map.Unknown_006820A0();
        if (BuildableCount <= rows * 2) {
            unknown_44 = 0;
        } else if (unknown_44 < 0) {
            if (!unknown_40) {
                unknown_44 = 0;
            } else {
                unknown_44++;
                unknown_3a = false;
                unknown_3b = true;
                unknown_40--;
                unknown_48 = 0;
            }
        } else if ((unknown_40 + rows) * 2 >= BuildableCount) {
            unknown_44 = 0;
        } else {
            unknown_44--;
            unknown_48 = unknown_abcd6c;
            unknown_3a = true;
            unknown_3b = true;
        }
    }

    if (unknown_3b) {
        if (unknown_3a) {
            unknown_48 -= unknown_abcd80;
            if (unknown_48 <= 0) {
                unknown_3b = false;
                unknown_48 = 0;
                unknown_40++;
            }
        } else {
            unknown_48 += unknown_abcd80;
            if (unknown_48 >= unknown_abcd6c) {
                unknown_3b = false;
                unknown_48 = 0;
            }
        }
        redraw = true;
    }

    if (unknown_3c != -1) {
        if (unknown_00.Graphic_Logic()) {
            redraw = true;
            if (unknown_00.Fetch_Stage() >= 7) {
                unknown_00.Set_Rate(0);
                unknown_00.Set_Stage(0);
                unknown_3c = -1;
            }
        }
    }

    if (Map.unknown_4edc > Frame) {
        redraw = true;
    }

    if (unknown_34 == 0 || unknown_34 == 1) {
        for (int index = 0; index < BuildableCount; index++) {
            if (Buildables[index].unknown_04 == 31) {
                SuperClass *super = unknown_player_a35db4->Supers[Buildables[index].unknown_00];
                if (super && super->Unknown_0069D820()) {
                    goto flash;
                }
            } else {
                UnknownFactory *factory = Buildables[index].Factory;
                if (factory && factory->Unknown_004B9900()) {
                    ObjectClass *object = factory->Get_Object();
                    if (object && object->Kind_Of() == 6) {
                        goto flash;
                    }
                }
            }
        }
        unknown_buttons_ab9508[unknown_34].Unknown_00675300();
    }
    goto building;
flash:
    {
        int frame = Frame;
        int length = 10 - frame % 10;
        unknown_buttons_ab9508[unknown_34].Unknown_006752D0(10, length, ((frame + length) / 10) % 2 == 0);
        Map.unknown_4ee3 = true;
        Map.Flag_To_Redraw(false);
    }
building:

    if (unknown_39) {
        for (int index = 0; index < BuildableCount; index++) {
            UnknownFactory *factory = Buildables[index].Factory;
            if (factory && factory->Unknown_004B9430()) {
                redraw = true;
                if (factory->Unknown_004B9900()) {
                    TechnoClass *pending = (TechnoClass *)factory->Get_Object();
                    if (pending) {
                        switch (pending->Kind_Of()) {
                        case 6:
                            Speech_Play_Name("EVA_ConstructionComplete", -1, -1);
                            Unknown_006F8A00(As_Building(pending));
                            break;
                        case 1:
                        case 2:
                        case 15:
                            OutList.Add(EventClass(pending->Owner(), 11, pending->Kind_Of(), -1,
                                pending->unknown_slot32()->Naval, unknown_cell_ab9698));
                            Buildables[index].unknown_10 = 0;
                            break;
                        }
                    }
                }
            }
        }
    }

    for (int index = 0; index < BuildableCount; index++) {
        if (Buildables[index].unknown_10 == 1) {
            UnknownFactory *factory = Buildables[index].Factory;
            if (factory && (!factory->unknown_34 || factory->unknown_6c || factory->Unknown_004B9420())) {
                Buildables[index].Stage.Set_Rate(0);
                Buildables[index].Stage.Set_Stage(0);
            }
            if (Buildables[index].Stage.Graphic_Logic()) {
                redraw = true;
                if (Buildables[index].Stage.Fetch_Stage() >= 53) {
                    Buildables[index].Stage.Set_Rate(0);
                }
            }
        }
    }

    if (redraw) {
        Map.Unknown_0067C2D0(Map.unknown_4ed8);
        Flag_To_Redraw();
        Map.unknown_4ee3 = true;
        unknown_flag_abcd84 = true;
    }
    return redraw;
}
