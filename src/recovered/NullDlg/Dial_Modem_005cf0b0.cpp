// bool __fastcall Dial_Modem(SerialSettingsType *settings, bool reconnect) (0x005CF0B0)
// Dials DialString: logs the modem status lines; on reconnect an existing
// carrier is enough, otherwise a live line is hung up first. Detects the modem
// (a 14400 or 28800 modem is retried at 19200 or 38400), then dials and
// reports the result (a cancelled call is hung up). Modem servicing is off meanwhile.
#include "shared/null_dlg.hpp"
#include "shared/serial_progress.hpp"
#include "shared/ww_message_box.hpp"
#include "shared/string_table.hpp"
#include "shared/debug_printf.hpp"
#include "shared/map_view.hpp"
// @ref ?serial_manager_00a40a28@@3VNullModemClass@@A=00a40a28
// @ref ?serial_session_flags_00a3fac0@@3IA=00a3fac0
// @ref ?DialSettings@@3PAUSerialSettingsType@@A=00a72dc4
// @ref ?unknown_flags_a3f600@@3EA=00a3f600
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Get_Modem_Status@NullModemClass@@QAEHXZ=005d1e50
// @ref ?Hangup_Modem@NullModemClass@@QAE_NXZ=005d1b70
// @ref ?Shutdown@NullModemClass@@QAEXXZ=005d0570
// @ref ?Init@NullModemClass@@QAEHHHPADHDHH@Z=005d00e0
// @ref ?Setup_Modem_Echo@NullModemClass@@QAEXP6IXD@Z@Z=005d1d20
// @ref ?unknown_text_buffer_append_005cfd70@@YIXD@Z=005cfd70
// @ref ?Detect_Modem@NullModemClass@@QAE_NPAUSerialSettingsType@@_N@Z=005d09a0
// @ref ?Dial_Modem@NullModemClass@@QAE?AW4DialStatusType@@PADH_N@Z=005d1350
// @ref ?DialString@@3PADA=00a72d78
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Flag_To_Redraw@GScreenClass@@UAEXH@Z=004e09a0
// @ref ?Render@GScreenClass@@UAEXXZ=004e0b30
// @ref ?unknown_5d1d40@NullModemClass@@QAEXXZ=005d1d40
// @ref ?Translate_Line_Ends@NullModemClass@@QAEXXZ=005d1d50
// @ref ?Clear_Receive_Buffer@NullModemClass@@QAEXXZ=005d1da0
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ?Process@WWMessageBox@@QAEHPBG000_N@Z=005b46b0
// @ref ??_C@_13ECNF@?$AA?5?$AA?$AA@=007d64f4
// @ref ??_C@_06DN@TXT_OK?$AA@=007db8f4
// @ref ??_C@_0BD@MKPO@D?3?2Ra2?2NullDlg?4CPP?$AA@=007e74bc
// @ref ??_C@_0BF@LNNF@TXT_DIALING_CANCELED?$AA@=007e7504
// @ref ??_C@_0CG@JPJK@Dial_Modem?5returned?5?8DIAL_CANCEL@=007e751c
// @ref ??_C@_0BB@EDPM@TXT_NO_DIAL_TONE?$AA@=007e7544
// @ref ??_C@_0CJ@GCIB@Dial_Modem?5returned?5?8DIAL_NO_DIA@=007e7558
// @ref ??_C@_0BC@CENF@TXT_ERROR_TIMEOUT?$AA@=007e7584
// @ref ??_C@_0CE@HJFB@Dial_Modem?5returned?5?8DIAL_TIMEOU@=007e7598
// @ref ??_C@_0BD@HMLB@TXT_NUMBER_INVALID?$AA@=007e75bc
// @ref ??_C@_0CC@CME@Dial_Modem?5returned?5?8DIAL_ERROR?8@=007e75d0
// @ref ??_C@_0O@GKIA@TXT_LINE_BUSY?$AA@=007e75f4
// @ref ??_C@_0CB@GNGL@Dial_Modem?5returned?5?8DIAL_BUSY?8?6@=007e7604
// @ref ??_C@_0P@NPH@TXT_NO_CARRIER?$AA@=007e7628
// @ref ??_C@_0CH@IIOE@Dial_Modem?5returned?5?8DIAL_NO_CAR@=007e7638
// @ref ??_C@_0CG@KOPL@Dial_Modem?5returned?5?8DIAL_CONNEC@=007e7660
// @ref ??_C@_0P@CHNG@Ready?5to?5dial?6?$AA@=007e7688
// @ref ??_C@_0BI@EDGA@TXT_ERROR_IN_INITSTRING?$AA@=007e7698
// @ref ??_C@_0BO@JGCB@Detect_Modem?5failed?5at?519200?6?$AA@=007e76b0
// @ref ??_C@_0BF@PLNI@Upshifting?5to?519200?6?$AA@=007e76d0
// @ref ??_C@_0BO@MCKI@Detect_Modem?5failed?5at?538400?6?$AA@=007e76e8
// @ref ??_C@_0BF@KPFB@Upshifting?5to?538400?6?$AA@=007e7708
// @ref ??_C@_0BG@JBNM@TXT_UNABLE_FIND_MODEM?$AA@=007e7720
// @ref ??_C@_0BF@BBGJ@Detect_Modem?5failed?6?$AA@=007e7738
// @ref ??_C@_0CE@FCOP@Modem?5already?5on?9line?5?9?5hanging?5@=007e7750
// @ref ??_C@_08HHPO@?5CD?3?5?$CFs?6?$AA@=007e7774
// @ref ??_C@_08NOBA@?5RI?3?5?$CFs?6?$AA@=007e7780
// @ref ??_C@_08JHKL@DSR?3?5?$CFs?6?$AA@=007e778c
// @ref ??_C@_08DDCK@CTS?3?5?$CFs?6?$AA@=007e7798
// @ref ??_C@_05HIBB@CLEAR?$AA@=007e77a4
// @ref ??_C@_03BCLC@SET?$AA@=007e77ac
// @ref ??_C@_0CN@LPEB@Get_Modem_Status?5indicates?5the?5f@=007e77b0
// @ref ??_C@_0M@PAA@Dial?5Modem?6?$AA@=007e77e0

bool __fastcall Dial_Modem(SerialSettingsType *settings, bool reconnect)
{
    bool connected = false;
    DialStatusType dialstatus;
    int modemstatus;

    Debug_Printf("Dial Modem\n");
    serial_session_flags_00a3fac0 &= ~1;
    DialSettings = settings;
    modemstatus = serial_manager_00a40a28.Get_Modem_Status();
    Debug_Printf("Get_Modem_Status indicates the following...\n");
    Debug_Printf("CTS: %s\n", (modemstatus & 0x10) ? "SET" : "CLEAR");
    Debug_Printf("DSR: %s\n", (modemstatus & 0x20) ? "SET" : "CLEAR");
    Debug_Printf(" RI: %s\n", (modemstatus & 0x40) ? "SET" : "CLEAR");
    Debug_Printf(" CD: %s\n", (modemstatus & 0x80) ? "SET" : "CLEAR");

    if (reconnect) {
        if (modemstatus & 0x80) {
            connected = true;
            serial_session_flags_00a3fac0 |= 1;
            return connected;
        }
    } else if (modemstatus & 0x80) {
        Debug_Printf("Modem already on-line - hanging up\n");
        serial_manager_00a40a28.Hangup_Modem();
        serial_session_flags_00a3fac0 &= ~1;
    }

    serial_manager_00a40a28.Setup_Modem_Echo(unknown_text_buffer_append_005cfd70);
    modemstatus = serial_manager_00a40a28.Detect_Modem(settings, reconnect);
    if (!modemstatus) {
        Debug_Printf("Detect_Modem failed\n");
        serial_manager_00a40a28.unknown_5d1d40();
        serial_manager_00a40a28.Translate_Line_Ends();
        serial_manager_00a40a28.Clear_Receive_Buffer();
        switch (settings->Baud) {
            case 14400:
                Debug_Printf("Upshifting to 19200\n");
                settings->Baud = 19200;
                Shutdown_Modem();
                serial_manager_00a40a28.Init(settings->Port, settings->IRQ, settings->ModemName, settings->Baud, 0, 8, 1);
                serial_manager_00a40a28.Setup_Modem_Echo(unknown_text_buffer_append_005cfd70);
                modemstatus = serial_manager_00a40a28.Detect_Modem(settings, reconnect);
                if (!modemstatus) {
                    Debug_Printf("Detect_Modem failed at 19200\n");
                    serial_manager_00a40a28.unknown_5d1d40();
                    serial_manager_00a40a28.Translate_Line_Ends();
                    serial_manager_00a40a28.Clear_Receive_Buffer();
                    WWMessageBox(L" ").Process(StringTable::Load_String("TXT_UNABLE_FIND_MODEM", 0, "D:\\Ra2\\NullDlg.CPP", 0x1A08),
                        StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\NullDlg.CPP", 0x1A08), 0, 0, false);
                    serial_session_flags_00a3fac0 |= 1;
                    return connected;
                }
                break;
            case 28800:
                Debug_Printf("Upshifting to 38400\n");
                settings->Baud = 38400;
                Shutdown_Modem();
                serial_manager_00a40a28.Init(settings->Port, settings->IRQ, settings->ModemName, settings->Baud, 0, 8, 1);
                serial_manager_00a40a28.Setup_Modem_Echo(unknown_text_buffer_append_005cfd70);
                modemstatus = serial_manager_00a40a28.Detect_Modem(settings, reconnect);
                if (!modemstatus) {
                    Debug_Printf("Detect_Modem failed at 38400\n");
                    serial_manager_00a40a28.unknown_5d1d40();
                    serial_manager_00a40a28.Translate_Line_Ends();
                    serial_manager_00a40a28.Clear_Receive_Buffer();
                    WWMessageBox(L" ").Process(StringTable::Load_String("TXT_UNABLE_FIND_MODEM", 0, "D:\\Ra2\\NullDlg.CPP", 0x1A1D),
                        StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\NullDlg.CPP", 0x1A1D), 0, 0, false);
                    serial_session_flags_00a3fac0 |= 1;
                    return connected;
                }
                break;
            default:
                WWMessageBox(L" ").Process(StringTable::Load_String("TXT_UNABLE_FIND_MODEM", 0, "D:\\Ra2\\NullDlg.CPP", 0x1A24),
                    StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\NullDlg.CPP", 0x1A24), 0, 0, false);
                serial_session_flags_00a3fac0 |= 1;
                return connected;
        }
    } else if (modemstatus == -1) {
        serial_manager_00a40a28.unknown_5d1d40();
        serial_manager_00a40a28.Translate_Line_Ends();
        serial_manager_00a40a28.Clear_Receive_Buffer();
        WWMessageBox(L" ").Process(StringTable::Load_String("TXT_ERROR_IN_INITSTRING", 0, "D:\\Ra2\\NullDlg.CPP", 0x1A31),
            StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\NullDlg.CPP", 0x1A31), 0, 0, false);
        serial_session_flags_00a3fac0 |= 1;
        return connected;
    }

    Debug_Printf("Ready to dial\n");
    dialstatus = serial_manager_00a40a28.Dial_Modem(DialString, settings->DialMethod, reconnect);
    if (reconnect) {
        Map.Flag_To_Redraw(2);
        Map.Render();
    }
    switch (dialstatus) {
        case DIAL_CONNECTED:
            Debug_Printf("Dial_Modem returned 'DIAL_CONNECTED'\n");
            connected = true;
            break;
        case DIAL_NO_CARRIER:
            Debug_Printf("Dial_Modem returned 'DIAL_NO_CARRIER'\n");
            WWMessageBox(L" ").Process(StringTable::Load_String("TXT_NO_CARRIER", 0, "D:\\Ra2\\NullDlg.CPP", 0x1A66),
                StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\NullDlg.CPP", 0x1A66), 0, 0, false);
            connected = false;
            break;
        case DIAL_BUSY:
            Debug_Printf("Dial_Modem returned 'DIAL_BUSY'\n");
            WWMessageBox(L" ").Process(StringTable::Load_String("TXT_LINE_BUSY", 0, "D:\\Ra2\\NullDlg.CPP", 0x1A6C),
                StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\NullDlg.CPP", 0x1A6C), 0, 0, false);
            connected = false;
            break;
        case DIAL_ERROR:
            Debug_Printf("Dial_Modem returned 'DIAL_ERROR'\n");
            WWMessageBox(L" ").Process(StringTable::Load_String("TXT_NUMBER_INVALID", 0, "D:\\Ra2\\NullDlg.CPP", 0x1A72),
                StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\NullDlg.CPP", 0x1A72), 0, 0, false);
            connected = false;
            break;
        case DIAL_TIMEOUT:
            Debug_Printf("Dial_Modem returned 'DIAL_TIMEOUT'\n");
            WWMessageBox(L" ").Process(StringTable::Load_String("TXT_ERROR_TIMEOUT", 0, "D:\\Ra2\\NullDlg.CPP", 0x1A78),
                StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\NullDlg.CPP", 0x1A78), 0, 0, false);
            connected = false;
            break;
        case DIAL_NO_DIAL_TONE:
            Debug_Printf("Dial_Modem returned 'DIAL_NO_DIAL_TONE'\n");
            WWMessageBox(L" ").Process(StringTable::Load_String("TXT_NO_DIAL_TONE", 0, "D:\\Ra2\\NullDlg.CPP", 0x1A7E),
                StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\NullDlg.CPP", 0x1A7E), 0, 0, false);
            connected = false;
            break;
        case DIAL_CANCELED:
            Debug_Printf("Dial_Modem returned 'DIAL_CANCELLED'\n");
            serial_manager_00a40a28.Hangup_Modem();
            serial_session_flags_00a3fac0 &= ~1;
            WWMessageBox(L" ").Process(StringTable::Load_String("TXT_DIALING_CANCELED", 0, "D:\\Ra2\\NullDlg.CPP", 0x1A86),
                StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\NullDlg.CPP", 0x1A86), 0, 0, false);
            connected = false;
            break;
    }

    serial_manager_00a40a28.unknown_5d1d40();
    serial_manager_00a40a28.Translate_Line_Ends();
    serial_manager_00a40a28.Clear_Receive_Buffer();
    serial_session_flags_00a3fac0 |= 1;
    return connected;
}
