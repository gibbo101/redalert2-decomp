// void __fastcall Print_CRCs(EventClass *event) (0x0062A360; Red Alert's Print_CRCs): writes the game state
// to SYNC<player>.TXT (houses, every infantry, unit, building and aircraft by house, the map and logic layers,
// the event that failed and the CRC of every object list), echoing each section's CRC on debug page 4.
#include "shared/queue.hpp"
#include "shared/crt_stdio.hpp"
#include "shared/crt_string.hpp"
#include "shared/lobby.hpp"
#include "shared/win_stub.hpp"
#include "shared/cpu_info.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/network_statistics.hpp"
#include "shared/building_class.hpp"
#include "shared/unit.hpp"
#include "shared/infantry.hpp"
#include "shared/cell.hpp"
#include "shared/aircraft.hpp"
#include "shared/ccini_extra.hpp"
#include "shared/display.hpp"
#include "shared/unknown_list_832470.hpp"
#include "shared/id_source.hpp"
#include "shared/color_scheme.hpp"
#include "shared/house_type.hpp"
#include "shared/mono_class.hpp"
#include "shared/target.hpp"
#include "shared/wwcrc_engine.hpp"
#include "shared/unit_type.hpp"
#include "shared/infantry_type.hpp"
#include "shared/building_type_list.hpp"
#include "shared/aircraft_type.hpp"
#include "shared/anim.hpp"
#include "shared/anim_type.hpp"
#include "shared/task_force.hpp"
#include "shared/team_type.hpp"
#include "shared/team.hpp"
#include "shared/script.hpp"
#include "shared/tag_type.hpp"
#include "shared/tag.hpp"
#include "shared/trigger_type.hpp"
#include "shared/trigger.hpp"
#include "shared/taction.hpp"
#include "shared/tevent.hpp"
#include "shared/factory_class.hpp"
#include "shared/voxel_anim_type.hpp"
#include "shared/voxel_anim.hpp"
#include "shared/warhead_type.hpp"
#include "shared/weapon_type.hpp"
#include "shared/particle.hpp"
#include "shared/particle_system.hpp"
#include "shared/bullet_type.hpp"
#include "shared/bullet.hpp"
#include "shared/waypoint_path.hpp"
#include "shared/smudge_type.hpp"
#include "shared/overlay_type.hpp"
#include "shared/light_source.hpp"
#include "shared/building_light.hpp"
#include "shared/tube.hpp"
#include "shared/side.hpp"
#include "shared/tiberium.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/vector_class.hpp"
#include "shared/abstract.hpp"
#include "shared/empulse_class.hpp"
// @ref ??_C@_04COF@None?$AA@=007ec49c
// @ref ??_C@_0BA@GEND@?$CFs?5Infantry?3?$CFx?6?$AA@=007edd50
// @ref ??_C@_0BA@MGMI@?$CF05d?5?5?5?5?5?5?$CF08x?6?$AA@=007ed8dc
// @ref ??_C@_0BB@LGDM@?$CFs?5Buildings?3?$CFx?6?$AA@=007edc08
// @ref ??_C@_0BB@NFEE@Map?5Layers?3?$CFx?5?5?6?$AA@=007edb54
// @ref ??_C@_0BE@CEAI@Random?5Number?3?$CFx?5?5?6?$AA@=007eda20
// @ref ??_C@_0BJ@CFGE@Unit?5?5?5?5?5?5?$CIType?3?$CFd?$CI?$CFs?$CJ?$CJ?5?$AA@=007eda40
// @ref ??_C@_0BJ@DBCN@Infantry?5?5?$CIType?3?$CFd?$CI?$CFs?$CJ?$CJ?5?$AA@=007edab0
// @ref ??_C@_0BJ@EJEM@Overlay?5?5?5?$CIType?3?$CFd?$CI?$CFs?$CJ?$CJ?5?$AA@=007eda94
// @ref ??_C@_0BJ@FGLF@Anim?5?5?5?5?5?5?$CIType?3?$CFd?$CI?$CFs?$CJ?$CJ?5?$AA@=007edb04
// @ref ??_C@_0BJ@GHHO@Building?5?5?$CIType?3?$CFd?$CI?$CFs?$CJ?$CJ?5?$AA@=007edae8
// @ref ??_C@_0BJ@GHKP@Terrain?5?5?5?$CIType?3?$CFd?$CI?$CFs?$CJ?$CJ?5?$AA@=007eda5c
// @ref ??_C@_0BJ@KLDK@Aircraft?5?5?$CIType?3?$CFd?$CI?$CFs?$CJ?$CJ?5?$AA@=007edb20
// @ref ??_C@_0BJ@MLPL@Smudge?5?5?5?5?$CIType?3?$CFd?$CI?$CFs?$CJ?$CJ?5?$AA@=007eda78
// @ref ??_C@_0BJ@OJOH@Bullet?5?5?5?5?$CIType?3?$CFd?$CI?$CFs?$CJ?$CJ?5?$AA@=007edacc
// @ref ??_C@_0CL@LOJP@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Tag?5CRCs?$CK?$CK?$CK?$CK?$CK?$CK@=007ed560
// @ref ??_C@_0CM@BCKK@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Tube?5CRCs?$CK?$CK?$CK?$CK?$CK@=007ed12c
// @ref ??_C@_0CM@DPGD@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Anim?5CRCs?$CK?$CK?$CK?$CK?$CK@=007ed6e8
// @ref ??_C@_0CM@LBA@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Unit?5CRCs?$CK?$CK?$CK?$CK?$CK@=007ed848
// @ref ??_C@_0CM@MMHK@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Team?5CRCs?$CK?$CK?$CK?$CK?$CK@=007ed620
// @ref ??_C@_0CN@KCIA@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Event?5CRCs?$CK?$CK?$CK?$CK@=007ed49c
// @ref ??_C@_0CN@NBEC@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Sides?5CRCs?$CK?$CK?$CK?$CK@=007ed0fc
// @ref ??_C@_0CO@FPKE@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Script?5CRCs?$CK?$CK?$CK@=007ed5bc
// @ref ??_C@_0CO@HOEA@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Bullet?5CRCs?$CK?$CK?$CK@=007ed264
// @ref ??_C@_0CO@LLBB@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Weapon?5CRCs?$CK?$CK?$CK@=007ed3a0
// @ref ??_C@_0CO@PGLL@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Action?5CRCs?$CK?$CK?$CK@=007ed4cc
// @ref ??_C@_0CP@BLDL@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Trigger?5CRCs?$CK?$CK@=007ed4fc
// @ref ??_C@_0CP@GCHD@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Warhead?5CRCs?$CK?$CK@=007ed3d0
// @ref ??_C@_0CP@LPFH@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Factory?5CRCs?$CK?$CK@=007ed46c
// @ref ??_C@_0DA@BKDI@?$HO?$HO?$HO?$HO?$HO?$HO?$HO?$HO?$HO?$HO?$HO?$HO?$HO?$HO?$HO?$HO?$HO?$HO?$HO?$HO?$HO?$HO?$HO?$HO?$HO?$HO?$HO?$HO?$HO?$HO?$HO?$HO@=007ed8ec
// @ref ??_C@_0DA@CAPN@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Aircraft?5CRCs?$CK@=007ed714
// @ref ??_C@_0DA@EFJB@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Bullet?5Type?8s?$CK@=007ed294
// @ref ??_C@_0DA@EOPO@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Infantry?5CRCs?$CK@=007ed7e0
// @ref ??_C@_0DA@IIHO@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Building?5CRCs?$CK@=007ed77c
// @ref ??_C@_0DA@JOBA@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Particle?5CRCs?$CK@=007ed338
// @ref ??_C@_0DA@MOKF@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Tag?5Type?5CRCs?$CK@=007ed58c
// @ref ??_C@_0DA@OCAE@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Em?5Pulse?5CRCs?$CK@=007ed09c
// @ref ??_C@_0DA@PKEF@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Tiberium?5CRCs?$CK@=007ed0cc
// @ref ??_C@_0DB@DEBP@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Anim?5Type?5CRCs@=007ed6b4
// @ref ??_C@_0DB@EMDN@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Unit?5Type?5CRCs@=007ed874
// @ref ??_C@_0DB@INOB@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Team?5Type?5CRCs@=007ed64c
// @ref ??_C@_0DC@IEPF@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5House?5Type?5CRC@=007ed92c
// @ref ??_C@_0DC@JDOP@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Task?5Force?5CRC@=007ed680
// @ref ??_C@_0DC@KPCA@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Voxel?5Anim?5CRC@=007ed400
// @ref ??_C@_0DC@NCOP@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5House?5CRCs?$CK?$CK?$CK?$CK@=007ed8a8
// @ref ??_C@_0DD@BFJO@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Smudge?5Type?5CR@=007ed1f8
// @ref ??_C@_0DD@KEFK@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Script?5Type?5CR@=007ed5ec
// @ref ??_C@_0DE@EIJF@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Overlay?5Type?5C@=007ed1c4
// @ref ??_C@_0DE@MPLB@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Light?5Source?5C@=007ed190
// @ref ??_C@_0DE@OADH@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5BuildingType?5C@=007ed7ac
// @ref ??_C@_0DE@OCGO@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Trigger?5Type?5C@=007ed52c
// @ref ??_C@_0DF@COJC@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Particle?5Type?5@=007ed368
// @ref ??_C@_0DF@GACF@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Infantry?5Type?5@=007ed810
// @ref ??_C@_0DF@HBDG@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Aircraft?5Type?5@=007ed744
// @ref ??_C@_0DF@IDBI@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Waypoint?5Path?5@=007ed22c
// @ref ??_C@_0DG@OIP@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Building?5Light@=007ed158
// @ref ??_C@_0DH@IJEB@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Voxel?5Anim?5Typ@=007ed434
// @ref ??_C@_0DH@OOLJ@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Particle?5Syste@=007ed300
// @ref ??_C@_0DK@PNEJ@COORD?3?$CFx?5?5?5Facing?3?$CFd?5?5?5Mission?3?$CF@=007edc1c
// @ref ??_C@_0DM@BLDP@?6?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Particle?5Syste@=007ed2c4
// @ref ??_C@_0M@EILE@Logic?3?$CFx?5?5?6?$AA@=007eda34
// @ref ??_C@_0N@BNGC@SYNC?$CF01d?4TXT?$AA@=007edf00
// @ref ??_C@_0N@HFOF@Owner?3?5NONE?6?$AA@=007edb68
// @ref ??_C@_0N@JBKL@House?5?$CFs?3?$CFx?6?$AA@=007eddf0
// @ref ??_C@_0N@MME@?$CFs?5Units?3?$CFx?6?$AA@=007edc90
// @ref ??_C@_0N@PFKN@My?5Frame?3?$CFd?6?$AA@=007ed9ec
// @ref ??_C@_0P@GBNH@Index?5?5?5?5?5CRC?6?$AA@=007ed91c
// @ref ??_C@_0P@GLCI@My?5Frame?3?$CFd?5?5?6?$AA@=007ed9fc
// @ref ?Clear@MonoClass@@QAEXXZ=0059e290
// @ref ?Mono_Page_0059da50@@YIPAVMonoClass@@H@Z=0059da50
// @ref ?Set_Cursor@MonoClass@@QAEXHH@Z=0059e240

// Canonical Mono page getter at 0x0059DA50; declared here to use the existing provider.
MonoClass *__fastcall Mono_Page_0059da50(int page);

#define PRINT_LIST_CRCS(title, list)                                                        \
    fprintf(file, title);                                                                   \
    fprintf(file, "Index     CRC\n");                                                       \
    fprintf(file, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");                       \
    delete crc;                                                                             \
    crc = new WWCRCEngine;                                                                  \
    for (i = 0; i < list.Count(); i++) {                                                    \
        list[i]->Compute_CRC(*crc);                                                         \
        fprintf(file, "%05d      %08x\n", i, *crc);                                          \
    }

// The kind name of a target, its sync ID in id.
inline char const *Sync_Target_Name(AbstractClass *target, int &id)
{
    bool is_object;
    char const *name;
    id = 0;
    name = "None";
    if (target) {
        is_object = target->AbstractFlags.IsTechno;
    }
    if (target) {
        if (is_object) {
            id = target->unknown_slot16();
        } else if (target->Kind_Of() == 11) {
            id = ((CellClass *)target)->MapCoords.Y << 16 | ((CellClass *)target)->MapCoords.X;
        }
        name = Name_From_RTTI((RTTIType)target->Kind_Of());
    }
    return name;
}

// The packed form of a target, -1 for none.
inline int Sync_Target(TargetClass const &target)
{
    if (!target.Is_Valid()) {
        return -1;
    }
    return target.As_Target();
}

void __fastcall Print_CRCs(EventClass *event)
{
    char filename[0x200];
    char time[0x80];
    char builder[0x80];
    char machine[0x80];
    int family;
    unsigned char has_mmx;
    int i, j;
    int house;

    sprintf(filename, "SYNC%01d.TXT", unknown_player_a35db4->ArrayIndex);
    Debug_Printf("Writing sync data to file %s\n", filename);
    MonoClass *mono = Mono_Page_0059da50(4);
    mono->Clear();
    mono->Set_Cursor(0, 0);
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
        fprintf(file, "CRC[%d]=%x\n", i, CRC[i]);
    }

    for (house = 0; house < Houses.Count(); house++) {
        GameCRC = 0;
        HouseClass *housep = Houses[house];
        fprintf(file, "%s: IsHuman:%d  Color:%s  ID:%d  HouseType:%s\n", (char const *)housep->IniName, housep->unknown_134,
            ColorSchemes[housep->Type->Color]->Name, housep->ArrayIndex, (char const *)HouseTypes[housep->Type->ArrayIndex]->ID);
        mono->Printf("House %s:%x\n", (char const *)housep->Type->ID, GameCRC);
    }

    for (house = 0; house < Houses.Count(); house++) {
        HouseClass *housep = Houses[house];
        GameCRC = 0;
        fprintf(file, "-------------------- %s Infantry -------------------\n", (char const *)housep->Type->ID);
        for (i = 0; i < Infantry.Count(); i++) {
            InfantryClass *infp = Infantry[i];
            if (infp->House == housep) {
                int target_id, navcom_id;
                char const *target_name;
                char const *navcom_name;
                unsigned long val = Coord_CRC(infp->Coord) + Dir_To_256(infp->unknown_2e0.Current());
                Add_CRC(&GameCRC, val);
                target_name = Sync_Target_Name(infp->unknown_228, target_id);
                navcom_name = Sync_Target_Name(infp->unknown_494, navcom_id);
                fprintf(file, "COORD:%x   Facing:%d   Mission:%d   Type:%d(%s)   Tgt:%s(%d) Speed:%d NavCom:%s(%d)\n",
                    Coord_CRC(infp->Coord), Dir_To_256(infp->unknown_2e0.Current()), infp->unknown_slot91(),
                    infp->Type->ArrayIndex, (char const *)infp->Type->ID, target_name, target_id, (int)(infp->unknown_468 * 256.0),
                    navcom_name, navcom_id);
            }
        }
        mono->Printf("%s Infantry:%x\n", (char const *)housep->Type->ID, GameCRC);
    }

    for (house = 0; house < Houses.Count(); house++) {
        HouseClass *housep = Houses[house];
        GameCRC = 0;
        fprintf(file, "-------------------- %s Units -------------------\n", (char const *)housep->Type->ID);
        for (i = 0; i < Units.Count(); i++) {
            UnitClass *unitp = Units[i];
            if (unitp->House == housep) {
                int target_id, navcom_id;
                char const *target_name;
                char const *navcom_name;
                unsigned long val = Coord_CRC(unitp->Coord) + Dir_To_256(unitp->unknown_2e0.Current())
                    + Dir_To_256(unitp->unknown_2f8.Current());
                Add_CRC(&GameCRC, val);
                target_name = Sync_Target_Name(unitp->unknown_228, target_id);
                navcom_name = Sync_Target_Name(unitp->unknown_494, navcom_id);
                fprintf(file, "COORD:%x   Facing:%d   Facing2:%d   Mission:%d   Type:%d(%s)   Tgt:%s(%d)  NavCom:%s(%d)   TrkNum:%d TrkInd:%d SpdAc:%d\n",
                    Coord_CRC(unitp->Coord), Dir_To_256(unitp->unknown_2e0.Current()), Dir_To_256(unitp->unknown_2f8.Current()),
                    unitp->unknown_slot91(), unitp->Type->ArrayIndex, (char const *)unitp->Type->ID, target_name, target_id,
                    navcom_name, navcom_id, unitp->Locomotor.Checked()->Get_Track_Number(),
                    unitp->Locomotor.Checked()->Get_Track_Index(), unitp->Locomotor.Checked()->Get_Speed_Accum());
            }
        }
        mono->Printf("%s Units:%x\n", (char const *)housep->Type->ID, GameCRC);
    }

    for (house = 0; house < Houses.Count(); house++) {
        HouseClass *housep = Houses[house];
        GameCRC = 0;
        fprintf(file, "-------------------- %s Buildings -------------------\n", (char const *)housep->Type->ID);
        for (i = 0; i < unknown_BuildingClass_list_00a40af8.Count(); i++) {
            BuildingClass *bldgp = unknown_BuildingClass_list_00a40af8[i];
            if (bldgp->House == housep) {
                unsigned long val = Coord_CRC(bldgp->Coord) + Dir_To_256(bldgp->unknown_2e0.Current());
                Add_CRC(&GameCRC, val);
                fprintf(file, "COORD:%x   Facing:%d   Mission:%d   Type:%d(%s)   Tgt:%x\n",
                    Coord_CRC(bldgp->Coord), Dir_To_256(bldgp->unknown_2e0.Current()), bldgp->unknown_slot91(),
                    bldgp->Type->ArrayIndex, (char const *)bldgp->Type->ID, Sync_Target(TargetClass(bldgp)));
            }
        }
        mono->Printf("%s Buildings:%x\n", (char const *)housep->Type->ID, GameCRC);
    }

    for (house = 0; house < Houses.Count(); house++) {
        HouseClass *housep = Houses[house];
        GameCRC = 0;
        fprintf(file, "-------------------- %s Aircraft -------------------\n", (char const *)housep->Type->ID);
        for (i = 0; i < Aircraft.Count(); i++) {
            AircraftClass *aircraftp = Aircraft[i];
            if (aircraftp->House == housep) {
                unsigned long val = Coord_CRC(aircraftp->Coord) + Dir_To_256(aircraftp->unknown_2e0.Current());
                Add_CRC(&GameCRC, val);
                fprintf(file, "COORD:%x   Facing:%d   Mission:%d   Type:%d(%s)   Tgt:%x\n",
                    Coord_CRC(aircraftp->Coord), Dir_To_256(aircraftp->unknown_2e0.Current()), aircraftp->unknown_slot91(),
                    aircraftp->Type->ArrayIndex, (char const *)aircraftp->Type->ID, Sync_Target(TargetClass(aircraftp)));
            }
        }
        mono->Printf("%s Buildings:%x\n", (char const *)housep->Type->ID, GameCRC);
    }

    GameCRC = 0;
    for (i = 0; i < 5; i++) {
        fprintf(file, ">>>> MAP LAYER %d <<<<\n", i);
        LayerClass &layer = DisplayClass::Layer[i];
        for (j = 0; j < layer.Count(); j++) {
            ObjectClass *objp = layer[j];
            if (objp->Kind_Of() == 4 && objp->Fetch_ID() == -2) continue;
            unsigned long val = Coord_CRC(objp->Coord) + objp->Kind_Of();
            Add_CRC(&GameCRC, val);
            fprintf(file, "Object %d: %x ", j, Coord_CRC(objp->Coord));
            if (objp->Kind_Of() == 0x2B || objp->Kind_Of() == 0x13) {
                fprintf(file, "%s\t(Type:%d) ", Name_From_RTTI((RTTIType)objp->Kind_Of()), 0);
            } else {
                fprintf(file, "%s\t(Type:%d(%s)) ", Name_From_RTTI((RTTIType)objp->Kind_Of()),
                    objp->Class_Of()->unknown_slot16(), (char const *)objp->Class_Of()->ID);
            }
            HouseClass *owner = objp->Owning_House();
            if (owner) {
                fprintf(file, "Owner: %s\n", (char const *)owner->Type->ID);
            } else {
                fprintf(file, "Owner: NONE\n");
            }

        }
    }
    mono->Printf("Map Layers:%x  \n", GameCRC);

    GameCRC = 0;
    fprintf(file, ">>>> LOGIC LAYER <<<<\n");
    for (i = 0; i < unknown_list_832470.Count(); i++) {
        ObjectClass *objp = unknown_list_832470[i];
        if (objp->Kind_Of() == 4 && objp->Fetch_ID() == -2) continue;
        unsigned long val = Coord_CRC(objp->Coord) + objp->Kind_Of();
            Add_CRC(&GameCRC, val);
        fprintf(file, "Object %d: %x ", i, Coord_CRC(objp->Coord));
        if (objp->Kind_Of() == 2) {
            fprintf(file, "Aircraft  (Type:%d(%s)) ", objp->Class_Of()->unknown_slot16(), (char const *)objp->Class_Of()->ID);
        } else if (objp->Kind_Of() == 4) {
            fprintf(file, "Anim      (Type:%d(%s)) ", objp->Class_Of()->unknown_slot16(), (char const *)objp->Class_Of()->ID);
        } else if (objp->Kind_Of() == 6) {
            fprintf(file, "Building  (Type:%d(%s)) ", objp->Class_Of()->unknown_slot16(), (char const *)objp->Class_Of()->ID);
        } else if (objp->Kind_Of() == 8) {
            fprintf(file, "Bullet    (Type:%d(%s)) ", objp->Class_Of()->unknown_slot16(), (char const *)objp->Class_Of()->ID);
        } else if (objp->Kind_Of() == 15) {
            fprintf(file, "Infantry  (Type:%d(%s)) ", objp->Class_Of()->unknown_slot16(), (char const *)objp->Class_Of()->ID);
        } else if (objp->Kind_Of() == 20) {
            fprintf(file, "Overlay   (Type:%d(%s)) ", objp->Class_Of()->unknown_slot16(), (char const *)objp->Class_Of()->ID);
        } else if (objp->Kind_Of() == 29) {
            fprintf(file, "Smudge    (Type:%d(%s)) ", objp->Class_Of()->unknown_slot16(), (char const *)objp->Class_Of()->ID);
        } else if (objp->Kind_Of() == 36) {
            fprintf(file, "Terrain   (Type:%d(%s)) ", objp->Class_Of()->unknown_slot16(), (char const *)objp->Class_Of()->ID);
        } else if (objp->Kind_Of() == 1) {
            fprintf(file, "Unit      (Type:%d(%s)) ", objp->Class_Of()->unknown_slot16(), (char const *)objp->Class_Of()->ID);
        }
        HouseClass *owner = objp->Owning_House();
        if (owner) {
            fprintf(file, "Owner: %s\n", (char const *)owner->Type->ID);
        } else {
            fprintf(file, "Owner: NONE\n");
        }

    }
    mono->Printf("Logic:%x  \n", GameCRC);

    int random = unknown_id_source_a3d290->RandomNumber();
    mono->Printf("Random Number:%x  \n", random);
    fprintf(file, "\nRandom Number:%d\n", random);
    mono->Printf("My Frame:%d  \n", ::Frame);
    fprintf(file, "My Frame:%d\n", ::Frame);

    if (event) {
        fprintf(file, "Offending event:\n");
        fprintf(file, "Type:         %d\n", event->Type);
        fprintf(file, "Frame:        %d\n", event->Frame);
        fprintf(file, "ID:           %x\n", (char)event->House);
        fprintf(file, "CRC:          %x\n", event->LongAt(0x07));
        fprintf(file, "CommandCount: %d\n", (unsigned short)event->ShortAt(0x0B));
        fprintf(file, "Delay:        %d\n", event->ByteAt(0x0D));
    }

    WWCRCEngine *crc = new WWCRCEngine;
    fprintf(file, "\n\n*************** House Type CRCs**************\n\n");
    fprintf(file, "Index     CRC\n");
    fprintf(file, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    for (i = 0; i < HouseTypes.Count(); i++) {
        HouseTypes[i]->Compute_CRC(*crc);
        fprintf(file, "%05d      %08x\n", i, *crc);
    }
    PRINT_LIST_CRCS("\n\n*************** House CRCs*******************\n\n", Houses)
    PRINT_LIST_CRCS("\n\n*************** Unit Type CRCs**************\n\n", UnitTypes)
    PRINT_LIST_CRCS("\n\n*************** Unit CRCs**************\n\n", Units)
    PRINT_LIST_CRCS("\n\n*************** Infantry Type CRCs**************\n\n", InfantryTypes)
    PRINT_LIST_CRCS("\n\n*************** Infantry CRCs**************\n\n", Infantry)
    PRINT_LIST_CRCS("\n\n*************** BuildingType CRCs**************\n\n", BuildingTypes)
    PRINT_LIST_CRCS("\n\n*************** Building CRCs**************\n\n", unknown_BuildingClass_list_00a40af8)
    PRINT_LIST_CRCS("\n\n*************** Aircraft Type CRCs**************\n\n", AircraftTypes)
    PRINT_LIST_CRCS("\n\n*************** Aircraft CRCs**************\n\n", Aircraft)
    fprintf(file, "\n\n*************** Anim CRCs**************\n\n");
    fprintf(file, "Index     CRC\n");
    fprintf(file, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    delete crc;
    crc = new WWCRCEngine;
    for (i = 0; i < Anims.Count(); i++) {
        AnimClass *animp = Anims[i];
        if (animp->Fetch_ID() != -2) {
            animp->Compute_CRC(*crc);
            fprintf(file, "%05d      %08x\n", i, *crc);
        }
    }
    PRINT_LIST_CRCS("\n\n*************** Anim Type CRCs**************\n\n", AnimTypes)
    PRINT_LIST_CRCS("\n\n*************** Task Force CRCs**************\n\n", TaskForces)
    PRINT_LIST_CRCS("\n\n*************** Team Type CRCs**************\n\n", TeamTypes)
    PRINT_LIST_CRCS("\n\n*************** Team CRCs**************\n\n", Teams)
    PRINT_LIST_CRCS("\n\n*************** Script Type CRCs**************\n\n", ScriptTypes)
    PRINT_LIST_CRCS("\n\n*************** Script CRCs**************\n\n", Scripts)
    PRINT_LIST_CRCS("\n\n*************** Tag Type CRCs**************\n\n", unknown_TagTypeClass_list_00abfea0)
    PRINT_LIST_CRCS("\n\n*************** Tag CRCs**************\n\n", unknown_TagClass_list_00abfe48)
    PRINT_LIST_CRCS("\n\n*************** Trigger Type CRCs**************\n\n", TriggerTypes)
    PRINT_LIST_CRCS("\n\n*************** Trigger CRCs**************\n\n", unknown_TriggerClass_list_00a40aa0)
    PRINT_LIST_CRCS("\n\n*************** Action CRCs**************\n\n", unknown_TActionClass_list_00abfd88)
    PRINT_LIST_CRCS("\n\n*************** Event CRCs**************\n\n", unknown_TEventClass_list_00ac0808)
    PRINT_LIST_CRCS("\n\n*************** Factory CRCs**************\n\n", Factories)
    PRINT_LIST_CRCS("\n\n*************** Voxel Anim Type CRCs**************\n\n", VoxelAnimTypes)
    PRINT_LIST_CRCS("\n\n*************** Voxel Anim CRCs**************\n\n", unknown_VoxelAnimClass_list_008399d0)
    PRINT_LIST_CRCS("\n\n*************** Warhead CRCs**************\n\n", unknown_WarheadTypeClass_list_00839b00)
    PRINT_LIST_CRCS("\n\n*************** Weapon CRCs**************\n\n", unknown_WeaponTypeClass_list_00839b90)
    PRINT_LIST_CRCS("\n\n*************** Particle Type CRCs**************\n\n", ParticleTypes)
    PRINT_LIST_CRCS("\n\n*************** Particle CRCs**************\n\n", unknown_ParticleClass_list_00a35e28)
    PRINT_LIST_CRCS("\n\n*************** Particle System CRCs**************\n\n", ParticleSystems)
    PRINT_LIST_CRCS("\n\n*************** Particle System Type CRCs**************\n\n", ParticleSystemTypes)
    PRINT_LIST_CRCS("\n\n*************** Bullet Type's**************\n\n", BulletTypes)
    PRINT_LIST_CRCS("\n\n*************** Bullet CRCs**************\n\n", unknown_BulletClass_list_00a40ce8)
    PRINT_LIST_CRCS("\n\n*************** Waypoint Path CRCs**************\n\n", unknown_WaypointPathClass_list_00b25590)
    PRINT_LIST_CRCS("\n\n*************** Smudge Type CRCs**************\n\n", SmudgeTypes)
    PRINT_LIST_CRCS("\n\n*************** Overlay Type CRCs**************\n\n", OverlayTypes)
    PRINT_LIST_CRCS("\n\n*************** Light Source CRCs**************\n\n", unknown_LightSourceClass_list_00a6e818)
    PRINT_LIST_CRCS("\n\n*************** Building Light CRCs**************\n\n", BuildingLights)
    PRINT_LIST_CRCS("\n\n*************** Tube CRCs**************\n\n", unknown_TubeClass_list_008661c8)
    PRINT_LIST_CRCS("\n\n*************** Sides CRCs**************\n\n", Sides)
    PRINT_LIST_CRCS("\n\n*************** Tiberium CRCs**************\n\n", unknown_TiberiumClass_list_00ac0b30)
    PRINT_LIST_CRCS("\n\n*************** Em Pulse CRCs**************\n\n", EMPulseClass::Array)
    delete crc;
    fclose(file);
}
