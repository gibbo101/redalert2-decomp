// DialStatusType NullModemClass::Dial_Modem(char *string, int method, bool reconnect) (0x005D1350)
// Dials under a cancel dialog and waits for the modem's answer: CONNECT
// (copied to ModemRXString), BUSY, NO CARRIER, NO DIALTONE or ERROR; the
// wait ends on a timeout, the cancel button or ESC (the modem gets a CR).
#include "shared/null_modem.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/string_table.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
#include "shared/campaign.hpp"
extern "C" char *__cdecl strstr(char const *string, char const *search);
extern "C" char *__cdecl strncpy(char *destination, char const *source, unsigned int count);
// @ref ?SerialPort@@3PAVWinModemClass@@A=00b25bb0
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ?unknown_cancel_dialog_6001e0@@YIPAUHWND__@@PBG0PA_N@Z=006001e0
// @ref ?unknown_dialog_5ff7c0@@YIXPAUHWND__@@@Z=005ff7c0
// @ref ?unknown_dialog_5ff6e0@@YIXPAUHWND__@@@Z=005ff6e0
// @ref ?unknown_6000d0@@YA_NXZ=006000d0
// @ref ?unknown_517370@@YIX_N@Z=00517370
// @ref ?unknown_modem_aborted_a72ec4@@3_NA=00a72ec4
// @ref ?ModemRXString@@3PADA=00a72e10
// @ref ?Abort_Modem@NullModemClass@@SAHXZ=005d1db0
// @ref ?Write_To_Serial_Port@WinModemClass@@QAEXPAEH@Z=00734c70
// @ref __strupr=007961e4
// @ref _strstr=007836b0
// @ref _strncpy=007823d0
// @ref _strncmp=00783810
// @ref ??_C@_03DDP@CON?$AA@=007e7e00
// @ref ??_C@_04IFKM@NO?5C?$AA@=007e7ddc
// @ref ??_C@_04KJMB@BUSY?$AA@=007e7de4
// @ref ??_C@_04KNLG@ERRO?$AA@=007e7dcc
// @ref ??_C@_04NAEJ@NO?5D?$AA@=007e7dd4
// @ref ??_C@_0BA@EJNB@From?5Modem?3?5?$CFs?6?$AA@=007e7e04
// @ref ??_C@_0BD@KBMC@D?3?2Ra2?2NullMgr?4CPP?$AA@=007e7d60
// @ref ??_C@_0BD@OFGK@Dial?5result?5is?5?$CFs?6?$AA@=007e7dec
// @ref ??_C@_0BE@DOMF@Dialling?5cancelled?6?$AA@=007e7d88
// @ref ??_C@_0BH@HLBG@Calling?5dial?5function?6?$AA@=007e7e30
// @ref ??_C@_0BJ@LJOJ@Waiting?5for?5dial?5result?6?$AA@=007e7e14
// @ref ??_C@_0BJ@OEJG@Clearing?5results?5buffer?6?$AA@=007e7e48
// @ref ??_C@_0BJ@PLMI@Setting?5modem?5dial?5type?6?$AA@=007e7e64
// @ref ??_C@_0BM@HCDO@TXT_MODEM_CONNERR_REDIALING?$AA@=007e7e8c
// @ref ??_C@_0CK@GCOH@NullModemClass?3?3Dial_Modem?5has?5t@=007e7d9c
// @ref ??_C@_0L@NPIH@TXT_CANCEL?$AA@=007db8c8
// @ref ??_C@_0M@CMMD@Dial_Modem?6?$AA@=007e7ea8
// @ref ??_C@_0M@IOFH@TXT_DIALING?$AA@=007e7e80
// @ref ??_C@_01FEHD@?$AN?$AA@=007e7dc8

DialStatusType NullModemClass::Dial_Modem(char *string, int method, bool reconnect)
{
    bool process = true;
    int delay;
    DialStatusType dialstatus = DIAL_ERROR;
    char buffer[240];
    wchar_t const *text;

    Debug_Printf("Dial_Modem\n");
    if (reconnect == true) {
        text = StringTable::Load_String("TXT_MODEM_CONNERR_REDIALING", 0, "D:\\Ra2\\NullMgr.CPP", 0x581);
    } else {
        text = StringTable::Load_String("TXT_DIALING", 0, "D:\\Ra2\\NullMgr.CPP", 0x583);
    }
    unknown_modem_aborted_a72ec4 = false;
    HWND dialog = unknown_cancel_dialog_6001e0(text, StringTable::Load_String("TXT_CANCEL", 0, "D:\\Ra2\\NullMgr.CPP", 0x587),
                                               &unknown_modem_aborted_a72ec4);
    if (dialog) {
        unknown_dialog_5ff7c0(dialog);

        Debug_Printf("Setting modem dial type\n");
        SerialPort->Set_Modem_Dial_Type(method);
        Debug_Printf("Clearing results buffer\n");
        SerialPort->Get_Modem_Result(60, buffer, 81, -1);
        Debug_Printf("Calling dial function\n");
        SerialPort->Dial_Modem(string);
        SerialPort->Set_Abort_Function(Abort_Modem);
        unknown_modem_aborted_a72ec4 = false;

        delay = unknown_24;
        Debug_Printf("Waiting for dial result\n");
        while (process == true) {
            if (unknown_6000d0() == true || unknown_modem_aborted_a72ec4) {
                dialstatus = DIAL_CANCELED;
                if (SerialPort) {
                    char abort[3] = "\r";
                    SerialPort->Write_To_Serial_Port((unsigned char *)abort, 2);
                }
                Debug_Printf("Dialling cancelled\n");
                break;
            }
            unknown_517370(false);
            memset(buffer, 0, sizeof(buffer));
            delay = SerialPort->Get_Modem_Result(delay, buffer, 81, 15);
            if (delay == -1000) {
                dialstatus = DIAL_CANCELED;
                if (SerialPort) {
                    char abort[3] = "\r";
                    SerialPort->Write_To_Serial_Port((unsigned char *)abort, 2);
                }
                Debug_Printf("Dialling cancelled\n");
                break;
            }
            _strupr(buffer);
            if (strlen(buffer)) {
                Debug_Printf("From Modem: %s\n", buffer);
            }
            if (strstr(buffer, "CON")) {
                memset(ModemRXString, 0, 80);
                strncpy(ModemRXString, buffer, 79);
                dialstatus = DIAL_CONNECTED;
                Debug_Printf("Dial result is %s\n", buffer);
                process = false;
            } else if (strncmp(buffer, "BUSY", 4) == 0) {
                dialstatus = DIAL_BUSY;
                Debug_Printf("Dial result is %s\n", buffer);
                process = false;
            } else if (strncmp(buffer, "NO C", 4) == 0) {
                dialstatus = DIAL_NO_CARRIER;
                Debug_Printf("Dial result is %s\n", buffer);
                process = false;
            } else if (strncmp(buffer, "NO D", 4) == 0) {
                dialstatus = DIAL_NO_DIAL_TONE;
                Debug_Printf("Dial result is %s\n", buffer);
                process = false;
            } else if (strncmp(buffer, "ERRO", 4) == 0) {
                dialstatus = DIAL_ERROR;
                Debug_Printf("Dial result is %s\n", buffer);
                process = false;
            }
            if (delay <= 0) {
                Debug_Printf("NullModemClass::Dial_Modem has timed out\n");
                if (strlen(buffer)) {
                    Debug_Printf("Dial result is %s\n", buffer);
                }
                if (SerialPort) {
                    char abort[3] = "\r";
                    SerialPort->Write_To_Serial_Port((unsigned char *)abort, 2);
                }
                dialstatus = DIAL_TIMEOUT;
                break;
            }
        }

        SerialPort->Set_Abort_Function(0);
        unknown_modem_aborted_a72ec4 = false;
        unknown_dialog_5ff6e0(dialog);
    }
    return dialstatus;
}
