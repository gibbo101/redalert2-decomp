// void NullModemClass::Shutdown() (0x005D0570)
// Closes and deletes the serial port, then the connection.
#include "shared/null_modem.hpp"

void NullModemClass::Shutdown()
{
    if (PortHandle != -1 && SerialPort) {
        SerialPort->Serial_Port_Close();
        delete SerialPort;
        SerialPort = 0;
        PortHandle = -1;
        Delete_Connection();
    }
}
