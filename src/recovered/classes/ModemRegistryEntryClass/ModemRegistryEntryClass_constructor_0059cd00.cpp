// ModemRegistryEntryClass::ModemRegistryEntryClass (0x0059CD00)
#include "shared/null_modem.hpp"
#include "shared/crt_string.hpp"
#include "shared/crt_memory.hpp"
#include "shared/crt_tokens.hpp"
#include "shared/debug_printf.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?Search_Registry_Key@@YIPAUHKEY__@@PAU1@PBD1@Z=0059cba0
// @ref ?unknown_flag_839c4c@@3_NA=00839c4c
// @ref ??_C@_04MBMK@?$CF04d?$AA@=007e2abc
// @ref ??_C@_05LCAF@Class?$AA@=007e29a4
// @ref ??_C@_05LDDB@Model?$AA@=007e2994
// @ref ??_C@_06LCIG@Driver?$AA@=007e2800
// @ref ??_C@_08BIGC@Settings?$AA@=007e2940
// @ref ??_C@_08IDAB@PORTNAME?$AA@=007e27f4
// @ref ??_C@_0BA@LKPI@Compression_Off?$AA@=007e2884
// @ref ??_C@_0BA@MKJO@ErrorControl_On?$AA@=007e2930
// @ref ??_C@_0BB@FGMM@ErrorControl_Off?$AA@=007e28f4
// @ref ??_C@_0BB@LGEI@FlowControl_Hard?$AA@=007e2848
// @ref ??_C@_0BC@INBJ@Modem?5name?5is?5?$CFs?6?$AA@=007e2980
// @ref ??_C@_0BG@FEH@Modem?5attached?5to?5?$CFs?6?$AA@=007e294c
// @ref ??_C@_0BK@JAHE@PNP?5Modem?5attached?5to?5?$CFs?6?$AA@=007e27d8
// @ref ??_C@_0CD@JMLE@Failed?5to?5find?5port?5for?5device?5?$CF@=007e27b4
// @ref ??_C@_0CF@LIPE@Modem?5compression?5enable?5string?3@=007e2894
// @ref ??_C@_0CG@BALI@Modem?5compression?5disable?5string@=007e285c
// @ref ??_C@_0CH@BJBL@Modem?5error?5control?5enable?5strin@=007e2908
// @ref ??_C@_0CH@OBIP@System?2CurrentControlSet?2Control@=007e2a18
// @ref ??_C@_0CI@DKLF@System?2CurrentControlSet?2Control@=007e29ac
// @ref ??_C@_0CI@PFBJ@Modem?5error?5control?5disable?5stri@=007e28cc
// @ref ??_C@_0CO@PGCH@System?2CurrentControlSet?2Service@=007e2a8c
// @ref ??_C@_0CP@GHI@Modem?5hardware?5flow?5control?5enab@=007e2818
// @ref ??_C@_0ED@KIFK@Unable?5to?5find?5System?2CurrentCon@=007e29d4
// @ref ??_C@_0EK@LGKK@Unable?5to?5find?5System?2CurrentCon@=007e2a40
// @ref ??_C@_0L@LPIL@AttachedTo?$AA@=007e2974
// @ref ??_C@_0O@DNPK@PnPAttachedTo?$AA@=007e2964
// @ref ??_C@_0P@POLI@Compression_On?$AA@=007e28bc
// @ref ??_C@_06KIEN@Modem?2?$AA@=007e2810
// @ref ??_C@_01PCFE@?2?$AA@=007cc944
// @ref ??_C@_04KFCP@Enum?$AA@=007e2808
// @ref ??_C@_05BJKG@Modem?$AA@=007e299c

ModemRegistryEntryClass::ModemRegistryEntryClass(int modem_number)
{
    HKEY key;
    unsigned char return_buf[256];
    DWORD retbuf_size = sizeof(return_buf);
    int pnp = 0;

    ModemName = 0;
    ModemDeviceName = 0;
    ErrorCorrectionEnable = 0;
    ErrorCorrectionDisable = 0;
    CompressionEnable = 0;
    CompressionDisable = 0;
    HardwareFlowControl = 0;

    char which_modem[5];
    wsprintfA(which_modem, "%04d", modem_number);

    if (unknown_flag_839c4c) {
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "System\\CurrentControlSet\\Services\\Class\\Modem", 0, KEY_READ, &key) != 0) {
            return;
        }
        if (RegOpenKeyExA(key, which_modem, 0, KEY_READ, &key) != 0) {
            Debug_Printf("Unable to find System\\CurrentControlSet\\Services\\Class\\Modem in registry\n");
            return;
        }
    } else {
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "System\\CurrentControlSet\\Control\\Class", 0, KEY_READ, &key) != 0) {
            Debug_Printf("Unable to find System\\CurrentControlSet\\Control\\Class in registry\n");
            return;
        }
        char key_path[256];
        char sub_key_name[256];
        char class_name[256];
        DWORD sub_key_name_size;
        DWORD class_name_size;
        FILETIME last_write_time;
        HKEY class_key;
        for (DWORD index = 0;; index++) {
            sub_key_name_size = 256;
            class_name_size = 256;
            if (RegEnumKeyExA(key, index, sub_key_name, &sub_key_name_size, 0, class_name, &class_name_size, &last_write_time) != 0) {
                return;
            }
            strcpy(key_path, "System\\CurrentControlSet\\Control\\Class\\");
            strcat(key_path, sub_key_name);
            if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, key_path, 0, KEY_READ, &class_key) == 0) {
                retbuf_size = sizeof(return_buf);
                if (RegQueryValueExA(class_key, "Class", 0, 0, return_buf, &retbuf_size) == 0
                    && _stricmp((char *)return_buf, "Modem") == 0) {
                    break;
                }
            }
        }
        strcpy(key_path, "System\\CurrentControlSet\\Control\\Class\\");
        strcat(key_path, sub_key_name);
        strcat(key_path, "\\");
        strcat(key_path, which_modem);
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, key_path, 0, KEY_READ, &key) != 0) {
            return;
        }
    }

    retbuf_size = sizeof(return_buf);
    if (RegQueryValueExA(key, "Model", 0, 0, return_buf, &retbuf_size) != 0) {
        RegCloseKey(key);
        return;
    }
    ModemName = new char[retbuf_size + 1];
    memcpy(ModemName, return_buf, retbuf_size);
    Debug_Printf("Modem name is %s\n", ModemName);

    retbuf_size = sizeof(return_buf);
    if (RegQueryValueExA(key, "AttachedTo", 0, 0, return_buf, &retbuf_size) != 0) {
        retbuf_size = sizeof(return_buf);
        if (unknown_flag_839c4c || RegQueryValueExA(key, "PnPAttachedTo", 0, 0, return_buf, &retbuf_size) != 0) {
            pnp = 1;
            ModemDeviceName = new char[strlen(ModemName) + 1];
            strcpy(ModemDeviceName, ModemName);
        } else {
            ModemDeviceName = new char[retbuf_size + 1];
            memcpy(ModemDeviceName, return_buf, retbuf_size);
        }
    } else {
        ModemDeviceName = new char[retbuf_size + 1];
        memcpy(ModemDeviceName, return_buf, retbuf_size);
    }
    Debug_Printf("Modem attached to %s\n", ModemDeviceName);

    key = Get_Registry_Sub_Key(key, "Settings", true);
    if (!key) {
        return;
    }

    retbuf_size = sizeof(return_buf);
    if (RegQueryValueExA(key, "ErrorControl_On", 0, 0, return_buf, &retbuf_size) == 0) {
        ErrorCorrectionEnable = new char[retbuf_size + 1];
        memcpy(ErrorCorrectionEnable, return_buf, retbuf_size);
        Debug_Printf("Modem error control enable string: %s\n", ErrorCorrectionEnable);
    }
    retbuf_size = sizeof(return_buf);
    if (RegQueryValueExA(key, "ErrorControl_Off", 0, 0, return_buf, &retbuf_size) == 0) {
        ErrorCorrectionDisable = new char[retbuf_size + 1];
        memcpy(ErrorCorrectionDisable, return_buf, retbuf_size);
        Debug_Printf("Modem error control disable string: %s\n", ErrorCorrectionDisable);
    }
    retbuf_size = sizeof(return_buf);
    if (RegQueryValueExA(key, "Compression_On", 0, 0, return_buf, &retbuf_size) == 0) {
        CompressionEnable = new char[retbuf_size + 1];
        memcpy(CompressionEnable, return_buf, retbuf_size);
        Debug_Printf("Modem compression enable string: %s\n", CompressionEnable);
    }
    retbuf_size = sizeof(return_buf);
    if (RegQueryValueExA(key, "Compression_Off", 0, 0, return_buf, &retbuf_size) == 0) {
        CompressionDisable = new char[retbuf_size + 1];
        memcpy(CompressionDisable, return_buf, retbuf_size);
        Debug_Printf("Modem compression disable string: %s\n", CompressionDisable);
    }
    retbuf_size = sizeof(return_buf);
    if (RegQueryValueExA(key, "FlowControl_Hard", 0, 0, return_buf, &retbuf_size) == 0) {
        HardwareFlowControl = new char[retbuf_size + 1];
        memcpy(HardwareFlowControl, return_buf, retbuf_size);
        Debug_Printf("Modem hardware flow control enable string: %s\n", HardwareFlowControl);
    }
    RegCloseKey(key);

    if (pnp) {
        char search_string[256] = "Modem\\";
        strcat(search_string, which_modem);
        key = Get_Registry_Sub_Key(HKEY_LOCAL_MACHINE, "Enum", false);
        if (!key) {
            return;
        }
        HKEY port_key = Search_Registry_Key(key, "Driver", search_string);
        if (port_key) {
            retbuf_size = sizeof(return_buf);
            if (RegQueryValueExA(port_key, "PORTNAME", 0, 0, return_buf, &retbuf_size) == 0) {
                if (ModemDeviceName) {
                    delete[] ModemDeviceName;
                }
                ModemDeviceName = new char[retbuf_size + 1];
                memcpy(ModemDeviceName, return_buf, retbuf_size);
                Debug_Printf("PNP Modem attached to %s\n", ModemName);
            }
        } else if (ModemDeviceName && ModemName && strcmp(ModemName, ModemDeviceName) == 0) {
            Debug_Printf("Failed to find port for device %s\n", ModemName);
            delete[] ModemName;
            ModemName = 0;
            delete[] ModemDeviceName;
            ModemDeviceName = 0;
        }
        RegCloseKey(key);
    }
}
