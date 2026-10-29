// SerialEd.cpp
#include "shared/shape_file.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/serial_ed.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/session_state.hpp"
#include "shared/modem_guest.hpp"
#include "shared/string_table.hpp"
#include "shared/crt_string.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/null_modem.hpp"
#include "shared/ww_message_box.hpp"
#include "shared/serial_progress.hpp"
#include "shared/debug_printf.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Detect_Port@NullModemClass@@QAEHPAUSerialSettingsType@@@Z=005d03e0
// @ref ?serial_manager_00a40a28@@3VNullModemClass@@A=00a40a28
// @ref ??_C@_15KLDP@?$AA?$CF?$AAd?$AA?$AA@=007d1598
// @ref _swscanf=00784ddb
// @ref ?Read_Settings_0066cf60@SerialEdDialog@@QAE_NXZ=0066cf60
// @ref ??_C@_04DHPA@Tone?$AA@=007f316c
// @ref ??_C@_05NGCH@Pulse?$AA@=007f3164
// @ref ??_C@_0BA@EKHJ@DialMethod?3?5?$CFs?6?$AA@=007f3154
// @ref ??_C@_0BH@CDGJ@TXT_IRQ_ALREADY_IN_USE?$AA@=007f3128
// @ref ??_C@_0BI@MFIH@TXT_UNABLE_TO_OPEN_PORT?$AA@=007f3110
// @ref ??_C@_0CA@HIAM@Reading?5serial?5settings?5dialog?6?$AA@=007f3198
// @ref ??_C@_0L@FNHB@Modem?3?5?$CFs?6?$AA@=007f3180
// @ref ??_C@_0L@HKKL@Port?3?5?$CFlx?6?$AA@=007f318c
// @ref ??_C@_0L@JCDO@Baud?3?5?$CFld?6?$AA@=007f3174
// @ref ?Process@WWMessageBox@@QAEHPBG000_N@Z=005b46b0
// @ref _strncmp=00783810
// @ref ??_C@_03IOBP@2E8?$AA@=007f31f4
// @ref ??_C@_03LFOA@2F8?$AA@=007f31fc
// @ref ??_C@_03NMAJ@3E8?$AA@=007f31f8
// @ref ??_C@_03OHPG@3F8?$AA@=007f3200
// @ref ??_C@_03PMIG@COM?$AA@=007f31f0
// @ref ??_C@_0BJ@KBOG@TXT_INVALID_PORT_ADDRESS?$AA@=007f31d4
// @ref __stricmp=00781f20
// @ref ??_C@_06DN@TXT_OK?$AA@=007db8f4
// @ref ??_C@_13ECNF@?$AA?5?$AA?$AA@=007d64f4
// @ref ?Read_Custom_Port_0066db50@SerialEdDialog@@QAEXXZ=0066db50
// @ref ?Fill_Port_0066d5a0@SerialEdDialog@@QAEXXZ=0066d5a0
// @ref ??0ModemRegistryEntryClass@@QAE@H@Z=0059cd00
// @ref ??1ModemRegistryEntryClass@@QAE@XZ=0059d4f0
// @ref ??3@YAXPAX@Z=00781d3b
// @ref _wcscpy=00783689
// @ref _swprintf=00783764
// @ref _strncpy=007823d0
// @ref ??_C@_1M@CIBC@?$AA?$CF?$AAs?$AA?5?$AA?$CF?$AAx?$AA?$AA@=007f31b8
// @ref ??_C@_1O@EPIL@?$AA?$CF?$AAs?$AA?5?$AA?$CF?$AAh?$AAs?$AA?$AA@=007f31c4
// @ref ?unknown_port_names_7f305c@@3PAPBDA=007f305c
// @ref __imp__GetWindowLongA@8=0079a48c
// @ref __imp__SendDlgItemMessageA@20=0079a484
// @ref __imp__SetFocus@4=0079a38c
// @ref __imp__SetWindowLongA@12=0079a488
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ?unknown_create_dialog_5ff610@@YIPAUHWND__@@HP6GHPAU1@IIJ@ZH@Z=005ff610
// @ref ?unknown_dialog_5ff7c0@@YIXPAUHWND__@@@Z=005ff7c0
// @ref ?unknown_dialog_5ff6e0@@YIXPAUHWND__@@@Z=005ff6e0
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?unknown_6000d0@@YA_NXZ=006000d0
// @ref ?unknown_517370@@YIX_N@Z=00517370
// @ref ?Init_0066d370@SerialEdDialog@@QAEXPBUSerialSettingsType@@@Z=0066d370
// @ref ?Read_Custom_Port_0066db50@SerialEdDialog@@QAEXXZ=0066db50
// @ref ?Add_Init_String_0066de80@SerialEdDialog@@QAEXXZ=0066de80
// @ref ?Delete_Init_String_0066dfe0@SerialEdDialog@@QAEXXZ=0066dfe0
// @ref ?Dialog_Proc_0066cb00@SerialEdDialog@@SGHPAUHWND__@@IIJ@Z=0066cb00
// @ref ?Find_Combo_Item_Data_00736e10@@YIHPAUHWND__@@HH@Z=00736e10
// @ref ?strtrim@@YIPADPAD@Z=006eef10
// @ref __strupr=007961e4
// @ref _strchr=00784130
// @ref ??2@YAPAXI@Z=00782017
// @ref ??_C@_03EADM@ATZ?$AA@=007e8030
// @ref ?Read_Custom_Port_0066db50@SerialEdDialog@@QAEXXZ=0066db50
// @ref ?Fill_Port_0066d5a0@SerialEdDialog@@QAEXXZ=0066d5a0
// @ref ?Fill_Baud_0066d860@SerialEdDialog@@QAEXXZ=0066d860
// @ref ?Fill_Init_Strings_0066d9b0@SerialEdDialog@@QAEXXZ=0066d9b0
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref ??_C@_04HJIJ@?$CFls?5?$AA@=007f3204
// @ref ??_C@_0BE@ECKE@D?3?2Ra2?2SerialEd?4cpp?$AA@=007f3140
// @ref ??_C@_0L@DPHB@TXT_CUSTOM?$AA@=007f30d4
// @ref ?Set_Custom_Entry_0066dd60@SerialEdDialog@@QAEXHHPBD@Z=0066dd60
// @ref ?unknown_baud_names_7f3070@@3PAPAGA=007f3070
extern "C" char *__cdecl _strupr(char *string);
extern "C" char *__cdecl strchr(char const *string, int character);
char *__fastcall strtrim(char *string);
extern unsigned short *unknown_baud_names_7f3070[6];
extern "C" int __cdecl swscanf(unsigned short const *text, unsigned short const *format, ...);
extern char const *unknown_port_names_7f305c[4];
extern "C" unsigned short *__cdecl wcscpy(unsigned short *destination, unsigned short const *source);
extern "C" int __cdecl swprintf(unsigned short *buffer, unsigned short const *format, ...);
extern "C" char *__cdecl strncpy(char *destination, char const *source, unsigned int count);

bool SerialEdDialog::Dialog_0066ca70(SerialSettingsType *settings)
{
    Result = -1;
    Window = unknown_create_dialog_5ff610(0xED, Dialog_Proc_0066cb00, 0);
    if (Window) {
        SetWindowLongA(Window, DWL_USER, (LONG)this);
        Init_0066d370(settings);
        unknown_dialog_5ff7c0(Window);
        while (Result < 0) {
            if (unknown_6000d0() == true) {
                break;
            }
            unknown_517370(false);
        }
        unknown_dialog_5ff6e0(Window);
        if (Result == 1) {
            *settings = Settings;
        }
    }
    if (Result == 1) {
        return true;
    }
    return false;
}
