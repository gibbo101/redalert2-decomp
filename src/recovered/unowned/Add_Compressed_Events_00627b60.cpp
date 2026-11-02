// @ref ??_C@_0BI@FBBB@?5?5New?5MEGAMISSION?5run?3?6?$AA@=007ecd58
// @ref ??_C@_0CB@NMEI@?6Frame?5?$CFd?3?5Building?5Send?5Packet?6@=007ecda4
// @ref ??_C@_0CL@OEIH@Compress?3?5Out?5of?5buffer?5space?5at@=007ecc0c
// @ref ??_C@_0DD@HJDM@?5?5?5?5?5?5adding?5Whom?3?$CFx?5Mission?3?$CFs?5@=007ecd70
// @ref ??_C@_0DO@KOHI@Compress?3?5Ended?5megamission?5run?5@=007ecc38
// @ref ??_C@_0EF@GFIK@Compress?3?5Found?5early?5repeat?5meg@=007ecc78
// @ref ??_C@_0EK@GOKC@Compress?3?5New?5megamission?5run?5?9?5@=007ecd0c
// @ref ??_C@_0EM@BCFF@Compress?3?5Non?9megamission?5event?5@=007eccc0
// int __fastcall Add_Compressed_Events(void *buf, int bufsize, int frame_delay, int size, int cap, int *added) (0x00627B60)
#include "shared/queue.hpp"
#include "shared/crt_memory.hpp"
#include "shared/mission.hpp"
// @ref ?Name_From_Mission@MissionClass@@SIPBDH@Z=00595020
// @ref ?Unknown_006279D0@@YI_NPAEPAHPAD2_N@Z=006279d0
// @ref ?unknown_event_lengths_7d659c@@3PAEA=007d659c
extern unsigned char unknown_event_lengths_7d659c[];
extern bool unknown_flag_a40d1c;    // 0x00A40D1C (trace the events)
// @ref ?unknown_flag_a40d1c@@3_NA=00a40d1c

#ifndef RA2_QUEUE_SAME_TARGET
#define RA2_QUEUE_SAME_TARGET
inline bool Same_Target(TargetClass const &a, TargetClass const &b)
{
    return a.Kind == b.Kind && a.ID == b.ID;
}
#endif

int __fastcall Add_Compressed_Events(void *buf, int bufsize, int frame_delay, int size, int cap, int *added)
{
    int num = 0;
    unsigned char eventtype;
    EventClass prevevent;
    int datasize;
    int storedsize;
    unsigned char *unitsptr = 0;
    unsigned char numunits = 0;
    bool missiondup = false;
    bool cached = false;
    char mission;
    char *units;
    char *whom;

    memset(&prevevent, 0, sizeof(EventClass));
    units = 0;
    whom = 0;

    if (unknown_flag_a40d1c) {
        Debug_Printf("\nFrame %d: Building Send Packet\n", ::Frame);
    }

    while (OutList.Count && num < cap) {
        eventtype = OutList.First().Type;
        datasize = unknown_event_lengths_7d659c[eventtype];
        if (eventtype == 0x1F) {
            storedsize = datasize + 1 + OutList.First().LongAt(0x0B);
        } else {
            storedsize = datasize + 1;
        }

        if (prevevent.Type == 4) {
            if (eventtype == 4) {
                if (!cached
                    && (mission = OutList.First().ByteAt(0x0C)) == (char)prevevent.ByteAt(0x0C)
                    && Same_Target(OutList.First().TargetAt(0x0E), prevevent.TargetAt(0x0E))
                    && Same_Target(OutList.First().TargetAt(0x13), prevevent.TargetAt(0x13))) {
                    if (unknown_flag_a40d1c) {
                        Debug_Printf("      adding Whom:%x Mission:%s Target:%x Dest:%x\n",
                            OutList.First().TargetAt(0x07).Encode(),
                            MissionClass::Name_From_Mission(mission),
                            OutList.First().TargetAt(0x0E).Encode(),
                            OutList.First().TargetAt(0x13).Encode());
                    }
                    datasize = 5;
                    storedsize = datasize;
                    numunits++;
                    missiondup = true;
                } else {
                    if (unknown_flag_a40d1c) {
                        Debug_Printf("  New MEGAMISSION run:\n");
                    }
                    Debug_Printf("Compress: New megamission run - checking for previous repeat of %d units\n", numunits);
                    Unknown_006279D0(&numunits, &size, whom, units, true);
                    *unitsptr = numunits;
                    unitsptr = (unsigned char *)buf + size + 1;
                    storedsize += 1;
                    numunits = 1;
                    missiondup = false;
                }
            } else {
                Debug_Printf("Compress: Non-megamission event - checking for previous repeat of %d units\n", numunits);
                Unknown_006279D0(&numunits, &size, whom, units, true);
                *unitsptr = numunits;
                unitsptr = 0;
                numunits = 0;
                missiondup = false;
            }
        } else if (eventtype == 4) {
            if (unknown_flag_a40d1c) {
                Debug_Printf("  New MEGAMISSION run:\n");
            }
            unitsptr = (unsigned char *)buf + size + 1;
            storedsize += 1;
            numunits = 1;
            missiondup = false;
        }
        cached = false;

        if (size + storedsize > bufsize) {
            if (eventtype == 4 && missiondup) {
                numunits--;
                Debug_Printf("Compress: Out of buffer space at %d units\n", numunits);
                Unknown_006279D0(&numunits, &size, whom, units, true);
                *unitsptr = numunits;
            }
            break;
        }

        if (unknown_session_a3d2ac == 2) {
            OutList.First().Frame = ((::Frame + frame_delay + (unknown_frame_send_rate_a3d564 - 1)) / unknown_frame_send_rate_a3d564)
                * unknown_frame_send_rate_a3d564;
        } else {
            OutList.First().Frame = ::Frame + frame_delay;
        }
        OutList.First().House = unknown_player_a35db4->ArrayIndex;
        OutList.First().IsExecuted = 0;

        if (!DoList.Add(OutList.First(), OutList.Timings[OutList.Head])) {
            break;
        }

        switch (eventtype) {
        case 4:
            if (missiondup) {
                *unitsptr = numunits;
                memcpy((char *)buf + size, &OutList.First().TargetAt(0x07), datasize);
                size += datasize;
                if (OutList.Count != 1 && num != cap - 1) {
                    if (Unknown_006279D0(&numunits, &size, whom, units, false)) {
                        Debug_Printf("Compress: Found early repeat megamission - splitting after %d units\n", numunits);
                        cached = true;
                        *unitsptr = numunits;
                    }
                } else {
                    Debug_Printf("Compress: Ended megamission run at %d units - no more events\n", numunits);
                    Unknown_006279D0(&numunits, &size, whom, units, true);
                    *unitsptr = numunits;
                }
            } else {
                *unitsptr = numunits;
                *((char *)buf + size) = 4;
                whom = (char *)buf + size + 2;
                memcpy(whom, &OutList.First().Data, datasize);
                units = whom + datasize;
                size += datasize + 2;
            }
            break;

        case 0x1B:
            *((char *)buf + size) = 0x1B;
            memcpy((char *)buf + size + 1, &OutList.First().ByteAt(0x0D), datasize);
            size += datasize + 1;
            break;

        case 0x1F:
            *((char *)buf + size) = 0x1F;
            memcpy((char *)buf + size + 1, &OutList.First().LongAt(0x0B), datasize);
            size += datasize + 1;
            memcpy((char *)buf + size, (void *)OutList.First().LongAt(0x07), OutList.First().LongAt(0x0B));
            size += OutList.First().LongAt(0x0B);
            break;

        default:
            *((char *)buf + size) = eventtype;
            memcpy((char *)buf + size + 1, &OutList.First().Data, datasize);
            size += datasize + 1;
            break;
        }

        num++;
        memcpy(&prevevent, &OutList.First(), sizeof(EventClass));
        if (!OutList.Next()) {
            break;
        }
    }

    *added = num;
    return size;
}
