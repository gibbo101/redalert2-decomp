// int NullModemClass::Init(int port, int irq, char *dev_name, int baud, char parity, int wordlen, int stopbits) (0x005D00E0)
// Creates the connection and its buffers once, then opens the port (COM1-COM4
// by address, or the registry modem named dev_name): 1 when it opened.
#include "shared/null_modem.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
// @ref ?SerialPort@@3PAVWinModemClass@@A=00b25bb0
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Get_Port_Handle@WinModemClass@@QAEPAXXZ=007354c0
// @ref ??0NullModemConnClass@@QAE@HHHG@Z=005cdb40
// @ref ?Init@NullModemConnClass@@QAEXH@Z=005cdbb0
// @ref ??0WinModemClass@@QAE@XZ=00734120
// @ref ??0ModemRegistryEntryClass@@QAE@H@Z=0059cd00
// @ref ??1ModemRegistryEntryClass@@QAE@XZ=0059d4f0
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref _?com_ids@?1??Init@NullModemClass@@QAEHHHPADHDHH@Z@4PAY04DA=007e7940
// @ref ??_C@_0BG@ECPJ@NullModemClass?3?3Init?6?$AA@=007e7a18
// @ref ??_C@_0BL@PJOH@Creating?5connection?5class?6?$AA@=007e79fc
// @ref ??_C@_0BL@CKIP@Connection?5already?5exists?6?$AA@=007e79e0
// @ref ??_C@_0CA@DFAP@Ready?5to?5initialise?5connection?6?$AA@=007e79c0

int NullModemClass::Init(int port, int irq, char *dev_name, int baud, char parity, int wordlen, int stopbits)
{
    int i;
    static char com_ids[9][5] = {
        "COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8", "COM9"
    };
    char *device;

    Debug_Printf("NullModemClass::Init\n");
    if (SerialPort) {
        PortHandle = (int)SerialPort->Get_Port_Handle();
    } else {
        PortHandle = -1;
    }

    if (!Connection) {
        Debug_Printf("Creating connection class\n");
        Connection = new NullModemConnClass(NumSend, NumReceive, MaxLen, MagicNum);
        Connection->RetryDelta = RetryDelta;
        Connection->MaxRetries = MaxRetries;
        Connection->Timeout = Timeout;
        RXSize = Connection->Actual_Max_Packet() * NumReceive;
        RXBuf = new char[RXSize];
        BuildBuf = new char[MaxLen];
        ReceiveBuf = new char[ReceiveLen];
    } else {
        Debug_Printf("Connection already exists\n");
    }

    RXCount = 0;
    ReceiveIndex = 0;

    if (!SerialPort) {
        SerialPort = new WinModemClass;
    }

    switch (port) {
        case 0x3F8:
            device = com_ids[0];
            break;
        case 0x2F8:
            device = com_ids[1];
            break;
        case 0x3E8:
            device = com_ids[2];
            break;
        case 0x2E8:
            device = com_ids[3];
            break;
        case 1:
            device = dev_name;
            if (ModemEntry) {
                delete ModemEntry;
                ModemEntry = 0;
            }
            for (i = 0; i < 10; i++) {
                ModemEntry = new ModemRegistryEntryClass(i);
                if (ModemEntry->ModemName && !strcmp(dev_name, ModemEntry->ModemName)) {
                    device = ModemEntry->ModemDeviceName;
                    break;
                }
                delete ModemEntry;
                ModemEntry = 0;
            }
            break;
        default:
            device = 0;
            break;
    }

    PortHandle = (int)SerialPort->Serial_Port_Open(device, baud, parity, wordlen, stopbits);
    if (PortHandle == -1) {
        return 0;
    }

    Debug_Printf("Ready to initialise connection\n");
    Connection->Init(PortHandle);
    NumConnections = 1;
    return 1;
}
