// NullModemClass::~NullModemClass() (0x005D0050)
// Releases the modem entry, the connection and the serial port.
#include "shared/null_modem.hpp"
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??1ModemRegistryEntryClass@@QAE@XZ=0059d4f0
// @ref ?Delete_Connection@NullModemClass@@QAEHXZ=005d0360
// @ref ?Serial_Port_Close@WinModemClass@@QAEXXZ=00734950
// @ref ?SerialPort@@3PAVWinModemClass@@A=00b25bb0
// @ref ??_7ConnManClass@@6B@=007a474c

NullModemClass::~NullModemClass()
{
    if (ModemEntry) {
        delete ModemEntry;
    }
    Delete_Connection();
    Shutdown();
    if (SerialPort) {
        delete SerialPort;
        SerialPort = 0;
    }
}
