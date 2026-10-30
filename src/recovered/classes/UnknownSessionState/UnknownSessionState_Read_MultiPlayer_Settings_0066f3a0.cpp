#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#include "shared/session_state.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/serial_settings.hpp"
#include "shared/ccini_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/rules.hpp"
#include "shared/random2.hpp"
#include "shared/firewall_settings.hpp"
#include "shared/multiplayer_game_mode.hpp"
#include "shared/string_table.hpp"
#include "shared/modem_guest.hpp"
#include "shared/lobby.hpp"
#include "shared/crt_string.hpp"
#include "shared/crt_tokens.hpp"
#include "shared/udp_interface.hpp"
#include "shared/campaign.hpp"
#include "shared/mouse.hpp"
#include "shared/gscreen.hpp"
#include "shared/map_view.hpp"
#include "shared/coord.hpp"
extern "C" unsigned short *__cdecl _wcsupr(unsigned short *string);
// The dial method letters (0x007F320C; also declared by Write_MultiPlayer_Settings 0x00670380).
extern char const *unknown_dial_methods_7f320c[2];
// Set once the port settings are read (0x00AB9178).
extern bool unknown_ports_read_ab9178;
// The firewall detection state (0x00A71B18) and the port pool after it (0x00A71B28).
extern FirewallSettings unknown_firewall_a71b18;
extern int unknown_port_pool_a71b28;
// The "no cell" value the SyncBug cell is compared with (0x00AB71D8).
extern Cell unknown_cell_none_ab71d8;

// Red Alert's SessionClass::Read_MultiPlayer_Settings: reads the player and serial settings,
// the init strings, the phone book and the SyncBug settings from RA2.INI.
void UnknownSessionState::Read_MultiPlayer_Settings()
{
    char *tokenptr;
    PhoneEntryClass *phone;
    char *entry;
    char buf[0x400];
    int i;

    Rules->Countries(*unknown_ini_8396d0);

    for (i = 0; i < InitStrings.Count(); i++) {
        delete [] InitStrings[i];
    }
    InitStrings.Clear();

    for (i = 0; i < PhoneBook.Count(); i++) {
        delete PhoneBook[i];
    }
    PhoneBook.Clear();

    CCFileClass file("RA2.INI");

    if (!unknown_ports_read_ab9178) {
        PortBase = unknown_ini_839740.Get_Int("MultiPlayer", "PortBase", 0x4E2);
        unknown_2f9c = unknown_ini_839740.Get_Int("MultiPlayer", "ForcePortBase", 0);
        unknown_port_pool_a71b28 = unknown_ini_839740.Get_Int("MultiPlayer", "PortPool", unknown_random_839218(0, 0x8000) + 0x1000);
        unknown_ports_read_ab9178 = true;
        unknown_firewall_a71b18.Load_005ba280();
    }
    unknown_session_a3d298.SendDelay = unknown_ini_839740.Get_Bool("MultiPlayer", "SendDelay", false);
    unknown_session_a3d298.PortNumberOverride = unknown_ini_839740.Get_Int("MultiPlayer", "PortNumberOverride", 0);

    buf[0] = 0;
    CurPhoneIdx = unknown_ini_839740.Get_Int("MultiPlayer", "PhoneIndex", -1);
    TrapCheckHeap = unknown_ini_839740.Get_Int("MultiPlayer", "CheckHeap", 0);
    WOLLimitResolution = unknown_ini_839740.Get_Bool("MultiPlayer", "WOLLimitResolution", WOLLimitResolution);
    LastNickSlot = unknown_ini_839740.Get_Int("MultiPlayer", "LastNickSlot", -1);

    unsigned short handle[20];
    unknown_ini_839740.Get_Unicode("MultiPlayer", "Handle",
                                   StringTable::Load_String("TXT_NONAME", 0, "D:\\Ra2\\Session.CPP", 0x4b2), handle, 20);
    Unknown_006FA0F0(Handle, handle, -1);

    unknown_12c = unknown_ini_839740.Get_Int("MultiPlayer", "Color", unknown_12c);
    unknown_130 = unknown_ini_839740.Get_Int("MultiPlayer", "ColorEx", unknown_130);
    unknown_134 = unknown_ini_839740.Get_HousesType("MultiPlayer", "Side", unknown_134);
    unknown_138 = unknown_ini_839740.Get_Int("MultiPlayer", "SideEx", unknown_138);
    WOLTaunts = unknown_ini_839740.Get_Bool("MultiPlayer", "WOLTaunts", WOLTaunts);
    LANTaunts = unknown_ini_839740.Get_Bool("MultiPlayer", "LANTaunts", LANTaunts);
    WOLScrollText = unknown_ini_839740.Get_Bool("MultiPlayer", "WOLScrollText", WOLScrollText);
    LANScrollText = unknown_ini_839740.Get_Bool("MultiPlayer", "LANScrollText", LANScrollText);

    unknown_124 = unknown_134;
    if (unknown_124 == -2) {
        unknown_124 = 0;
    }
    unknown_128 = unknown_138;

    Mode = MultiplayerGameMode::unknown_find_mode_5b6fe0(unknown_ini_839740.Get_Int("MultiPlayer", "GameMode", 1));
    if (!Mode) {
        Mode = MultiplayerGameMode::unknown_first_mode_5b6ec0();
    }
    SkirmishOptions.Read(unknown_ini_839740, "Skirmish", 1, 6);
    LANOptions.Read(unknown_ini_839740, "LAN", 2, 2);
    WonlineOptions.Read(unknown_ini_839740, "WonlinePref", 2, 2);

    unknown_ini_839740.Get_String("SerialDefaults", "ModemName", buf, SerialDefaults.ModemName, 0x3F);
    if (strcmp(SerialDefaults.ModemName, buf) == 0) {
        SerialDefaults.ModemName[0] = 0;
    }
    SerialDefaults.Port = unknown_ini_839740.Get_Int("SerialDefaults", "Port", 0);
    SerialDefaults.IRQ = unknown_ini_839740.Get_Int("SerialDefaults", "IRQ", -1);
    SerialDefaults.Baud = unknown_ini_839740.Get_Int("SerialDefaults", "Baud", -1);
    SerialDefaults.Compression = unknown_ini_839740.Get_Int("SerialDefaults", "Compression", 0);
    SerialDefaults.ErrorCorrection = unknown_ini_839740.Get_Int("SerialDefaults", "ErrorCorrection", 0);

    unknown_ini_839740.Get_String("SerialDefaults", "DialMethod", "T", buf, 2);
    for (i = 0; i < 2; i++) {
        if (!_stricmp(buf, unknown_dial_methods_7f320c[i])) {
            SerialDefaults.DialMethod = i;
            break;
        }
    }
    if (i == 2) {
        SerialDefaults.DialMethod = 0;
    }

    SerialDefaults.InitStringIndex = unknown_ini_839740.Get_Int("SerialDefaults", "InitStringIndex", -1);
    SerialDefaults.CallWaitStringIndex = unknown_ini_839740.Get_Int("SerialDefaults", "CallWaitStringIndex", 3);
    unknown_ini_839740.Get_String("SerialDefaults", "CallWaitString", "", SerialDefaults.CallWaitString, 0x10);

    if (SerialDefaults.IRQ == 0 || SerialDefaults.Baud == 0) {
        SerialDefaults.Port = 0;
        SerialDefaults.IRQ = -1;
        SerialDefaults.Baud = -1;
    }

    int initcount = unknown_ini_839740.Entry_Count("InitStrings");
    int index;
    for (index = 0; index < initcount; index++) {
        entry = new char[0x29];
        if (entry) {
            entry[0] = 0;
            unknown_ini_839740.Get_String("InitStrings", unknown_ini_839740.Get_Entry("InitStrings", index), 0, entry, 0x29);
            _strupr(entry);
            InitStrings.Add(entry);
        }
    }
    SerialDefaults.InitStringIndex = initcount ? 0 : -1;

    int phonecount = unknown_ini_839740.Entry_Count("PhoneBook");
    for (index = 0; index < phonecount; index++) {
        phone = new PhoneEntryClass;
        unknown_ini_839740.Get_String("PhoneBook", unknown_ini_839740.Get_Entry("PhoneBook", index), 0, buf, sizeof(buf));

        tokenptr = strtok(buf, "|");
        if (tokenptr) {
            Unknown_006FA0C0(phone->Name, tokenptr, -1);
            _wcsupr(phone->Name);
        } else {
            phone->Name[0] = 0;
        }

        tokenptr = strtok(0, "|");
        if (tokenptr) {
            strcpy(phone->Number, tokenptr);
            _strupr(phone->Number);
        } else {
            phone->Number[0] = 0;
        }

        tokenptr = strtok(0, "|");
        if (tokenptr) {
            sscanf(tokenptr, "%x", &phone->Settings.Port);
        } else {
            phone->Settings.Port = 0;
        }

        tokenptr = strtok(0, "|");
        if (tokenptr) {
            phone->Settings.IRQ = atoi(tokenptr);
        } else {
            phone->Settings.IRQ = -1;
        }

        tokenptr = strtok(0, "|");
        if (tokenptr) {
            phone->Settings.Baud = atoi(tokenptr);
        } else {
            phone->Settings.Baud = -1;
        }

        tokenptr = strtok(0, "|");
        if (tokenptr) {
            phone->Settings.Compression = atoi(tokenptr);
        } else {
            phone->Settings.Compression = -1;
        }

        tokenptr = strtok(0, "|");
        if (tokenptr) {
            phone->Settings.ErrorCorrection = atoi(tokenptr);
        } else {
            phone->Settings.ErrorCorrection = 0;
        }

        tokenptr = strtok(0, "|");
        if (tokenptr) {
            strcpy(buf, tokenptr);
            for (i = 0; i < 2; i++) {
                if (!_stricmp(buf, unknown_dial_methods_7f320c[i])) {
                    phone->Settings.DialMethod = i;
                    break;
                }
            }
            if (i == 2) {
                phone->Settings.DialMethod = 0;
            }
        } else {
            phone->Settings.DialMethod = 0;
        }

        tokenptr = strtok(0, "|");
        if (tokenptr) {
            phone->Settings.InitStringIndex = atoi(tokenptr);
        } else {
            phone->Settings.InitStringIndex = -1;
        }

        tokenptr = strtok(0, "|");
        if (tokenptr) {
            phone->Settings.CallWaitStringIndex = atoi(tokenptr);
        } else {
            phone->Settings.CallWaitStringIndex = 3;
        }

        tokenptr = strtok(0, "|");
        if (tokenptr) {
            strcpy(phone->Settings.CallWaitString, tokenptr);
        } else {
            phone->Settings.CallWaitString[0] = 0;
        }

        PhoneBook.Add(phone);
    }

    if (unknown_session_a3d298.Play) {
        TrapFrame = unknown_ini_839740.Get_Int("SyncBug", "Frame", 0x7FFFFFFF);
        unknown_ini_839740.Get_String("SyncBug", "Type", "NONE", buf, 0x50);
        if (!_stricmp(buf, "AIRCRAFT")) {
            TrapObjType = 2;
        } else if (!_stricmp(buf, "ANIM")) {
            TrapObjType = 4;
        } else if (!_stricmp(buf, "BUILDING")) {
            TrapObjType = 6;
        } else if (!_stricmp(buf, "BULLET")) {
            TrapObjType = 8;
        } else if (!_stricmp(buf, "INFANTRY")) {
            TrapObjType = 15;
        } else if (!_stricmp(buf, "UNIT")) {
            TrapObjType = 1;
        } else {
            TrapObjType = 0;
        }

        unknown_ini_839740.Get_String("SyncBug", "Coord", "0", buf, 0x50);
        int x;
        int y;
        int z;
        sscanf(buf, "%d,%d,%d", &x, &y, &z);
        int target = unknown_ini_839740.Get_Int("SyncBug", "Target", -1);
        TrapTargetKind = target >> 24;
        TrapTarget = target & 0xFFFFFF;

        unknown_ini_839740.Get_String("SyncBug", "Cell", "0,0", buf, 0x50);
        sscanf(buf, "%d,%d", &x, &y);
        Cell cell(x, y);
        if (cell != unknown_cell_none_ab71d8) {
            TrapCell = &Map[cell];
        }

        TrapPrintCRC = unknown_ini_839740.Get_Int("SyncBug", "PrintCRC", 0x7FFFFFFF);
    }
}
// @ref ??_C@_0O@CBJD@ForcePortBase?$AA@=007f36a4
// @ref ?Load_005ba280@FirewallSettings@@QAEXXZ=005ba280
// @ref ??_C@_09OJJN@SendDelay?$AA@=007dfe18
// @ref ??_C@_0BD@JACO@PortNumberOverride?$AA@=007dfe04
// @ref ??_C@_09GCLC@CheckHeap?$AA@=007f368c
// @ref ??_C@_05MMOI@Frame?$AA@=007f3550
// @ref ??_C@_07GAE@SyncBug?$AA@=007f3548
// @ref ??_C@_04MHIC@NONE?$AA@=007f3540
// @ref ??_C@_08KLKB@AIRCRAFT?$AA@=007f3534
// @ref ??_C@_04HAFH@ANIM?$AA@=007f352c
// @ref ??_C@_08IFKF@BUILDING?$AA@=007f3520
// @ref ??_C@_06JOKJ@BULLET?$AA@=007f3518
// @ref ??_C@_08NKFK@INFANTRY?$AA@=007f350c
// @ref ??_C@_04OHGB@UNIT?$AA@=007f3504
// @ref ??_C@_05ELAO@Coord?$AA@=007f34fc
// @ref ??_C@_03KCID@0?00?$AA@=007f34f0
// @ref ??_C@_04HPIN@Cell?$AA@=007cde50
// @ref ??_C@_08JIFJ@PrintCRC?$AA@=007f34e4
// @ref ?Load_005ba280@FirewallSettings@@QAEXXZ=005ba280
// @ref ??_C@_0L@JPAF@TXT_NONAME?$AA@=007eb8ec
// @ref ?unknown_ports_read_ab9178@@3_NA=00ab9178
// @ref ?unknown_firewall_a71b18@@3VFirewallSettings@@A=00a71b18
// @ref ?unknown_port_pool_a71b28@@3HA=00a71b28
// @ref ?unknown_cell_none_ab71d8@@3VCell@@A=00ab71d8
// @ref ?unknown_dial_methods_7f320c@@3PAPBDA=007f320c
// @ref ??_C@_07IBND@RA2?4INI?$AA@=007db8b8
// @ref ??_C@_08DDKG@PortBase?$AA@=007dbcf0
// @ref ??_C@_0M@MLEF@MultiPlayer?$AA@=007dbce4
// @ref ??_C@_08CLJJ@PortPool?$AA@=007dbcd8
// @ref ??_C@_0L@JMMI@PhoneIndex?$AA@=007f3698
// @ref ??_C@_0BD@FJLN@WOLLimitResolution?$AA@=007f3678
// @ref ??_C@_0N@FPHD@LastNickSlot?$AA@=007f3668
// @ref ??_C@_0BD@OFLC@D?3?2Ra2?2Session?4CPP?$AA@=007f33c8
// @ref ??_C@_06ILKP@Handle?$AA@=007f3660
// @ref ??_C@_05HIMK@Color?$AA@=007d13d8
// @ref ??_C@_07EDGH@ColorEx?$AA@=007f3658
// @ref ??_C@_04LJDI@Side?$AA@=007cdd8c
// @ref ??_C@_06HKOL@SideEx?$AA@=007f3650
// @ref ??_C@_09KHPG@WOLTaunts?$AA@=007f3644
// @ref ??_C@_09HLFF@LANTaunts?$AA@=007f3638
// @ref ??_C@_0O@NDBO@WOLScrollText?$AA@=007f3628
// @ref ??_C@_0O@GLCN@LANScrollText?$AA@=007f3618
// @ref ??_C@_08MAFF@GameMode?$AA@=007f34d8
// @ref ??_C@_08GGBF@Skirmish?$AA@=007f360c
// @ref ??_C@_03OPEA@LAN?$AA@=007f3608
// @ref ??_C@_0M@BIDM@WonlinePref?$AA@=007f35fc
// @ref ??_C@_09EHPD@ModemName?$AA@=007f35f0
// @ref ??_C@_0P@HEME@SerialDefaults?$AA@=007f35e0
// @ref ??_C@_04CEAI@Port?$AA@=007f35d8
// @ref ??_C@_03MHH@IRQ?$AA@=007f35d4
// @ref ??_C@_04IPGK@Baud?$AA@=007f35cc
// @ref ??_C@_0M@MOML@Compression?$AA@=007f35c0
// @ref ??_C@_0BA@NIDC@ErrorCorrection?$AA@=007f35b0
// @ref ??_C@_01KGOM@T?$AA@=007f326c
// @ref ??_C@_0L@IPGK@DialMethod?$AA@=007f35a4
// @ref ??_C@_0BA@OGHJ@InitStringIndex?$AA@=007f3594
// @ref ??_C@_0BE@FIJL@CallWaitStringIndex?$AA@=007f3580
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_0P@KBNH@CallWaitString?$AA@=007f3570
// @ref ??_C@_0M@LJHH@InitStrings?$AA@=007f3564
// @ref ??_C@_09BCMM@PhoneBook?$AA@=007f3558
// @ref ??_C@_01KALE@?$HM?$AA@=007e7c60
// @ref ??_C@_02JDLK@?$CFx?$AA@=007db4b4
// @ref ??_C@_04FCOP@Type?$AA@=007d9eec
// @ref ??_C@_01PLJA@0?$AA@=007e1a60
// @ref ??_C@_08POMI@?$CFd?0?$CFd?0?$CFd?$AA@=007cf360
// @ref ??_C@_06JGPH@Target?$AA@=007f34f4
// @ref ??_C@_05BBIB@?$CFd?0?$CFd?$AA@=007d1f10
