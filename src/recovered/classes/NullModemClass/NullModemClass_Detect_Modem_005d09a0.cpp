// bool NullModemClass::Detect_Modem(SerialSettingsType *settings, bool reconnect) (0x005D09A0)
// Initialises the modem in failsafe mode under an "initializing" dialog: echo,
// result codes and verbose results on, AT, the session's init string (each
// '|' part), the registry modem's flow control, compression and error
// correction strings, auto-answer off; three errors are too many. Then checks
// AT again at the normal settings.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#include "shared/null_modem.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/ww_message_box.hpp"
#include "shared/string_table.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
#include "shared/session_state.hpp"
#include "shared/vector_class.hpp"
#include "shared/crt_tokens.hpp"
// @ref ?SerialPort@@3PAVWinModemClass@@A=00b25bb0
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ?Process@WWMessageBox@@QAEHPBG000_N@Z=005b46b0
// @ref ?unknown_cancel_dialog_6001e0@@YIPAUHWND__@@PBG0PA_N@Z=006001e0
// @ref ?unknown_dialog_5ff7c0@@YIXPAUHWND__@@@Z=005ff7c0
// @ref ?unknown_dialog_5ff6e0@@YIXPAUHWND__@@@Z=005ff6e0
// @ref ?Enter_Failsafe_Mode@WinModemClass@@QAE_NXZ=00734670
// @ref ?Leave_Failsafe_Mode@WinModemClass@@QAEXXZ=007347c0
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref _strtok=00782ec2
// @ref ??_C@_13ECNF@?$AA?5?$AA?$AA@=007d64f4
// @ref ??_C@_0L@NPIH@TXT_CANCEL?$AA@=007db8c8
// @ref ??_C@_06DN@TXT_OK?$AA@=007db8f4
// @ref ??_C@_0BD@KBMC@D?3?2Ra2?2NullMgr?4CPP?$AA@=007e7d60
// @ref ??_C@_02BKOD@AT?$AA@=007e7ca8
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_04CKOP@ATE1?$AA@=007e7d24
// @ref ??_C@_04HLLJ@ATV1?$AA@=007e7cac
// @ref ??_C@_04LAHL@ATQ0?$AA@=007e7cdc
// @ref ??_C@_06MGOP@ATS0?$DN0?$AA@=007e7abc
// @ref ??_C@_0BB@MMNG@Detecting?5modem?6?$AA@=007e7d74
// @ref ??_C@_0BC@LDEP@TXT_ERROR_NO_INIT?$AA@=007e7c34
// @ref ??_C@_0BD@MHPF@Modem?5detected?5OK?6?$AA@=007e7a7c
// @ref ??_C@_0BD@OFIP@TXT_ERROR_TOO_MANY?$AA@=007e7a90
// @ref ??_C@_0BF@BPHD@TXT_ERROR_NO_DISABLE?$AA@=007e7aa4
// @ref ??_C@_0BG@CFFN@Sending?5init?5strings?6?$AA@=007e7c64
// @ref ??_C@_0BH@GKEN@TXT_INITIALIZING_MODEM?$AA@=007e7d48
// @ref ??_C@_0BJ@BLMF@Command?5response?5was?5?$CFs?6?$AA@=007e7d08
// @ref ??_C@_0BJ@HAJN@Sending?5echo?5on?5command?6?$AA@=007e7d2c
// @ref ??_C@_0BK@NCDP@TXT_NO_EC_ENABLE_RESPONSE?$AA@=007e7b28
// @ref ??_C@_0BL@OBKP@Sending?5flow?5control?5init?6?$AA@=007e7c18
// @ref ??_C@_0BL@PKMM@TXT_NO_EC_DISABLE_RESPONSE?$AA@=007e7ae4
// @ref ??_C@_0BM@BBGC@TXT_NO_COMP_ENABLE_RESPONSE?$AA@=007e7bb4
// @ref ??_C@_0BN@DEP@TXT_NO_FLOW_CONTROL_RESPONSE?$AA@=007e7bf8
// @ref ??_C@_0BN@MABI@Sending?5disable?5auto?9answer?6?$AA@=007e7ac4
// @ref ??_C@_0BN@NNAP@TXT_NO_COMP_DISABLE_RESPONSE?$AA@=007e7b6c
// @ref ??_C@_0CB@HOHL@Sending?5result?5codes?5on?5command?6@=007e7ce4
// @ref ??_C@_0CG@DADM@Sending?5data?5compression?5enable?5@=007e7bd0
// @ref ??_C@_0CG@JJIH@Sending?5error?5correction?5enable?5@=007e7b44
// @ref ??_C@_0CG@MEBK@Sending?5verbose?5result?5codes?5com@=007e7cb4
// @ref ??_C@_0CH@MBHB@Sending?5data?5compression?5disable@=007e7b8c
// @ref ??_C@_0CH@OHNI@Sending?5error?5correction?5disable@=007e7b00
// @ref ??_C@_0CJ@HEKF@Modem?5failed?5to?5respond?5to?5?8AT?8?5@=007e7c7c
// @ref ??_C@_0L@LECF@TXT_IGNORE?$AA@=007e7c48
// @ref ??_C@_0M@HHHO@Sending?5?$CFs?6?$AA@=007e7c54
// @ref ?ModemCmdNames@@3PAY0BE@DA=007e78f0
// @ref ??_C@_01KALE@?$HM?$AA@=007e7c60

bool NullModemClass::Detect_Modem(SerialSettingsType *settings, bool reconnect)
{
    int status;
    int error_count = 0;
    char buffer[240];

    Debug_Printf("Detecting modem\n");
    if (SerialPort->Enter_Failsafe_Mode()) {
        HWND dialog = unknown_cancel_dialog_6001e0(StringTable::Load_String("TXT_INITIALIZING_MODEM", 0, "D:\\Ra2\\NullMgr.CPP", 0x46E), 0, 0);
        if (dialog) {
            unknown_dialog_5ff7c0(dialog);

            Debug_Printf("Sending echo on command\n");
            Debug_Printf("Command response was %s\n", ModemCmdNames[SerialPort->Send_Command_To_Modem("ATE1", '\r', buffer, 81, 90, 2, -1)]);
            Debug_Printf("Sending result codes on command\n");
            Debug_Printf("Command response was %s\n", ModemCmdNames[SerialPort->Send_Command_To_Modem("ATQ0", '\r', buffer, 81, 90, 2, -1)]);
            Debug_Printf("Sending verbose result codes command\n");
            Debug_Printf("Command response was %s\n", ModemCmdNames[SerialPort->Send_Command_To_Modem("ATV1", '\r', buffer, 81, 90, 2, -1)]);
            unknown_1c = 1;
            unknown_20 = 1;

            status = SerialPort->Send_Command_To_Modem("AT", '\r', buffer, 81, 180, 2, -1);
            if (status < 2) {
                Debug_Printf("Modem failed to respond to 'AT' command\n");
            } else {
            if (settings->InitStringIndex == -1) {
                status = SerialPort->Send_Command_To_Modem("", '\r', buffer, 81, 300, 1, -1);
            } else {
                Debug_Printf("Sending init strings\n");
                char *istr = new char[2 + strlen(unknown_session_a3d298.InitStrings[settings->InitStringIndex])];
                strcpy(istr, unknown_session_a3d298.InitStrings[settings->InitStringIndex]);
                char *tokenptr = strtok(istr, "|");
                while (tokenptr) {
                    Debug_Printf("Sending %s\n", tokenptr);
                    status = SerialPort->Send_Command_To_Modem(tokenptr, '\r', buffer, 81, 90, 1, -1);
                    Debug_Printf("Command response was %s\n", ModemCmdNames[status]);
                    if (status < 2) {
                        if (WWMessageBox(L" ").Process(StringTable::Load_String("TXT_ERROR_NO_INIT", 0, "D:\\Ra2\\NullMgr.CPP", 0x4BF),
                                StringTable::Load_String("TXT_IGNORE", 0, "D:\\Ra2\\NullMgr.CPP", 0x4BF),
                                StringTable::Load_String("TXT_CANCEL", 0, "D:\\Ra2\\NullMgr.CPP", 0x4BF), 0, false)) {
                            delete istr;
                            unknown_dialog_5ff6e0(dialog);
                            SerialPort->Leave_Failsafe_Mode();
                            return false;
                        }
                        error_count++;
                        break;
                    }
                    tokenptr = strtok(0, "|");
                }
                delete istr;
            }

            if (settings->Port == 1 && ModemEntry) {
                char send_string[256] = "AT";
                if (ModemEntry->HardwareFlowControl) {
                    Debug_Printf("Sending flow control init\n");
                    strcpy(&send_string[2], ModemEntry->HardwareFlowControl);
                    status = SerialPort->Send_Command_To_Modem(send_string, '\r', buffer, 81, 60, 1, -1);
                    Debug_Printf("Command response was %s\n", ModemCmdNames[status]);
                    if (status != 2 && status != 3) {
                        if (WWMessageBox(L" ").Process(StringTable::Load_String("TXT_NO_FLOW_CONTROL_RESPONSE", 0, "D:\\Ra2\\NullMgr.CPP", 0x4DF),
                                StringTable::Load_String("TXT_IGNORE", 0, "D:\\Ra2\\NullMgr.CPP", 0x4DF),
                                StringTable::Load_String("TXT_CANCEL", 0, "D:\\Ra2\\NullMgr.CPP", 0x4DF), 0, false)) {
                            unknown_dialog_5ff6e0(dialog);
                            SerialPort->Leave_Failsafe_Mode();
                            return false;
                        }
                    }
                }
                if (settings->Compression) {
                    if (ModemEntry->CompressionEnable) {
                        Debug_Printf("Sending data compression enable init\n");
                        strcpy(&send_string[2], ModemEntry->CompressionEnable);
                        SerialPort->Send_Command_To_Modem(send_string, '\r', buffer, 81, 60, 1, -1);
                        Debug_Printf("Command response was %s\n", ModemCmdNames[status]);
                        if (status != 2 && status != 3) {
                            if (WWMessageBox(L" ").Process(StringTable::Load_String("TXT_NO_COMP_ENABLE_RESPONSE", 0, "D:\\Ra2\\NullMgr.CPP", 0x4F2),
                                    StringTable::Load_String("TXT_IGNORE", 0, "D:\\Ra2\\NullMgr.CPP", 0x4F2),
                                    StringTable::Load_String("TXT_CANCEL", 0, "D:\\Ra2\\NullMgr.CPP", 0x4F2), 0, false)) {
                                unknown_dialog_5ff6e0(dialog);
                                SerialPort->Leave_Failsafe_Mode();
                                return false;
                            }
                        }
                    }
                } else {
                    if (ModemEntry->CompressionDisable) {
                        Debug_Printf("Sending data compression disable init\n");
                        strcpy(&send_string[2], ModemEntry->CompressionDisable);
                        SerialPort->Send_Command_To_Modem(send_string, '\r', buffer, 81, 60, 1, -1);
                        Debug_Printf("Command response was %s\n", ModemCmdNames[status]);
                        if (status != 2 && status != 3) {
                            if (WWMessageBox(L" ").Process(StringTable::Load_String("TXT_NO_COMP_DISABLE_RESPONSE", 0, "D:\\Ra2\\NullMgr.CPP", 0x501),
                                    StringTable::Load_String("TXT_IGNORE", 0, "D:\\Ra2\\NullMgr.CPP", 0x501),
                                    StringTable::Load_String("TXT_CANCEL", 0, "D:\\Ra2\\NullMgr.CPP", 0x501), 0, false)) {
                                unknown_dialog_5ff6e0(dialog);
                                SerialPort->Leave_Failsafe_Mode();
                                return false;
                            }
                        }
                    }
                }
                if (settings->ErrorCorrection) {
                    if (ModemEntry->ErrorCorrectionEnable) {
                        Debug_Printf("Sending error correction enable init\n");
                        strcpy(&send_string[2], ModemEntry->ErrorCorrectionEnable);
                        SerialPort->Send_Command_To_Modem(send_string, '\r', buffer, 81, 60, 1, -1);
                        Debug_Printf("Command response was %s\n", ModemCmdNames[status]);
                        if (status != 2 && status != 3) {
                            if (WWMessageBox(L" ").Process(StringTable::Load_String("TXT_NO_EC_ENABLE_RESPONSE", 0, "D:\\Ra2\\NullMgr.CPP", 0x515),
                                    StringTable::Load_String("TXT_IGNORE", 0, "D:\\Ra2\\NullMgr.CPP", 0x515),
                                    StringTable::Load_String("TXT_CANCEL", 0, "D:\\Ra2\\NullMgr.CPP", 0x515), 0, false)) {
                                unknown_dialog_5ff6e0(dialog);
                                SerialPort->Leave_Failsafe_Mode();
                                return false;
                            }
                        }
                    }
                } else {
                    if (ModemEntry->ErrorCorrectionDisable) {
                        Debug_Printf("Sending error correction disable init\n");
                        strcpy(&send_string[2], ModemEntry->ErrorCorrectionDisable);
                        SerialPort->Send_Command_To_Modem(send_string, '\r', buffer, 81, 60, 1, -1);
                        Debug_Printf("Command response was %s\n", ModemCmdNames[status]);
                        if (status != 2 && status != 3) {
                            if (WWMessageBox(L" ").Process(StringTable::Load_String("TXT_NO_EC_DISABLE_RESPONSE", 0, "D:\\Ra2\\NullMgr.CPP", 0x524),
                                    StringTable::Load_String("TXT_IGNORE", 0, "D:\\Ra2\\NullMgr.CPP", 0x524),
                                    StringTable::Load_String("TXT_CANCEL", 0, "D:\\Ra2\\NullMgr.CPP", 0x524), 0, false)) {
                                unknown_dialog_5ff6e0(dialog);
                                SerialPort->Leave_Failsafe_Mode();
                                return false;
                            }
                        }
                    }
                }
            }

            Debug_Printf("Sending disable auto-answer\n");
            status = SerialPort->Send_Command_To_Modem("ATS0=0", '\r', buffer, 81, 90, 2, -1);
            Debug_Printf("Command response was %s\n", ModemCmdNames[status]);
            if (status != 2) {
                if (WWMessageBox(L" ").Process(StringTable::Load_String("TXT_ERROR_NO_DISABLE", 0, "D:\\Ra2\\NullMgr.CPP", 0x536),
                        StringTable::Load_String("TXT_IGNORE", 0, "D:\\Ra2\\NullMgr.CPP", 0x536),
                        StringTable::Load_String("TXT_CANCEL", 0, "D:\\Ra2\\NullMgr.CPP", 0x536), 0, false)) {
                    unknown_dialog_5ff6e0(dialog);
                    SerialPort->Leave_Failsafe_Mode();
                    return false;
                }
                error_count++;
            }

            if (error_count >= 3) {
                WWMessageBox(L" ").Process(StringTable::Load_String("TXT_ERROR_TOO_MANY", 0, "D:\\Ra2\\NullMgr.CPP", 0x543),
                    StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\NullMgr.CPP", 0x543), 0, 0, false);
                unknown_dialog_5ff6e0(dialog);
                SerialPort->Leave_Failsafe_Mode();
                return false;
            }

            unknown_dialog_5ff6e0(dialog);
            Debug_Printf("Modem detected OK\n");
            SerialPort->Leave_Failsafe_Mode();
            status = SerialPort->Send_Command_To_Modem("AT", '\r', buffer, 81, 90, 2, -1);
            if (status < 2) {
                Debug_Printf("Modem failed to respond to 'AT' command\n");
                return false;
            }
            return true;
            }
            unknown_dialog_5ff6e0(dialog);
        }
        SerialPort->Leave_Failsafe_Mode();
    }
    return false;
}
