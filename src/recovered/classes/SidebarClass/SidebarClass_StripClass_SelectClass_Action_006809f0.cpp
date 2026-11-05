// int SidebarClass::StripClass::SelectClass::Action(unsigned flags, unsigned &key) (0x006809F0, slot 31)
// A click on a strip icon: a super weapon fires or enters targeting; a right
// click puts production on hold or cancels it; a left click places or
// releases a completed object, resumes held production or starts it.
// Unknown_0067F7C0 is the row's inlined progress read; its body is visible as
// the strip pointer held in ebp across the factory call.
#include "shared/sidebar.hpp"
#include "shared/sidebar_screen.hpp"
#include "shared/event.hpp"
#include "shared/super.hpp"
#include "shared/super_weapon_type.hpp"
#include "shared/techno.hpp"
#include "shared/techno_type.hpp"
#include "shared/factory_class_decl.hpp"
#include "shared/rules.hpp"
#include "shared/building_type_class.hpp"
#include "shared/ipx_manager.hpp"

// @ref ??_C@_0BB@ICHJ@EVA_SelectTarget?$AA@=007f3f00
// @ref ??_C@_0BD@FDCO@EVA_UnableToComply?$AA@=007f3ee0
// @ref ??_C@_0L@HCDE@EVA_OnHold?$AA@=007f3ef4
// @ref ??_C@_0N@BEKL@EVA_Canceled?$AA@=007f3f14
// @ref ??_C@_0N@MIDF@EVA_Building?$AA@=007f3ec0
// @ref ??_C@_0N@NOFG@EVA_Training?$AA@=007f3ed0
// @ref ?Unknown_004B9780@UnknownFactory@@QAEHXZ=004b9780
// @ref ?Unknown_004B9940@UnknownFactory@@QAEHXZ=004b9940
// @ref ?Unknown_004E7070@UnknownSidebarHouse@@QAE_NPAVTechnoClass@@PAVBuildingClass@@@Z=004e7070
// @ref ?Unknown_004EB580@UnknownSidebarHouse@@QAEPAVFactoryClass@@H_NH@Z=004eb580
// @ref ?Unknown_004EB620@UnknownSidebarHouse@@QAEXH_NH@Z=004eb620
// @ref ?Unknown_004EB770@UnknownSidebarHouse@@QAE_NH_NH@Z=004eb770
// @ref ?Unknown_0069D680@SuperClass@@QAEXXZ=0069d680
// @ref ?Unselect_All@@YAXXZ=00482bc0

int SidebarClass::StripClass::SelectClass::Action(unsigned flags, unsigned &key)
{
    if (Strip == 0) {
        return 1;
    }

    TechnoTypeClass *choice = 0;
    int spc = -1;

    int index = Strip->unknown_40 * 2 + Index;
    int kind = Strip->Buildables[index].unknown_04;
    int id = Strip->Buildables[index].unknown_00;
    int arg = Strip->Buildables[index].unknown_08;
    UnknownFactory *factory = Strip->Buildables[index].Factory;

    Map.Override_Mouse_Shape(0, false);

    if (index < Strip->BuildableCount) {
        if (kind != 31) {
            choice = (TechnoTypeClass *)Unknown_00482C00(kind, id);
        } else {
            spc = id;
        }
    }

    if (spc != -1) {
        if (flags & 8) {
            flags &= ~8;
        }
        if (flags & 0x10) {
            Map.unknown_11b4 = -1;
        }
        if (flags & 1) {
            if ((unsigned)spc < (unsigned)unknown_player_a35db4->Supers.Count()) {
                Unknown_Play_Sound(Rules->unknown_184);
                SuperClass *super = unknown_player_a35db4->Supers[spc];
                if (super->Unknown_0069D820()) {
                    if (unknown_player_a35db4->Supers[spc]->Type->Action == 0) {
                        Cell cell;
                        cell.X = 0;
                        cell.Y = 0;
                        OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, (unsigned char)0x12,
                            unknown_player_a35db4->Supers[spc]->Type->ArrayIndex, cell));
                    } else {
                        Map.unknown_11a0 = 0;
                        Map.unknown_11a4 = 0;
                        Map.unknown_11a8 = -1;
                        Map.Unknown_00498F10(0);
                        Map.Unknown_0049CA20(0);
                        Map.Unknown_0049C7C0(0);
                        Map.unknown_11ae = false;
                        Map.unknown_11af = false;
                        Map.unknown_11b0 = false;
                        Map.unknown_11b4 = spc;
                        Unselect_All();
                        Speech_Play_Name("EVA_SelectTarget", -1, -1);
                    }
                } else {
                    super->Unknown_0069D680();
                }
            }
        }
    } else if (choice != 0) {
        if (flags & 8) {
            flags &= ~8;
        }

        if (flags & 0x10) {
            if (factory != 0) {
                if (Map.unknown_11a0 && ((AbstractClass *)Map.unknown_11a0)->As_Techno()) {
                    Map.unknown_11a0 = 0;
                    Map.unknown_11a4 = 0;
                    Map.unknown_11a8 = -1;
                    Map.Unknown_00498F10(0);
                }
                if (!factory->Is_Building()) {
                    Unknown_Play_Sound(Rules->unknown_184);
                    Speech_Play_Name("EVA_Canceled", -1, -1);
                    OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, 0x10, kind, id, choice->Naval));
                } else {
                    Unknown_Play_Sound(Rules->unknown_184);
                    Speech_Play_Name("EVA_OnHold", -1, -1);
                    OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, 0xF, kind, id, choice->Naval));
                    Map.Column[Strip->unknown_34].unknown_38 = true;
                }
            } else {
                if (Strip->Buildables[index].unknown_10 == 1) {
                    Strip->Buildables[index].unknown_10 = 2;
                    Strip->Flag_To_Redraw();
                    Unknown_Play_Sound(Rules->unknown_184);
                    Speech_Play_Name("EVA_OnHold", -1, -1);
                    OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, 0xF, kind, id, choice->Naval));
                }
                FactoryClass *fptr = ((UnknownSidebarHouse *)unknown_player_a35db4)->Unknown_004EB580(kind, choice->Naval, arg);
                if (fptr != 0 && fptr->Has_Queued_004B9E80(choice)) {
                    Unknown_Play_Sound(Rules->unknown_184);
                    OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, 0x10, kind, id, choice->Naval));
                }
            }
        }

        if (flags & 1) {
            if (factory != 0 && (!factory->Is_Building())) {
                if (factory->Unknown_004B9900()) {
                    TechnoClass *pending = (TechnoClass *)factory->Get_Object();
                    if (!pending) {
                        if (factory->Unknown_004B9940() != -1) {
                            Map.unknown_11b4 = 1;
                        }
                    } else {
                        Unknown_Play_Sound(Rules->unknown_184);
                        BuildingClass *builder = pending->Who_Can_Build_Me(false, false);
                        if (!builder) {
                            OutList.Add(EventClass(pending->Owner(), 0x10, kind, id, choice->Naval));
                            Speech_Play_Name("EVA_UnableToComply", -1, -1);
                        } else if (pending->Kind_Of() == 6) {
                            ((UnknownSidebarHouse *)unknown_player_a35db4)->Unknown_004E7070((TechnoClass *)builder, (BuildingClass *)pending);
                        } else {
                            OutList.Add(EventClass(pending->Owner(), 0xB, kind, -1, choice->Naval, unknown_cell_ab9698));
                        }
                    }
                } else {
                    Unknown_Play_Sound(Rules->unknown_184);
                    if (kind == 16) {
                        Speech_Play_Name("EVA_Training", -1, -1);
                    } else {
                        Speech_Play_Name("EVA_Building", -1, -1);
                    }
                    TechnoTypeClass *type = (TechnoTypeClass *)Unknown_00482C00(Strip->Buildables[index].unknown_04, Strip->Buildables[index].unknown_00);
                    bool naval = type && type->Naval;
                    ((UnknownSidebarHouse *)unknown_player_a35db4)->Unknown_004EB620(kind, choice->Naval, arg);
                    OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, 0xE, Strip->Buildables[index].unknown_04,
                        Strip->Buildables[index].unknown_00, naval));
                    Strip->Buildables[index].unknown_10 = 1;
                    Strip->Buildables[index].Stage.Value = Strip->Unknown_0067F7C0(index);
                    int rate = factory->Unknown_004B9780();
                    Strip->Buildables[index].Stage.Set_Rate(rate + 1);
                    Strip->Flag_To_Redraw();
                    unknown_flag_8373c3 = true;
                }
            } else {
                factory = (UnknownFactory *)((UnknownSidebarHouse *)unknown_player_a35db4)->Unknown_004EB580(kind, choice->Naval, arg);
                TechnoTypeClass *type = (TechnoTypeClass *)Unknown_00482C00(Strip->Buildables[index].unknown_04, Strip->Buildables[index].unknown_00);
                bool naval = type && type->Naval;
                bool limited = ((UnknownSidebarHouse *)unknown_player_a35db4)->Unknown_004F4F30(type);
                bool busy;
                bool produce = false;
                if (factory != 0 && (factory->Is_Building() || ((FactoryClass *)factory)->Object != 0 || ((FactoryClass *)factory)->Queue.Count() > 0)) {
                    busy = true;
                    if (kind == 7) {
                        Speech_Play_Name("EVA_UnableToComply", -1, -1);
                    } else {
                        produce = true;
                    }
                } else {
                    busy = false;
                    if (kind == 16) {
                        if (!limited) {
                            Speech_Play_Name("EVA_Training", -1, -1);
                        }
                    } else {
                        if (!limited) {
                            Speech_Play_Name("EVA_Building", -1, -1);
                        }
                    }
                    produce = true;
                }
                if (produce) {
                    bool queued = ((UnknownSidebarHouse *)unknown_player_a35db4)->Unknown_004EB770(kind, choice->Naval, arg);
                    bool started = false;
                    if (!limited) {
                        Unknown_Play_Sound(Rules->unknown_184);
                        if (factory == 0 && !queued) {
                            ((UnknownSidebarHouse *)unknown_player_a35db4)->Unknown_004EB620(kind, choice->Naval, arg);
                            started = true;
                        }
                        OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, 0xE, Strip->Buildables[index].unknown_04,
                            Strip->Buildables[index].unknown_00, naval));
                    }
                    if (started || !queued) {
                        if (!busy && !limited) {
                            Strip->Buildables[index].unknown_10 = 1;
                            Strip->Flag_To_Redraw();
                            TechnoTypeClass *tech = (TechnoTypeClass *)Unknown_00482C00(kind, Strip->Buildables[index].unknown_00);
                            if (tech) {
                                int ahead = unknown_max_ahead_a3d560;
                                if (((UnknownSidebarIHouse *)((char *)unknown_player_a35db4 + 0x24))->Available_Money() >= tech->unknown_slot33((int)unknown_player_a35db4) * ahead / 54
                                    && tech->Who_Can_Build_Me(true, false, false, (HouseClass *)unknown_player_a35db4)) {
                                    int time = tech->unknown_slot34();
                                    if (tech->Kind_Of() == 7 && ((BuildingTypeClass *)tech)->Wall) {
                                        time = time * Rules->WallBuildSpeedCoefficient;
                                    }
                                    int least = ahead + 15;
                                    if (time <= least) {
                                        time = least;
                                    }
                                    int steps = time / 54;
                                    if (steps * 54 < least) {
                                        steps++;
                                    }
                                    if (steps < 1) {
                                        steps = 1;
                                    } else if (steps > 255) {
                                        steps = 255;
                                    }
                                    Strip->Buildables[index].Stage.Value = 0;
                                    Strip->Buildables[index].Stage.Set_Rate(steps);
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        flags = 0;
    }

    ControlClass::Action(flags, key);
    return 1;
}
