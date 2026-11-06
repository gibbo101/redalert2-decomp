// RetcodeType __fastcall Process_Receive_Packet(ConnManClass *net, char *multi_packet_buf, int id, int packetlen,
// UnknownFrameTiming *their, UnknownElapsedTimer *timer) (0x006265C0; Red Alert's Process_Receive_Packet,
// with Breakup_Receive_Packet and Extract_Uncompressed_Events inline and the router's packets first).
#include "shared/queue.hpp"
#include "shared/crt_memory.hpp"
#include "shared/lobby.hpp"
// @ref ?Frame@@3HA=00a40d2c
// @ref ??_C@_0BF@NDB@Command?5count?5is?5?$CFd?6?$AA@=007ec9ec
// @ref ??_C@_0BO@DLBM@Received?5PACKETTIMING?5packet?6?$AA@=007eca8c
// @ref ??_C@_0BP@CMKN@Received?5MEGAFRAMEINFO?5packet?6?$AA@=007eca6c
// @ref ??_C@_0CB@CKAE@My?5router?5response?5time?5?$DN?5?$CFd?5ms?6@=007ec98c
// @ref ??_C@_0CB@MPMB@?$CK?$CK?$CK?$CK?$CK?5Error?5DOLIST_FULL?$CB?5?$CK?$CK?$CK?$CK?$CK?$CK?6@=007ec958
// @ref ??_C@_0CP@PAIA@Received?5FRAMESYNC?5packet?5from?5?$CF@=007ec8ec
// @ref ??_C@_0DA@OIEG@MEGAFRAMEINFO?5is?5part?5of?5a?5pserv@=007eca3c
// @ref ??_C@_0DI@PGH@Got?5MEGAFRAMEINFO?5frame?5update?5f@=007eca04
// @ref ??_C@_0DJ@NOJF@Frame?5?$CFd?0?5Receive?5packet?5uncompr@=007ec91c
// @ref ??_C@_0DM@GBDB@Got?5useless?5MEGAFRAMEINFO?5frame?5@=007ec9b0
// @ref ??_C@_0O@PCJG@Player?5ready?6?$AA@=007ec97c
// @ref ?Extract_Compressed_Events@@YIHPAXH@Z=006282d0
// @ref ?unknown_a402cc@@3IA=00a402cc
// @ref ?unknown_a402d4@@3HA=00a402d4
// @ref ?unknown_response_times_a76c88@@3PAKA=00a76c88
// @ref ?unknown_ipx_manager_a40978@@3VIPXManagerClass@@A=00a40978

static int Breakup_Receive_Packet(void *buf, int bufsize);
static int Extract_Uncompressed_Events(void *buf, int bufsize);

RetcodeType __fastcall Process_Receive_Packet(ConnManClass *net, char *multi_packet_buf, int id, int packetlen,
    UnknownFrameTiming *their, UnknownElapsedTimer *timer)
{
    EventClass *event = (EventClass *)multi_packet_buf;
    RetcodeType retcode = RC_NORMAL;
    int index = net->Connection_Index(id);
    int i;

    if (unknown_flag_a3fba8 && (event->Type == 0x25 || event->Type == 0x26)) {
        int count = (char)event->House;
        unsigned long most = 0;
        if (event->Type == 0x26) {
            Debug_Printf("Received PACKETTIMING packet\n");
        } else if (event->Type == 0x25) {
            Debug_Printf("Received MEGAFRAMEINFO packet\n");
        }
        if (count == 0) {
            Debug_Printf("MEGAFRAMEINFO is part of a pserver port blitz!\n");
        }
        i = 0;
        if (i < count) {
            UnknownPacketTimingEntry *timing = (UnknownPacketTimingEntry *)&event->Data;
            UnknownMegaFrameEntry *mega = (UnknownMegaFrameEntry *)&event->Data;
            for (; i < count; i++, mega++, timing++) {
                if (event->Type == 0x25) {
                    int player = net->Connection_Index(mega->ID);
                    if (player == -1) {
                        continue;
                    }
                    if (their[player].Frame < (long)(mega->Frame - mega->Delay)) {
                        their[player].Frame = mega->Frame - mega->Delay;
                        Unknown_0062E5C0(their, player);
                        if (unknown_ipx_manager_a40978.Connection_Name(mega->ID)) {
                            Debug_Printf("Got MEGAFRAMEINFO frame update from %s. New frame = %d\n",
                                Unknown_006FA120(unknown_ipx_manager_a40978.Connection_Name(mega->ID)), their[player].Frame);
                        }
                        if ((unsigned)their[player].unknown_04 < mega->CommandCount) {
                            their[player].unknown_04 = mega->CommandCount;
                            Debug_Printf("Command count is %d\n", their[player].unknown_04);
                        }
                    } else {
                        if (unknown_ipx_manager_a40978.Connection_Name(mega->ID)) {
                            Debug_Printf("Got useless MEGAFRAMEINFO frame update from %s. frame = %d\n",
                                Unknown_006FA120(unknown_ipx_manager_a40978.Connection_Name(mega->ID)), their[player].Frame);
                        }
                    }
                    if (!(mega->Flags & 1)) {
                        their[player].unknown_0c = timer->Timer - timer->Started;
                    }
                } else {
                    if (timing->ID == unknown_player_a35db4->ArrayIndex) {
                        unsigned long response = timing->ResponseTime;
                        unknown_a402dc = response;
                        Debug_Printf("My router response time = %d ms\n", response * 1000 / 60);
                        continue;
                    }
                    int player = net->Connection_Index(timing->ID);
                    if (player == -1) {
                        continue;
                    }
                    unsigned long response = timing->ResponseTime;
                    their[player].unknown_10 = response;
                    unknown_response_times_a76c88[player] = response;
                    if (most <= response) {
                        most = response;
                    }
                    if (timing->unknown_01 && unknown_session_a3d298.Am_I_Master(0) && unknown_a402d4 != timing->ID) {
                        OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, 0x28, timing->ID));
                    }
                }
            }
        }
        if (count && most) {
            unknown_a402cc = most;
        }
    } else {
    UnknownFrameTiming *t = &their[index];
    if (t->Frame < (long)(event->Frame - event->ByteAt(0x0D))) {
        if (t->Frame == -1) {
            retcode = RC_PLAYER_READY;
            Debug_Printf("Player ready\n");
        }
        t->Frame = event->Frame - event->ByteAt(0x0D);
        Unknown_0062E5C0(their, index);
    }
    if ((unsigned short)event->ShortAt(0x0B) > (unsigned)t->unknown_04) {
        t->unknown_04 = (unsigned short)event->ShortAt(0x0B);
    }

    if (event->Type != 0x19) {
        i = Breakup_Receive_Packet(event, packetlen);
        if (i == -1) {
            Debug_Printf("***** Error DOLIST_FULL! ******\n");
            return RC_DOLIST_FULL;
        }
        if (event->Type == 0x1C && i > 0) {
            i--;
        }
        Debug_Printf("Frame %d, Receive packet uncompressed into %d commmands\n", ::Frame, i);
        t->unknown_08 += (unsigned short)i;
    } else {
    if (unknown_session_a3d298.Type == 4 || unknown_session_a3d298.Type == 3) {
        Debug_Printf("Received FRAMESYNC packet from %s. Frame = %d\n", unknown_ipx_manager_a40978.Connection_Name(id),
            event->Frame - event->ByteAt(0x0D));
    }
    if (event->LongAt(0x07) != unknown_crc_a40770) {
        return RC_SCENARIO_MISMATCH;
    }
    t->unknown_0c = timer->Timer - timer->Started;
    }
    }
    return retcode;
}

static int Breakup_Receive_Packet(void *buf, int bufsize)
{
    int count = 0;

    switch (unknown_session_a3d2ac) {
    case 0:
        count = Extract_Uncompressed_Events(buf, bufsize);
        break;
    default:
        count = Extract_Compressed_Events(buf, bufsize);
        break;
    }
    return count;
}

static int Extract_Uncompressed_Events(void *buf, int bufsize)
{
    int count = 0;
    int pos = 0;
    int leftover = bufsize;
    EventClass *event;

    while (leftover >= sizeof(EventClass)) {
        event = (EventClass *)(((char *)buf) + pos);
        if (event->Type != 0x19) {
            event->IsExecuted = 0;
            if (event->Type == 0x1F) {
                event->Data.LongsCell.Long1 = (long)new char[event->Data.LongsCell.Long2];
                memcpy((void *)event->Data.LongsCell.Long1, ((char *)buf) + sizeof(EventClass), event->Data.LongsCell.Long2);
                pos += event->Data.LongsCell.Long2;
                leftover -= event->Data.LongsCell.Long2;
            }
            if (!DoList.Add(*event)) {
                if (event->Type == 0x1F) {
                    delete [] (char *)event->Data.LongsCell.Long1;
                }
                return -1;
            }
            count++;
        }
        pos += sizeof(EventClass);
        leftover -= sizeof(EventClass);
    }
    return count;
}
