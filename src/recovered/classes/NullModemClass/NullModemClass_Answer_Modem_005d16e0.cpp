// DialStatusType NullModemClass::Answer_Modem(bool reconnect) (0x005D16E0)
// Waits under a cancel dialog for the modem to ring, answers with ATA and
// waits for CONNECT (copied to ModemRXString), BUSY, NO CARRIER or ERROR;
// after the ring a timeout still connects while the modem has carrier.
#include "shared/null_modem.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/ww_message_box.hpp"
#include "shared/string_table.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
#include "shared/campaign.hpp"
extern "C" char *__cdecl strstr(char const *string, char const *search);
extern "C" char *__cdecl strncpy(char *destination, char const *source, unsigned int count);
extern "C" int __cdecl sprintf(char *buffer, char const *format, ...);
// @ref ?SerialPort@@3PAVWinModemClass@@A=00b25bb0
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ?Process@WWMessageBox@@QAEHPBG000_N@Z=005b46b0
// @ref ?unknown_cancel_dialog_6001e0@@YIPAUHWND__@@PBG0PA_N@Z=006001e0
// @ref ?unknown_set_dialog_item_5b0@@YIXPAUHWND__@@J@Z=006002c0
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
// @ref _sprintf=007820f4
// @ref ??_C@_13ECNF@?$AA?5?$AA?$AA@=007d64f4
// @ref ??_C@_0L@NPIH@TXT_CANCEL?$AA@=007db8c8
// @ref ??_C@_0BD@KBMC@D?3?2Ra2?2NullMgr?4CPP?$AA@=007e7d60
// @ref ??_C@_01FEHD@?$AN?$AA@=007e7dc8
// @ref ??_C@_04IFKM@NO?5C?$AA@=007e7ddc
// @ref ??_C@_04KJMB@BUSY?$AA@=007e7de4
// @ref ??_C@_04KNLG@ERRO?$AA@=007e7dcc
// @ref ??_C@_02DILL@?$CFs?$AA@=007e7f2c
// @ref ??_C@_04HFDB@ATA?$AN?$AA@=007e7f64
// @ref ??_C@_04JECC@RING?$AA@=007e7f98
// @ref ??_C@_05CDAC@RING?6?$AA@=007e7f90
// @ref ??_C@_07DKLG@CONNECT?$AA@=007e7f5c
// @ref ??_C@_09PHGC@Connected?$AA@=007e7f30
// @ref ??_C@_0BA@KLM@TXT_ERROR_ERROR?$AA@=007e7f3c
// @ref ??_C@_0BC@CENF@TXT_ERROR_TIMEOUT?$AA@=007e7584
// @ref ??_C@_0BC@CFGM@Waiting?5for?5ring?6?$AA@=007e7fe8
// @ref ??_C@_0BE@FGCE@Answering?5with?5ATA?6?$AA@=007e7f6c
// @ref ??_C@_0BF@DCPO@TXT_WAITING_FOR_CALL?$AA@=007e7ffc
// @ref ??_C@_0BF@HCEG@Answering?5cancelled?6?$AA@=007e7eb4
// @ref ??_C@_0BF@IOBB@Answer?5result?5is?5?$CFs?6?$AA@=007e7edc
// @ref ??_C@_0BK@DBDA@TXT_MODEM_CONNERR_WAITING?$AA@=007e8014
// @ref ??_C@_0BO@KDNG@Get_Modem_Result?5returned?5?$CFd?6?$AA@=007e7fc8
// @ref ??_C@_0CF@GHCI@Get_Modem_Result?5returned?5string@=007e7fa0
// @ref ??_C@_0CM@KADM@NullModemClass?3?3Answer_Modem?5has@=007e7ef4
// @ref ??_C@_0L@MIGB@Connected?6?$AA@=007e7f20
// @ref ??_C@_0O@ENMA@TXT_ANSWERING?$AA@=007e7f80
// @ref ??_C@_0O@LLOG@Result?5is?5?$CFs?6?$AA@=007e7f4c
// @ref ??_C@_0P@FDLO@Not?5connected?6?$AA@=007e7ecc
// @ref ??_C@_06DN@TXT_OK?$AA@=007db8f4

DialStatusType NullModemClass::Answer_Modem(bool reconnect)
{
    bool process;
    bool ring = false;
    int delay;
    DialStatusType dialstatus = DIAL_ERROR;
    char buffer[240];
    wchar_t const *text;

    if (reconnect == true) {
        text = StringTable::Load_String("TXT_MODEM_CONNERR_WAITING", 0, "D:\\Ra2\\NullMgr.CPP", 0x62C);
    } else {
        text = StringTable::Load_String("TXT_WAITING_FOR_CALL", 0, "D:\\Ra2\\NullMgr.CPP", 0x62E);
    }
    Debug_Printf("Waiting for ring\n");
    process = true;
    unknown_modem_aborted_a72ec4 = false;
    HWND dialog = unknown_cancel_dialog_6001e0(text, StringTable::Load_String("TXT_CANCEL", 0, "D:\\Ra2\\NullMgr.CPP", 0x635),
                                               &unknown_modem_aborted_a72ec4);
    if (dialog) {
        unknown_dialog_5ff7c0(dialog);
        SerialPort->Set_Abort_Function(Abort_Modem);
        unknown_modem_aborted_a72ec4 = false;

        delay = 3600;
        while (process == true) {
            if (unknown_6000d0() == true || unknown_modem_aborted_a72ec4) {
                dialstatus = DIAL_CANCELED;
                Debug_Printf("Answering cancelled\n");
                if (SerialPort) {
                    char abort[3] = "\r";
                    SerialPort->Write_To_Serial_Port((unsigned char *)abort, 2);
                }
                break;
            }
            unknown_517370(false);
            memset(buffer, 0, sizeof(buffer));
            delay = SerialPort->Get_Modem_Result(delay, buffer, 81, ring ? 15 : -1);
            Debug_Printf("Get_Modem_Result returned %d\n", delay);
            if (delay == -1000) {
                dialstatus = DIAL_CANCELED;
                Debug_Printf("Answering cancelled\n");
                if (SerialPort) {
                    char abort[3] = "\r";
                    SerialPort->Write_To_Serial_Port((unsigned char *)abort, 2);
                }
                break;
            }
            _strupr(buffer);
            if (strlen(buffer)) {
                Debug_Printf("Get_Modem_Result returned string:%s\n", buffer);
            }
            if (strncmp(buffer, "RING", 4) == 0) {
                Debug_Printf("RING\n");
                unknown_set_dialog_item_5b0(dialog, (LPARAM)StringTable::Load_String("TXT_ANSWERING", 0, "D:\\Ra2\\NullMgr.CPP", 0x66F));
                Debug_Printf("Answering with ATA\n");
                SerialPort->Write_To_Serial_Port((unsigned char *)"ATA\r", strlen("ATA\r"));
                ring = true;
                delay = unknown_24;
            } else if (strstr(buffer, "CONNECT")) {
                memset(ModemRXString, 0, 80);
                strncpy(ModemRXString, buffer, 79);
                dialstatus = DIAL_CONNECTED;
                Debug_Printf("Result is %s\n", buffer);
                process = false;
            } else if (strncmp(buffer, "BUSY", 4) == 0) {
                dialstatus = DIAL_BUSY;
                Debug_Printf("Result is %s\n", buffer);
                process = false;
            } else if (strncmp(buffer, "NO C", 4) == 0) {
                dialstatus = DIAL_NO_CARRIER;
                Debug_Printf("Result is %s\n", buffer);
                process = false;
            } else if (strncmp(buffer, "ERRO", 4) == 0) {
                dialstatus = DIAL_ERROR;
                Debug_Printf("Result is %s\n", buffer);
                WWMessageBox(L" ").Process(StringTable::Load_String("TXT_ERROR_ERROR", 0, "D:\\Ra2\\NullMgr.CPP", 0x687),
                    StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\NullMgr.CPP", 0x687), 0, 0, false);
                process = false;
            }
            if (delay <= 0) {
                if (ring) {
                    if (SerialPort->Get_Modem_Status() & 0x80) {
                        sprintf(ModemRXString, "%s", "Connected");
                        dialstatus = DIAL_CONNECTED;
                        Debug_Printf("Connected\n");
                    } else {
                        Debug_Printf("NullModemClass::Answer_Modem has timed out\n");
                        if (strlen(buffer)) {
                            Debug_Printf("Answer result is %s\n", buffer);
                        }
                        WWMessageBox(L" ").Process(StringTable::Load_String("TXT_ERROR_TIMEOUT", 0, "D:\\Ra2\\NullMgr.CPP", 0x697),
                            StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\NullMgr.CPP", 0x697), 0, 0, false);
                        Debug_Printf("Not connected\n");
                        dialstatus = DIAL_TIMEOUT;
                    }
                    process = false;
                } else {
                    delay = 3600;
                }
            }
        }

        SerialPort->Set_Abort_Function(0);
        unknown_modem_aborted_a72ec4 = false;
        unknown_dialog_5ff6e0(dialog);
    }
    return dialstatus;
}
