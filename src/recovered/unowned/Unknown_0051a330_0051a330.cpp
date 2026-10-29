// bool __fastcall Unknown_0051a330(int side) -- 0x0051A330
#include "shared/cd.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/cd_file_class.hpp"
#include "shared/crt_string.hpp"
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/debug_printf.hpp"

// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?unknown_mix_8374f8@@3PAV?$MixFileClass@VCCFileClass@@@@A=008374f8
// @ref ?unknown_side_mix_837500@@3PAV?$MixFileClass@VCCFileClass@@@@A=00837500
// @ref ?unknown_side_nc_mix_837504@@3PAV?$MixFileClass@VCCFileClass@@@@A=00837504
// @ref ??_C@_0BD@MGDA@?5?5?5?5?5Releasing?5?$CFs?6?$AA@=007d2208
// @ref ?Unknown_007168C0@@YIXH@Z=007168c0
// @ref ?Unknown_006F44D0@@YAXXZ=006f44d0
// @ref ?unknown_select_color@@YIXH@Z=006f45a0
// @ref ??_C@_0CP@PBMJ@?5?5?5?5?5FAILED?$CB?5?5This?5was?5not?5disk?5@=007dd990
// @ref ??_C@_0CD@FHGP@Preparing?5Mixfiles?5for?5Side?5?$CF02d@=007dd96c
// @ref ??_C@_0O@EEPB@SIDEC?$CF02d?4MIX?$AA@=007dd95c
// @ref ??_C@_0BF@NNEE@?5?5?5?5?5Initilizing?5?$CFs?6?$AA@=007dd944
// @ref ??_C@_0P@DLOK@SIDENC?$CF02d?4MIX?$AA@=007dd934
// @ref ??_C@_06HCKG@UI?4INI?$AA@=007dd92c
// @ref ??_C@_0O@HDKF@?5?5?5?5?5FAILED?$CB?6?$AA@=007d21ac
// @ref ??_C@_0BI@KFPN@Failed?5to?5load?5UI?4INI?$CB?6?$AA@=007dd914

// Opens the side's interface archives (SIDEC and SIDENC, numbered from 1; side -1 asks the
// CD, which must be disk one or two) and reads UI.INI's advanced command bar.
bool __fastcall Unknown_0051a330(int side)
{
    if (side == -1) {
        int disk = Get_CD_Index(CDFileClass::CurrentCDDrive, 60);
        if (disk != 0 && disk != 1) {
            Debug_Printf("     FAILED!  This was not disk one or two!!!\n");
            return false;
        }
        side = disk;
    }
    Debug_Printf("Preparing Mixfiles for Side %02d.\n", side);

    if (unknown_mix_8374f8 != 0) {
        Debug_Printf("     Releasing %s\n", unknown_mix_8374f8->Filename);
        delete unknown_mix_8374f8;
        unknown_mix_8374f8 = 0;
    }
    if (unknown_side_mix_837500 != 0) {
        Debug_Printf("     Releasing %s\n", unknown_side_mix_837500->Filename);
        delete unknown_side_mix_837500;
        unknown_side_mix_837500 = 0;
    }
    if (unknown_side_nc_mix_837504 != 0) {
        Debug_Printf("     Releasing %s\n", unknown_side_nc_mix_837504->Filename);
        delete unknown_side_nc_mix_837504;
        unknown_side_nc_mix_837504 = 0;
    }

    int number = side + 1;
    Unknown_007168C0(side);

    char filename[64];
    sprintf(filename, "SIDEC%02d.MIX", number);
    Debug_Printf("     Initilizing %s\n", filename);
    if (CCFileClass(filename).Is_Available()) {
        unknown_side_mix_837500 = new MixFileClass<CCFileClass>(filename, &FastKey);
    }
    if (unknown_side_mix_837500 == 0) {
        Debug_Printf("     FAILED!\n");
        return false;
    }
    unknown_side_mix_837500->Cache();

    sprintf(filename, "SIDENC%02d.MIX", number);
    Debug_Printf("     Initilizing %s\n", filename);
    if (CCFileClass(filename).Is_Available()) {
        unknown_side_nc_mix_837504 = new MixFileClass<CCFileClass>(filename, &FastKey);
    }

    Unknown_006F44D0();
    unknown_select_color(side);

    CCFileClass file("UI.INI");
    if (unknown_ini_839860.Load(file, false, false)) {
        Rules->Advanced_Command_Bar(unknown_ini_839860, unknown_game_mode_a3d298 != 0 && unknown_game_mode_a3d298 != 5);
        Map.unknown_slot53();
        return true;
    }
    Debug_Printf("Failed to load UI.INI!\n");
    return false;
}
