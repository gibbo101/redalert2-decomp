// int NullModemClass::Detect_Port(SerialSettingsType *settings) (0x005D03E0)
// Opens the settings' port (COM1-COM4 by address, or the registry modem
// named in the settings) to see that it works, and closes it again: 0 when
// it opened, 1 otherwise.
#include "shared/null_modem.hpp"
#include "shared/crt_string.hpp"
// @ref ?SerialPort@@3PAVWinModemClass@@A=00b25bb0
// @ref ??0WinModemClass@@QAE@XZ=00734120
// @ref ?Serial_Port_Close@WinModemClass@@QAEXXZ=00734950
// @ref ??0ModemRegistryEntryClass@@QAE@H@Z=0059cd00
// @ref ??1ModemRegistryEntryClass@@QAE@XZ=0059d4f0
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??_C@_04JCPL@COM1?$AA@=007e7970
// @ref ??_C@_04GNEC@COM2?$AA@=007e7975
// @ref ??_C@_04MHNF@COM3?$AA@=007e797a
// @ref ??_C@_04JCDA@COM4?$AA@=007e797f

int NullModemClass::Detect_Port(SerialSettingsType *settings)
{
    if (!SerialPort) {
        SerialPort = new WinModemClass;
    } else {
        SerialPort->Serial_Port_Close();
    }

    int baud = settings->Baud;
    char const *com;
    switch (settings->Port) {
        case 0x3F8:
            com = "COM1";
            break;
        case 0x2F8:
            com = "COM2";
            break;
        case 0x3E8:
            com = "COM3";
            break;
        case 0x2E8:
            com = "COM4";
            break;
        case 1: {
            com = settings->ModemName;
            if (ModemEntry) {
                delete ModemEntry;
                ModemEntry = 0;
            }
            for (int i = 0; i < 10; i++) {
                ModemEntry = new ModemRegistryEntryClass(i);
                if (ModemEntry->ModemName && !strcmp(settings->ModemName, ModemEntry->ModemName)) {
                    com = ModemEntry->ModemDeviceName;
                    break;
                }
                delete ModemEntry;
                ModemEntry = 0;
            }
            break;
        }
        default:
            return 1;
    }

    if (SerialPort->Serial_Port_Open(com, baud, 0, 8, 1) == INVALID_HANDLE_VALUE) {
        return 1;
    }
    SerialPort->Serial_Port_Close();
    return 0;
}
