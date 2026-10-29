// void __fastcall Unknown_0062DBA0(int index, EventClass *event) (0x0062DBA0): writes the saved game
// state of slot index to SYNC<player>_<index>.TXT, with the offending event when there is one.
#include "shared/queue.hpp"
#include "shared/crt_stdio.hpp"
#include "shared/crt_string.hpp"
#include "shared/lobby.hpp"
#include "shared/win_stub.hpp"
#include "shared/cpu_info.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/network_statistics.hpp"
#include "shared/ccini_extra.hpp"
// @ref ?Frame@@3HA=00a40d2c
// @ref ??_C@_02JOHD@No?$AA@=007d7ba0
// @ref ??_C@_03PEHN@Yes?$AA@=007d7ba4
// @ref ??_C@_02IAAH@wt?$AA@=007d37d8
// @ref ??_C@_09BCDK@RA2?5Sync?6?$AA@=007ede90
// @ref ??_C@_09BEHB@Slot?3?5?$CFd?6?$AA@=007edfec
// @ref ??_C@_09JCJI@Lost?3?5?$CFd?6?$AA@=007d36b4
// @ref ??_C@_0BB@CDKO@Average?5FPS?3?5?$CFd?6?$AA@=007d37ac
// @ref ??_C@_0BC@FHHG@Delay?3?5?5?5?5?5?5?5?5?$CFd?6?$AA@=007ed960
// @ref ??_C@_0BC@HMFN@Percent?5lost?3?5?$CFd?6?$AA@=007d36a0
// @ref ??_C@_0BC@KEK@ID?3?5?5?5?5?5?5?5?5?5?5?5?$CFx?6?$AA@=007ed99c
// @ref ??_C@_0BC@KNOG@SYNC?$CF01d_?$CF03d?4TXT?$AA@=007ee004
// @ref ??_C@_0BC@LHED@CommandCount?3?5?$CFd?6?$AA@=007ed974
// @ref ??_C@_0BC@LOLH@?$CFs?7?$CIType?3?$CFd?$CI?$CFs?$CJ?$CJ?5?$AA@=007edb94
// @ref ??_C@_0BC@MALJ@Frame?3?5?5?5?5?5?5?5?5?$CFd?6?$AA@=007ed9b0
// @ref ??_C@_0BC@NNCE@CRC?3?5?5?5?5?5?5?5?5?5?5?$CFx?6?$AA@=007ed988
// @ref ??_C@_0BC@NPDI@Max?5MaxAhead?3?5?$CFd?6?$AA@=007d3798
// @ref ??_C@_0BC@PCFG@Offending?5event?3?6?$AA@=007ed9d8
// @ref ??_C@_0BC@PGHJ@Type?3?5?5?5?5?5?5?5?5?5?$CFd?6?$AA@=007ed9c4
// @ref ??_C@_0BD@DCOD@CRC?$FL?$CFd?$FN?$DN?$CFx?5?5?$CK?$CK?$CK?$CK?$CK?6?$AA@=007edfd8
// @ref ??_C@_0BD@MDFA@FrameSendRate?3?5?$CFd?6?$AA@=007ede54
// @ref ??_C@_0BD@PKEB@?6Random?5Number?3?$CFd?6?$AA@=007eda0c
// @ref ??_C@_0BE@BMJJ@Max?5round?5trip?3?5?$CFd?6?$AA@=007d3704
// @ref ??_C@_0BF@POHA@Latency?5setting?3?5?$CFd?6?$AA@=007d3780
// @ref ??_C@_0BF@PPCO@Internal?5Version?5?$CFs?6?$AA@=007ede68
// @ref ??_C@_0BG@MFIN@Address?3?5?$CFd?4?$CFd?4?$CFd?4?$CFd?6?$AA@=007ede3c
// @ref ??_C@_0BH@CKHG@Frame?5sync?5stalls?3?5?$CFd?6?$AA@=007d36dc
// @ref ??_C@_0BH@KKEM@?$DO?$DO?$DO?$DO?5LOGIC?5LAYER?5?$DM?$DM?$DM?$DM?6?$AA@=007edb3c
// @ref ??_C@_0BI@FGEC@Game?5speed?5setting?3?5?$CFd?6?$AA@=007d3768
// @ref ??_C@_0BI@IGIM@Max?5avg?5round?5trip?3?5?$CFd?6?$AA@=007d3718
// @ref ??_C@_0BI@PFEF@?$DO?$DO?$DO?$DO?5MAP?5LAYER?5?$CFd?5?$DM?$DM?$DM?$DM?6?$AA@=007edbb8
// @ref ??_C@_0BK@INCL@Command?5cound?5stalls?3?5?$CFd?6?$AA@=007d36c0
// @ref ??_C@_0BM@PENM@Local?5address?3?5?$CFd?4?$CFd?4?$CFd?4?$CFd?6?$AA@=007d374c
// @ref ??_C@_0BN@BMBN@CPU?5?$CFs?0?5MMX?5?$CFs?0?5Vendor?3?5?$CFs?$AN?6?$AA@=007d7b80
// @ref ??_C@_0BO@LLDK@Writing?5sync?5data?5to?5file?5?$CFs?6?$AA@=007edee0
// @ref ??_C@_0BP@LJMN@Release?5Build?3?5?$CFs?5by?5?$CFs?5?9?5?$CFs?$AN?6?$AA@=007d7ba8
// @ref ??_C@_0CP@PHJA@?$CFs?3?5IsHuman?3?$CFd?5?5Color?3?$CFs?5?5ID?3?$CFd?5@=007ede00
// @ref ??_C@_0DD@HGPL@?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?5?$CFs?5Units?5?9?9@=007edd1c
// @ref ??_C@_0DG@DODG@?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?5?$CFs?5Aircraft@=007edbd0
// @ref ??_C@_0DG@FADF@?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?5?$CFs?5Infantry@=007eddb8
// @ref ??_C@_0DH@FEPA@?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?9?5?$CFs?5Building@=007edc58
// @ref ??_C@_0DO@OPJH@COORD?3?$CFx?5?5?5Facing?3?$CFd?5?5?5Mission?3?$CF@=007edf48
// @ref ??_C@_0EC@IKGH@Error?5?9?5failed?5to?5open?5sync?5file@=007ede9c
// @ref ??_C@_0EN@OMGP@COORD?3?$CFx?5?5?5Facing?3?$CFd?5?5?5Mission?3?$CF@=007edf88
// @ref ??_C@_0FF@OOEE@COORD?3?$CFx?5?5?5Facing?3?$CFd?5?5?5Mission?3?$CF@=007edd60
// @ref ??_C@_0HJ@JFGH@COORD?3?$CFx?5?5?5Facing?3?$CFd?5?5?5Facing2?3?$CF@=007edca0
// @ref ??_C@_0L@DINJ@?6Name?3?5?$CFs?6?$AA@=007d3740
// @ref ??_C@_0L@LKHM@Owner?3?5?$CFs?6?$AA@=007edb78
// @ref ??_C@_0M@DBEH@CRC?$FL?$CFd?$FN?$DN?$CFx?6?$AA@=007ede30
// @ref ??_C@_0M@EDAF@Frames?3?5?$CFd?6?$AA@=007d37c0
// @ref ??_C@_0M@HFCL@?6Frame?3?5?$CFd?6?$AA@=007edff8
// @ref ??_C@_0N@CCLH@Resends?3?5?$CFd?6?$AA@=007d36f4
// @ref ??_C@_0N@PCCD@?6Version?5?$CFs?6?$AA@=007ede80
// @ref ??_C@_0O@ODMA@?$CFs?7?$CIType?3?$CFd?$CJ?5?$AA@=007edb84
// @ref ??_C@_0P@ICAG@Object?5?$CFd?3?5?$CFx?5?$AA@=007edba8
// @ref ?Internal_Version_Name_00712ed0@UnknownVersionObject@@QAEPBDXZ=00712ed0
// @ref ?Unknown_00737ad0@@YIPADPADH@Z=00737ad0
// @ref ?Unknown_00737b00@@YIPADPADH@Z=00737b00
// @ref ?Version_Name_007131d0@@YIPBDXZ=007131d0
// @ref ?unknown_cpu_text_8015a5@@3PADA=008015a5
// @ref ??_C@_0N@EICA@Owner?3?5None?6?$AA@=007edf38
// @ref ?CRC@@3PAKA=00ab5edc
// @ref ?unknown_sync_states_a780d8@@3PAUUnknownSyncState@@A=00a780d8

void __fastcall Unknown_0062DBA0(int index, EventClass *event)
{
    UnknownSyncState *state = &unknown_sync_states_a780d8[index];
    char filename[0x200];
    char time[0x80];
    char builder[0x80];
    char machine[0x80];
    int family;
    unsigned char has_mmx;
    int players;
    int house;
    int i;
    UnknownSyncObject *objects;

    sprintf(filename, "SYNC%01d_%03d.TXT", unknown_player_a35db4->ArrayIndex, index);
    Debug_Printf("Writing sync data to file %s\n", filename);
    _iobuf *file = fopen(filename, "wt");
    if (!file) {
        Debug_Printf("Error - failed to open sync file for writing. Error code %d - %s\n", GetLastError(), file);
        return;
    }

    fprintf(file, "RA2 Sync\n");
    fprintf(file, "\nVersion %s\n", Version_Name_007131d0());
    fprintf(file, "Internal Version %s\n", version_object_00a40c88.Internal_Version_Name_00712ed0());
    time[0] = 0;
    Build_Time_Text(time, sizeof(time));
    fprintf(file, "Release Build: %s by %s - %s\r\n", Unknown_00737ad0(machine, sizeof(machine)), Unknown_00737b00(builder, sizeof(builder)), time);
    family = 5;
    has_mmx = 0;
    Get_CPU_Info(&family, &has_mmx, 0, 0);
    fprintf(file, "CPU %s, MMX %s, Vendor: %s\r\n", Get_CPU_Type_Name(), has_mmx ? "Yes" : "No", unknown_cpu_text_8015a5);
    fprintf(file, "Frames: %d\n", ::Frame);
    fprintf(file, "Average FPS: %d\n", fps_sample_count_00a6eb24 ? accumulated_fps_00a6eb20 / fps_sample_count_00a6eb24 : 0);
    fprintf(file, "Max MaxAhead: %d\n", max_max_ahead_00a3d578);
    fprintf(file, "Latency setting: %d\n", unknown_a3fba4);
    fprintf(file, "Game speed setting: %d\n", unknown_a40b18);
    fprintf(file, "FrameSendRate: %d\n", unknown_frame_send_rate_a3d564);
    fprintf(file, "\nFrame: %d\n", state->Frame);
    fprintf(file, "Slot: %d\n", index);

    if (PacketTransport) {
        for (i = 0; i < PacketTransport->unknown_slot18(); i++) {
            unsigned int *address = (unsigned int *)PacketTransport->unknown_slot19(i);
            if (address) {
                unsigned int ip = *address;
                fprintf(file, "Local address: %d.%d.%d.%d\n", ip & 255, (ip >> 8) & 255, (ip >> 16) & 255, ip >> 24);
            }
        }
    }

    for (i = 0; i < 8; i++) {
        UnknownNetworkPlayerStatistics &statistics = player_statistics_00a3d584[i];
        if (statistics.unknown_00[0]) {
            NetNumType net;
            NetNodeType node;
            statistics.Address.Get_Address(net, node);
            fprintf(file, "\nName: %s\n", statistics.unknown_00);
            fprintf(file, "Address: %d.%d.%d.%d\n", node[0], node[1], node[2], node[3]);
            fprintf(file, "Max avg round trip: %d\n", statistics.MaxAverageRoundTrip);
            fprintf(file, "Max round trip: %d\n", statistics.MaxRoundTrip);
            fprintf(file, "Resends: %d\n", statistics.Resends);
            fprintf(file, "Frame sync stalls: %d\n", statistics.FrameSyncStalls);
            fprintf(file, "Command cound stalls: %d\n", statistics.CommandCountStalls);
            fprintf(file, "Lost: %d\n", statistics.Lost);
            fprintf(file, "Percent lost: %d\n", statistics.PercentLost);
        }
    }

    for (i = 0; i < 256; i++) {
        if (i == index) {
            fprintf(file, "CRC[%d]=%x  *****\n", i, CRC[i]);
        } else {
            fprintf(file, "CRC[%d]=%x\n", i, CRC[i]);
        }
    }

    players = 0;
    for (i = 0; i < 8; i++) {
        UnknownSyncHouse &h = state->Houses[i];
        if (h.ID != -1) {
            players = h.ID;
            fprintf(file, "%s: IsHuman:%d  Color:%s  ID:%d  HouseType:%s\n", h.Name, h.IsHuman, h.Color, h.ID, h.HouseType);
        }
    }

    objects = state->Objects;
    for (house = 0; house < players; house++) {
        if (state->Houses[house].ID != -1) {
            fprintf(file, "-------------------- %s Infantry -------------------\n", state->Houses[house].Name);
            UnknownSyncObject *o = objects;
            for (i = 0; i < state->Counts[0]; i++) {
                if (o->Owner == house) {
                    fprintf(file, "COORD:%x   Facing:%d   Mission:%d   Type:%d(%s)   Tgt:%s(%d) Speed:%d NavCom:%s(%d)\n",
                        o->Coord, o->Facing, o->Mission, o->Type, o->TypeName, o->Target, o->TargetID, o->Speed, o->NavCom, o->NavComID);
                }
                o++;
            }
        }
    }
    objects += state->Counts[0];
    for (house = 0; house < players; house++) {
        if (state->Houses[house].ID != -1) {
            fprintf(file, "-------------------- %s Units -------------------\n", state->Houses[house].Name);
            UnknownSyncObject *o = objects;
            for (i = 0; i < state->Counts[1]; i++) {
                if (o->Owner == house) {
                    fprintf(file, "COORD:%x   Facing:%d   Facing2:%d   Mission:%d   Type:%d(%s)   Tgt:%s(%d)  NavCom:%s(%d)   TrkNum:%d TrkInd:%d SpdAc:%d\n",
                        o->Coord, o->Facing, o->Facing2, o->Mission, o->Type, o->TypeName, o->Target, o->TargetID, o->NavCom, o->NavComID, o->TrackNumber, o->TrackIndex, o->SpeedAccum);
                }
                o++;
            }
        }
    }
    objects += state->Counts[1];
    for (house = 0; house < players; house++) {
        if (state->Houses[house].ID != -1) {
            fprintf(file, "-------------------- %s Aircraft -------------------\n", state->Houses[house].Name);
            UnknownSyncObject *o = objects;
            for (i = 0; i < state->Counts[2]; i++) {
                if (o->Owner == house) {
                    fprintf(file, "COORD:%x   Facing:%d   Mission:%d   Type:%d(%s)   Tgt:%s(%d)  NavCom:%s(%d)\n",
                        o->Coord, o->Facing, o->Mission, o->Type, o->TypeName, o->Target, o->TargetID, o->NavCom, o->NavComID);
                }
                o++;
            }
        }
    }
    objects += state->Counts[2];
    for (house = 0; house < players; house++) {
        if (state->Houses[house].ID != -1) {
            fprintf(file, "-------------------- %s Buildings -------------------\n", state->Houses[house].Name);
            UnknownSyncObject *o = objects;
            for (i = 0; i < state->Counts[3]; i++) {
                if (o->Owner == house) {
                    fprintf(file, "COORD:%x   Facing:%d   Mission:%d   Type:%d(%s)   Tgt:%s(%d)\n",
                        o->Coord, o->Facing, o->Mission, o->Type, o->TypeName, o->Target, o->TargetID);
                }
                o++;
            }
        }
    }

    for (int layer = 0; layer < 5; layer++) {
        fprintf(file, ">>>> MAP LAYER %d <<<<\n", layer);
        for (i = 0; i < state->LayerCounts[layer]; i++) {
            UnknownSyncLayerObject &o = state->Layers[layer][i];
            fprintf(file, "Object %d: %x ", i, o.Value);
            if (o.RTTI == 0x2B || o.RTTI == 0x13) {
                fprintf(file, "%s\t(Type:%d) ", Name_From_RTTI((RTTIType)o.RTTI), 0);
            } else {
                fprintf(file, "%s\t(Type:%d(%s)) ", Name_From_RTTI((RTTIType)o.RTTI), o.Type, o.Name);
            }
            if (o.Owner != -1) {
                fprintf(file, "Owner: %s\n", state->Houses[o.Owner].Name);
            } else {
                fprintf(file, "Owner: None\n");
            }
        }
    }

    fprintf(file, ">>>> LOGIC LAYER <<<<\n");
    for (i = 0; i < state->LogicCount; i++) {
        UnknownSyncLayerObject &o = state->Logic[i];
        fprintf(file, "Object %d: %x ", i, o.Value);
        if (o.RTTI == 0x2B || o.RTTI == 0x13) {
            fprintf(file, "%s\t(Type:%d) ", Name_From_RTTI((RTTIType)o.RTTI), 0);
        } else {
            fprintf(file, "%s\t(Type:%d(%s)) ", Name_From_RTTI((RTTIType)o.RTTI), o.Type, o.Name);
        }
        if (o.Owner != -1) {
            fprintf(file, "Owner: %s\n", state->Houses[o.Owner].Name);
        } else {
            fprintf(file, "Owner: None\n");
        }
    }

    fprintf(file, "\nRandom Number:%d\n", state->RandomNumber);
    if (event) {
        fprintf(file, "Offending event:\n");
        fprintf(file, "Type:         %d\n", event->Type);
        fprintf(file, "Frame:        %d\n", event->Frame);
        fprintf(file, "ID:           %x\n", (char)event->House);
        fprintf(file, "CRC:          %x\n", event->LongAt(0x07));
        fprintf(file, "CommandCount: %d\n", (unsigned short)event->ShortAt(0x0B));
        fprintf(file, "Delay:        %d\n", event->ByteAt(0x0D));
    }
    fclose(file);
}
