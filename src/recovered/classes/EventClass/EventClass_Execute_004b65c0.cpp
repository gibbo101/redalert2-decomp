// void EventClass::Execute() (0x004B65C0): carries out an event from the DoList (Red Alert's
// EventClass::Execute; the cases keep the original's source order). Inlines EventClass(int, unsigned char).
#include "shared/building_class.hpp"
#include "shared/unit.hpp"
#include "shared/cell.hpp"
#include "shared/dsurface.hpp"
#include "shared/queue.hpp"
#include "shared/session_state.hpp"
#include "shared/foot.hpp"
#include "shared/building_type_class.hpp"
#include "shared/map_view.hpp"
#include "shared/anim.hpp"
#include "shared/anim_type.hpp"
#include "shared/rules.hpp"
#include "shared/team.hpp"
#include "shared/spawn_manager.hpp"
#include "shared/string_table.hpp"
#include "shared/ww_message_box.hpp"
#include "shared/load_dlg.hpp"
#include "shared/ipx_conn.hpp"
#include "shared/options.hpp"
#include "shared/id_source.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/unknown_geometry.hpp"
// @ref _unknown_geometry_j=00855b88
// @ref _unknown_geometry_k=00855b40
// @ref _unknown_geometry_l=00855b60
// @ref ??_C@_08FILB@TXT_NONE?$AA@=007d6a84
// @ref ??_C@_0N@JPFB@SAVEGAME?4NET?$AA@=007d6a4c
// @ref ??_C@_0BA@HIPI@TXT_SAVING_GAME?$AA@=007d6a74
// @ref ??_C@_13ECNF@?$AA?5?$AA?$AA@=007d64f4
// @ref ??_C@_0BB@EKFJ@D?3?2Ra2?2Event?4CPP?$AA@=007d6ae4
// @ref ??_C@_0BD@MAJD@New?5address?5is?5?$CFs?6?$AA@=007d69bc
// @ref ??_C@_0BE@EPMK@LatencyFudge?5is?5?$CFd?6?$AA@=007d68f4
// @ref ??_C@_0BE@MNAG@TXT_SPECIAL_WARNING?$AA@=007d6ad0
// @ref ??_C@_0BF@NLEO@TXT_MULTIPLAYER_GAME?$AA@=007d6a5c
// @ref ??_C@_0BG@PAMP@New?5game?5host?5is?5?$CFls?6?$AA@=007d6934
// @ref ??_C@_0BJ@IBAJ@TXT_PLAYER_CHANGED_SPEED?$AA@=007d6a90
// @ref ??_C@_0BL@ELJE@TXT_PLAYER_CHANGED_LATENCY?$AA@=007d68d8
// @ref ??_C@_0BN@IFAJ@Received?5FALLBACKHOST?5event?6?$AA@=007d6a00
// @ref ??_C@_0BP@KEPE@Session?4PacketRouterPort?5?$DN?5?$CFd?6?$AA@=007d694c
// @ref ??_C@_0CC@HDKL@Session?4PacketRouterAddress?5?$DN?5?$CFs@=007d696c
// @ref ??_C@_0CD@EFPN@Processing?5EXIT?5event?5on?5frame?5?$CF@=007d6aac
// @ref ??_C@_0CK@LFDL@Processing?5ABOUTTOEXIT?5event?5on?5@=007d6990
// @ref ??_C@_0CL@IMLE@Executing?5LATENCYFUDGE?5event?4?5Fr@=007d6908
// @ref ??_C@_0CL@KPPK@Executing?5REMOVEPLAYER?5event?4?5Fr@=007d6a20
// @ref ??_C@_0CN@JPPC@Executing?5ADDRESSCHANGE?5event?5fo@=007d69d0
// @ref ?Unknown_00435D30@BombClass@@QAEXXZ=00435d30
// @ref ?Unknown_004E6950@HouseClass@@QAE_NHH_NABVCell@@@Z=004e6950
// @ref ?Unknown_0063F130@OwnerTalkClass@@QAE_NXZ=0063f130
// @ref ?Unknown_0063F9A0@OwnerTalkClass@@QAEXHPAVIPXAddressClass@@@Z=0063f9a0
// @ref ?Unknown_0063FBA0@OwnerTalkClass@@QAEHXZ=0063fba0
// @ref ?Unknown_0063FE20@OwnerTalkClass@@QAEXH@Z=0063fe20

// Hypotheses (to move to shared headers).
// The planning hooks: a planned event (0x00614BA0) and an event about a techno (0x00615480).
void __fastcall Planning_Event_00614BA0(EventClass *event);
void __fastcall Planning_Techno_00615480(TechnoClass *techno, EventClass *event);
// @ref ?Planning_Event_00614BA0@@YIXPAVEventClass@@@Z=00614ba0
// @ref ?Planning_Techno_00615480@@YIXPAVTechnoClass@@PAVEventClass@@@Z=00615480
extern bool unknown_a35db0;
// @ref ?unknown_a35db0@@3_NA=00a35db0
extern int unknown_a3d23c;
extern int unknown_a3d258;
// @ref ?unknown_a3d23c@@3HA=00a3d23c
// @ref ?unknown_a3d258@@3HA=00a3d258
extern bool unknown_a402b8;
extern bool unknown_a402d8;
// @ref ?unknown_a402b8@@3_NA=00a402b8
// @ref ?unknown_a402d8@@3_NA=00a402d8

void EventClass::Execute()
{
    TechnoClass *techno;
    HouseClass *house = Houses[House];
    HouseClass *hptr;
    wchar_t const *str;
    bool foot;
    wchar_t txt[80];
    int i;
    int index;

    switch (Type) {
    case 0x2A:
    case 0x2B:
    case 0x2C:
        Planning_Event_00614BA0(this);
        return;

    case 1: {
        BuildingClass *building = TargetAt(0x07).As_Building();
        Planning_Techno_00615480(building, 0);
        if (building && building->unknown_7d && !building->unknown_76 && !building->Type->FirestormWall) {
            building->unknown_44d3e0();
        }
        break;
    }

    case 2: {
        BuildingClass *building = TargetAt(0x07).As_Building();
        Planning_Techno_00615480(building, 0);
        if (building && building->unknown_7d && !building->unknown_76 && !building->Type->FirestormWall) {
            building->unknown_44d530();
        }
        break;
    }

    case 0x1E:
        techno = TargetAt(0x07).As_Techno();
        Planning_Techno_00615480(techno, 0);
        if (techno && techno->unknown_7d) {
            techno->unknown_6d6e50(TargetAt(0x0C).As_Abstract());
        }
        break;

    case 3:
        hptr = Houses[Data.LongsCell.Long1];
        if (house->Is_Ally(hptr)) {
            house->Make_Enemy(Data.LongsCell.Long1, true);
        } else {
            house->Make_Ally(Data.LongsCell.Long1, true);
        }
        break;

    case 0x2D:
        if (house) {
            house->Cheer();
        }
        break;

    case 0x18:
        if (house) {
            unknown_special_a40920 = SpecialAt(0x07);
            unknown_id_source_a3d290->unknown_000 = Data.LongsCell.Long1;
            swprintf(txt, StringTable::Load_String("TXT_SPECIAL_WARNING", 0, "D:\\Ra2\\Event.CPP", 0x3B6), house->UIName);
            unknown_session_a3d298.Messages.Add_Message(0, 0, txt, house->ColorSchemeIndex, 0x4046, 0x4B0, false);
            Map.Flag_To_Redraw(false);
        }
        break;

    case 0x15:
        techno = TargetAt(0x07).As_Techno();
        Planning_Techno_00615480(techno, 0);
        if (techno && techno->unknown_7d) {
            techno->unknown_slot97(-1);
        }
        break;

    case 0x16:
        techno = TargetAt(0x07).As_Techno();
        Planning_Techno_00615480(techno, 0);
        if (techno && techno->unknown_7d && techno->House->ArrayIndex == House) {
            if (techno->Kind_Of() == 6
                || ((techno->Kind_Of() == 1 || techno->Kind_Of() == 2) && Map[techno->Center_Coord()].unknown_4717b0())) {
                techno->unknown_slot98(-1);
            }
        }
        break;

    case 0x17:
        house->Sell_Wall(Cell(ShortAt(0x07), ShortAt(0x09)), false);
        break;

    case 0x14: {
        CoordStruct coord;
        coord.X = LongAt(0x0F);
        coord.Y = LongAt(0x13);
        coord.Z = 0;
        coord.Z = Map.Unknown_0055A280(coord);
        if (Map[coord].unknown_140 & 0x100) {
            coord.Z += unknown_geometry_j;
        }
        AnimClass *anim;
        if (Data.LongsCell.Long1 == -1) {
            anim = new AnimClass(Rules->unknown_a74, coord, 0, 1, 0x600, 0);
        } else {
            anim = new AnimClass(AnimTypes[Data.LongsCell.Long1], coord, 0, 1, 0x600, 0);
        }
        if (anim && LongAt(0x0B) != -1 && !Houses[LongAt(0x0B)]->Unknown_004F52B0()) {
            anim->unknown_17d = true;
        }
        break;
    }

    case 0x0B:
        house->Unknown_004E6950(Data.LongsCell.Long1, LongAt(0x0B), LongAt(0x0F) != 0, Cell(ShortAt(0x13), ShortAt(0x15)));
        break;

    case 0x0E:
        house->Begin_Production(Data.LongsCell.Long1, LongAt(0x0B), LongAt(0x0F) != 0, false);
        break;

    case 0x0F:
        house->unknown_func_4e63f0(Data.LongsCell.Long1, LongAt(0x0B), LongAt(0x0F) != 0);
        break;

    case 0x10:
        house->Abandon_Production(Data.LongsCell.Long1, LongAt(0x0B), LongAt(0x0F) != 0);
        break;

    case 0x11: {
        BuildingClass *building = TargetAt(0x07).As_Building();
        Planning_Techno_00615480(building, 0);
        if (building && building->unknown_7d) {
            building->unknown_slot287();
        }
        break;
    }

    case 4:
    case 5: {
        techno = TargetAt(0x07).As_Techno();
        if (ByteAt(0x1D) == 1) {
            Planning_Event_00614BA0(this);
            break;
        }
        Planning_Techno_00615480(techno, this);
        if (techno && techno->unknown_7d && techno->Strength > 0 && !techno->unknown_76) {
            ObjectClass *object = 0;
            if (TargetAt(0x0E).Is_Valid()) {
                object = TargetAt(0x0E).As_Object();
                if (object && (!object->unknown_7d || object->Strength == 0 || object->unknown_76)) {
                    break;
                }
            }
            if (TargetAt(0x13).Is_Valid()) {
                object = TargetAt(0x13).As_Object();
                if (object && (!object->unknown_7d || object->Strength == 0 || object->unknown_76)) {
                    break;
                }
            }
            if (ByteAt(0x0C) == 7 && techno->Mission == 7) {
                if (techno) {
                    foot = techno->AbstractFlags.IsFoot;
                }
                if (techno && foot) {
                    AbstractClass *dest = TargetAt(0x13).As_Abstract();
                    if (dest && dest->Kind_Of() == 6 && techno->Contact(0) == dest) {
                        break;
                    }
                }
            }
            if (!techno->unknown_370) {
                techno->unknown_slot149(3);
            } else {
                TechnoClass *contact = techno->Contact(0);
                if (contact && contact->unknown_7d && contact->Kind_Of() == 6 && ((BuildingClass *)contact)->Type->DockUnload) {
                    techno->unknown_slot149(3);
                    techno->unknown_370 = false;
                }
            }
            if (techno->unknown_3f8) {
                techno->unknown_3f8 = 0;
            }
            if (techno) {
                foot = techno->AbstractFlags.IsFoot;
            }
            if (techno && foot && ((FootClass *)techno)->Team && ByteAt(0x0C) != 0x10) {
                ((FootClass *)techno)->Team->Unknown_006B8FB0((FootClass *)techno, -1, true);
            }
            if (object && unknown_player_a35db4->Is_Ally(techno)) {
                object->unknown_slot79(7);
            }
            int mission = techno->unknown_slot268((UnknownSlot268Arg const *)this);
            techno->unknown_slot116(mission, false);
            FootClass *footp;
            if (techno->AbstractFlags.IsFoot) {
                footp = (FootClass *)techno;
            } else {
                footp = 0;
            }
            if (footp) {
                footp->unknown_498 = 0;
            }
            techno->unknown_22c = 0;
            if (ByteAt(0x0C) == 0x0B) {
                if (techno) {
                    foot = techno->AbstractFlags.IsFoot;
                }
                if (techno && foot) {
                    techno->unknown_slot220(0);
                    techno->unknown_slot260(TargetAt(0x0E).As_Abstract(), 1);
                    techno->unknown_6d6e50(TargetAt(0x0E).As_Abstract());
                    break;
                }
            }
            if (footp) {
                footp->unknown_6d6e50(0);
                footp->unknown_4c8c90();
            }
            techno->unknown_slot220(TargetAt(0x0E).As_Abstract());
            techno->unknown_slot260(TargetAt(0x13).As_Abstract(), 1);
            if (TargetAt(0x18).Is_Valid()) {
                techno->unknown_slot259((int)TargetAt(0x18).As_Abstract());
            }
        }
        break;
    }

    case 6:
        techno = TargetAt(0x07).As_Techno();
        Planning_Techno_00615480(techno, 0);
        if (techno && techno->unknown_7d && !techno->unknown_76 && !techno->unknown_370 && techno->Mission != 0x12 && techno->Mission != 0x13) {
            if (!techno->unknown_79) {
                if (!Map[CoordStruct(techno->Coord)].unknown_11c && (unsigned char)techno->unknown_slot164()) {
                    break;
                }
            }
            if (techno) {
                foot = techno->AbstractFlags.IsFoot;
            }
            if (techno && foot) {
                ((FootClass *)techno)->unknown_49c.Clear();
                ((FootClass *)techno)->unknown_4c8c90();
                ((FootClass *)techno)->unknown_418 = -1;
                ((FootClass *)techno)->unknown_576 = 0;
                ((FootClass *)techno)->unknown_41c = Cell(0, 0);
                ((FootClass *)techno)->unknown_420 = Cell(0, 0);
            }
            techno->unknown_slot152(3);
            techno->unknown_slot260(0, 1);
            techno->unknown_slot220(0);
            if (techno->SpawnManager) {
                techno->SpawnManager->Abandon_Target();
            }
            if (techno->Kind_Of() == 1 && ((UnitClass *)techno)->Type->Harvester && (techno->Mission == 10 || techno->Mission == 12)) {
                techno->unknown_slot116(5, false);
                techno->unknown_slot117();
            }
        }
        break;

    case 9:
        techno = TargetAt(0x07).As_Techno();
        Planning_Techno_00615480(techno, 0);
        if (techno && techno->unknown_7d && !techno->unknown_76 && !techno->unknown_370 && !techno->unknown_3fc) {
            if (!techno->unknown_79) {
                if (!Map[CoordStruct(techno->Coord)].unknown_11c && (unsigned char)techno->unknown_slot164()) {
                    break;
                }
            }
            if (techno->Mission != 0x12 && techno->Mission != 0x13 && techno->Kind_Of() != 2) {
                Cell cell = techno->unknown_slot104();
                if (cell != unknown_geometry_k) {
                    ObjectClass *object = Map[cell].unknown_4717b0();
                    if (object && ((BuildingClass *)object)->Type->WeaponsFactory) {
                        break;
                    }
                }
                techno->unknown_slot149(3);
                techno->unknown_slot260(0, 1);
                techno->unknown_slot220(0);
                techno->unknown_slot116(0x10, false);
            }
        }
        break;

    case 0x0A:
        techno = TargetAt(0x07).As_Techno();
        Planning_Techno_00615480(techno, 0);
        if (techno && techno->unknown_38) {
            techno->unknown_38->Unknown_00435D30();
        }
        break;

    case 7:
        techno = TargetAt(0x07).As_Techno();
        Planning_Techno_00615480(techno, 0);
        if (techno) {
            foot = techno->AbstractFlags.IsFoot;
        }
        if (techno && foot && techno->unknown_7d && !techno->unknown_76 && !techno->unknown_370) {
            ((FootClass *)techno)->unknown_59c = true;
            techno->unknown_slot87(unknown_geometry_l, true, false);
        }
        break;

    case 0x12:
        house->unknown_func_4e68d0(Data.LongsCell.Long1, Cell(ShortAt(0x0B), ShortAt(0x0D)));
        break;

    case 0x13:
        Debug_Printf("Processing EXIT event on frame %d\n", ::Frame);
        unknown_a35db0 = true;
        break;

    case 0x0C:
        if (!(unknown_flags_a3f600 & 2)) {
            unknown_int_a40d48 = 1;
        }
        break;

    case 0x0D: {
        Options.GameSpeed = Data.LongsCell.Long1;
        house = Houses[House];
        if (house != unknown_player_a35db4 && house) {
            str = StringTable::Load_String("TXT_PLAYER_CHANGED_SPEED", 0, "D:\\Ra2\\Event.CPP", 0x579);
            if (str && wcslen(str)) {
                wchar_t buffer[256];
                swprintf(buffer, str, house->UIName);
                unknown_session_a3d298.Messages.Add_Message(0, 0, buffer, house->ColorSchemeIndex, 0x4046, Rules->MessageDelay * 900.0, false);
            }
        }
        break;
    }

    case 0x1B:
        unknown_session_a3d298.MaxAhead_2c8 = ByteAt(0x0D);
        break;

    case 0x1D:
        if (unknown_int_a40d48 == 0) {
            CDTimerClass<SystemTimerClass> timer;
            timer = CDTimerClass<SystemTimerClass>(60);
            WWMessageBox(L" ").Process(StringTable::Load_String("TXT_SAVING_GAME", 0, "D:\\Ra2\\Event.CPP", 0x59A),
                StringTable::Load_String("TXT_NONE", 0, "D:\\Ra2\\Event.CPP", 0x59A), 0, 0, false);
            Unknown_006554A0("SAVEGAME.NET", StringTable::Load_String("TXT_MULTIPLAYER_GAME", 0, "D:\\Ra2\\Event.CPP", 0x59C), 0);
            while (timer > 0) {
                Service_Game_IO_00481fb0();
            }
            unknown_surface_839954->Fill(0);
            Map.Flag_To_Redraw(2);
            Map.Render();
        } else {
            Unknown_006554A0("SAVEGAME.NET", StringTable::Load_String("TXT_MULTIPLAYER_GAME", 0, "D:\\Ra2\\Event.CPP", 0x5A7), 0);
        }
        break;

    case 0x1F:
        if (House != unknown_player_a35db4->ArrayIndex) {
            delete [] (char *)Data.LongsCell.Long1;
        }
        break;

    case 0x23: {
        Debug_Printf("Executing REMOVEPLAYER event. Frame is %d\n", ::Frame);
        index = Data.LongsCell.Long1;
        house = Houses[index];
        if (unknown_game_mode_a3d298 == 4 && unknown_flag_a3fba8) {
            if (house->unknown_func_4f52f0()) {
                unknown_OwnerTalkClass_00ab6d18.Unknown_0063FE20(index);
            }
        }
        if ((unknown_game_mode_a3d298 == 4 && unknown_b2a7ec) || house->unknown_func_4f52f0()) {
            house->unknown_func_4e7e80();
        }
        break;
    }

    case 8:
        house->unknown_func_4e7e80();
        break;

    case 0x28:
        Debug_Printf("Received FALLBACKHOST event\n");
        unknown_session_a3d298.unknown_303c = Data.LongsCell.Long1;
        break;

    case 0x29: {
        Debug_Printf("Executing ADDRESSCHANGE event for player %d\n", (char)ByteAt(0x07));
        unsigned char node[6];
        unsigned char network[4];
        memset(node, 0, sizeof(node));
        memset(network, 0, sizeof(network));
        *(long *)node = LongAt(0x08);
        IPXAddressClass address(network, node, 0);
        Debug_Printf("New address is %s\n", address.As_String_00523840(&address));
        unknown_ipx_manager_a40978.Set_Connection_Address((char)ByteAt(0x07), &address);
        unknown_OwnerTalkClass_00ab6d18.Unknown_0063F9A0((char)ByteAt(0x07), &address);
        int count = unknown_session_a3d298.Players.Count();
        for (i = 0; i < count; i++) {
            if (unknown_session_a3d298.Players[i]->ID == (char)ByteAt(0x07)) {
                break;
            }
        }
        if (i < count) {
            unknown_session_a3d298.Players[i]->Address = address;
        }
        break;
    }

    case 0x27: {
        Debug_Printf("Processing ABOUTTOEXIT event on frame %d\n", ::Frame);
        if (unknown_session_a3d298.Am_I_Master(0)) {
            OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, 0x13));
            unknown_a402b8 = true;
        }
        unknown_a402d8 = true;
        int host = unknown_OwnerTalkClass_00ab6d18.Unknown_0063FBA0();
        if (host != -1) {
            HouseClass *hostp = Houses[host];
            if (hostp) {
                if (unknown_session_a3d298.Players.Count() > 2) {
                    IPXAddressClass *address = 0;
                    for (i = 0; i < unknown_session_a3d298.Players.Count(); i++) {
                        if (unknown_session_a3d298.Players[i]->ID == host) {
                            address = &unknown_session_a3d298.Players[i]->Address;
                            unknown_session_a3d298.unknown_292c = unknown_node_ids_a402ba[i];
                            break;
                        }
                    }
                    unsigned char network[4];
                    unsigned char node[6];
                    address->Get_Address(network, node);
                    unknown_forward_address_a3fbac.Set_Address(network, node, 0);
                    Debug_Printf("Session.PacketRouterAddress = %s\n", unknown_forward_address_a3fbac.As_String_00523840(0));
                    Debug_Printf("Session.PacketRouterPort = %d\n", unknown_session_a3d298.unknown_292c);
                    if (!unknown_session_a3d298.Am_I_Master(0)) {
                        unknown_ipx_manager_a40978.unknown_5277c0(&unknown_forward_address_a3fbac);
                    }
                }
                wcscpy(unknown_session_a3d298.MasterPlayerName, hostp->UIName);
                Debug_Printf("New game host is %ls\n", unknown_session_a3d298.MasterPlayerName);
                unknown_session_a3d298.MasterPlayerID = host;
                if (unknown_session_a3d298.Am_I_Master(0)) {
                    unknown_OwnerTalkClass_00ab6d18.Unknown_0063F130();
                }
            }
            unknown_session_a3d298.unknown_3048 = ::Frame;
            unknown_session_a3d298.unknown_3050 = host;
            unknown_session_a3d298.unknown_304c = ((unknown_session_a3d298.MaxAhead_2c8 + ::Frame + 10) / 10) * 10;
            unknown_session_a3d298.unknown_303c = -1;
        }
        unknown_a402d8 = false;
        break;
    }

    case 0x24: {
        Debug_Printf("Executing LATENCYFUDGE event. Frame is %d\n", ::Frame);
        unknown_a3fba4 = Data.LongsCell.Long1;
        Debug_Printf("LatencyFudge is %d\n", unknown_a3fba4);
        house = Houses[House];
        if (house != unknown_player_a35db4 && house) {
            str = StringTable::Load_String("TXT_PLAYER_CHANGED_LATENCY", 0, "D:\\Ra2\\Event.CPP", 0x6B6);
            if (str && wcslen(str)) {
                wchar_t buffer[256];
                swprintf(buffer, str, house->UIName);
                unknown_session_a3d298.Messages.Add_Message(0, 0, buffer, house->ColorSchemeIndex, 0x4046, Rules->MessageDelay * 900.0, false);
            }
        }
        break;
    }

    case 0x20:
        Data.Timing.MaxAhead -= (unknown_id_source_a3d290->unknown_000 & 0x1000) ? 10 : 0;
        if (Data.Timing.MaxAhead > unknown_session_a3d298.MaxAhead_2c8 || Data.Timing.FrameSendRate > unknown_session_a3d298.unknown_2cc) {
            unknown_a3d258 = Frame;
            unknown_a3d23c = Data.Timing.FrameSendRate * ((Frame + Data.Timing.MaxAhead + Data.Timing.FrameSendRate - 1) / Data.Timing.FrameSendRate);
        } else {
            unknown_a3d258 = 0;
            unknown_a3d23c = 0;
        }
        unknown_session_a3d298.unknown_2d0 = Data.Timing.DesiredFrameRate;
        unknown_session_a3d298.MaxAhead_2c8 = Data.Timing.MaxAhead;
        if (unknown_session_a3d298.unknown_2e0 <= unknown_session_a3d298.MaxAhead_2c8) {
            unknown_session_a3d298.unknown_2e0 = unknown_session_a3d298.MaxAhead_2c8;
        }
        unknown_session_a3d298.unknown_2cc = Data.Timing.FrameSendRate;
        break;

    case 0x21: {
        for (i = 0; i < unknown_session_a3d298.Players.Count(); i++) {
            if (House == unknown_session_a3d298.Players[i]->ID) {
                unknown_session_a3d298.Players[i]->unknown_63 = Data.ProcessTime.AverageTicks;
                break;
            }
        }
        break;
    }

    case 0x22:
        if (!(unknown_flags_a3f600 & 2)) {
            unknown_int_a40d48 = 7;
        }
        break;
    }
}
