// WDTState::WDTState(unsigned char *data) (0x0072BFA0): a state read from the WOL state packet:
// NACK leaves it empty; TOTK (or CRTK/CYLN) gives the conflict counts, SDSC/LDSC/WURL the label
// strings, CMID/CYID/TICC the numbers; MPVC (current cycles only) and HSVC are parsed by
// unknown_72c490 / unknown_72c3b0. The field names are the packet tags.
// @ref ??_EWDTState@@UAEPAXI@Z=0072ca00
// @ref ??_GWDTState@@UAEPAXI@Z=0072ca00
// @ref ??_7?$DynamicVectorClass@V?$rc_ptr@VWDTTerritory@@@@@@6B@=007af318
// @ref ??_C@_04BGEB@CYLN?$AA@=007fc228
// @ref ??_C@_04BIMG@TICC?$AA@=007fc1e8
// @ref ??_C@_04CCI@SDSC?$AA@=007fc218
// @ref ??_C@_04DCOH@CMID?$AA@=007fc1f8
// @ref ??_C@_04FLNH@CYID?$AA@=007fc1f0
// @ref ??_C@_04IHCH@LDSC?$AA@=007fc210
// @ref ??_C@_04IHEF@MPVC?$AA@=007fc208
// @ref ??_C@_04KLPF@TOTK?$AA@=007fc238
// @ref ??_C@_04KPPJ@CRTK?$AA@=007fc230
// @ref ??_C@_04MBGE@HSVC?$AA@=007fc200
// @ref ??_C@_04OJNO@NACK?$AA@=007fc240
// @ref ??_C@_04PDOL@WURL?$AA@=007fc220
// @ref ?unknown_72c3b0@WDTState@@QAE_NPAXH@Z=0072c3b0
// @ref ?unknown_72c490@WDTState@@QAE_NPAXH@Z=0072c490
// @ref ??0PacketClass@@QAE@PAD@Z=00602aa0
// @ref ??1PacketClass@@QAE@XZ=00602a60
// @ref ?Get_Field@PacketClass@@QAE_NPBDAAE@Z=00602d60
// @ref ?Get_Field@PacketClass@@QAE_NPBDAAI@Z=00602f10
// @ref ?Get_Field@PacketClass@@QAE_NPBDPAXAAH@Z=00602f60
#include "shared/wdt_state.hpp"
#include "shared/wdt_territory.hpp"
#include "shared/packet.hpp"
#include "shared/crt_memory.hpp"

WDTState::WDTState(unsigned char *data)
{
    PacketClass *packet = new PacketClass((char *)data);
    int mpvc_length = 0;
    int hsvc_length = 0;
    int sdsc_length = 0;
    int ldsc_length = 0;
    int wurl_length = 0;
    int nack_length = 0;
    ShortLabel = 0;
    LongLabel = 0;
    unknown_10 = 0;
    unknown_14 = 0;
    unknown_18 = 0;
    unknown_1c = 0;
    unknown_20 = 0;
    ConflictCount = 0;
    unknown_28 = 0;
    unknown_44 = 0;
    if (packet->Get_Field("NACK", 0, nack_length)) {
        delete packet;
        return;
    }
    if (packet->Get_Field("TOTK", unknown_1c)) {
        unknown_48 = true;
        unknown_1c++;
        ConflictCount = unknown_1c;
    } else {
        unknown_48 = false;
        packet->Get_Field("CRTK", ConflictCount);
        ConflictCount++;
        packet->Get_Field("CYLN", unknown_1c);
        unknown_1c++;
    }
    packet->Get_Field("WURL", 0, wurl_length);
    packet->Get_Field("SDSC", 0, sdsc_length);
    packet->Get_Field("LDSC", 0, ldsc_length);
    if (!unknown_48) {
        packet->Get_Field("MPVC", 0, mpvc_length);
    }
    packet->Get_Field("HSVC", 0, hsvc_length);
    ShortLabel = new char[sdsc_length];
    LongLabel = new char[ldsc_length];
    unknown_10 = new char[wurl_length];
    char *hsvc = new char[hsvc_length];
    char *mpvc = 0;
    if (!unknown_48) {
        mpvc = new char[mpvc_length];
        memset(mpvc, 0, mpvc_length);
    }
    memset(ShortLabel, 0, sdsc_length);
    memset(LongLabel, 0, ldsc_length);
    memset(unknown_10, 0, wurl_length);
    memset(hsvc, 0, hsvc_length);
    packet->Get_Field("CMID", unknown_14);
    packet->Get_Field("CYID", unknown_18);
    if (unknown_48) {
        unknown_28 = 0;
    } else {
        packet->Get_Field("TICC", unknown_28);
    }
    packet->Get_Field("SDSC", ShortLabel, sdsc_length);
    packet->Get_Field("LDSC", LongLabel, ldsc_length);
    packet->Get_Field("WURL", unknown_10, wurl_length);
    if (!unknown_48) {
        packet->Get_Field("MPVC", mpvc, mpvc_length);
    }
    packet->Get_Field("HSVC", hsvc, hsvc_length);
    if (!unknown_48) {
        unknown_72c490(mpvc, mpvc_length);
    } else {
        unknown_20 = 30;
    }
    unknown_72c3b0(hsvc, hsvc_length);
    delete hsvc;
    if (!unknown_48) {
        delete mpvc;
    }
    delete packet;
}
