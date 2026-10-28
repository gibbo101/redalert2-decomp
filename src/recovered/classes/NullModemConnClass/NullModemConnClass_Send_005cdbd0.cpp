// int NullModemConnClass::Send(char *buf, int buflen, void *extrabuf, int extralen, bool flagged, unsigned short id) -- 0x005CDBD0
// Slot 9: frames the packet for the serial line (magic 0xDABD, length,
// magic 0xDEAF, the data, a rotating checksum of the data and a carriage
// return) in SendBuf and writes it through the serial port object (SerialPort,
// 0x00B25BB0; Write_To_Serial_Port 0x00734C70). Nothing is sent without an
// open port. The extra buffer and flags are unused here.
#include "shared/null_modem.hpp"
#include "shared/crt_memory.hpp"
// @ref ?SerialPort@@3PAVWinModemClass@@A=00b25bb0
// @ref ?Write_To_Serial_Port@WinModemClass@@QAEXPAEH@Z=00734c70
// @ref ?Compute_CRC@NullModemConnClass@@SIHPADH@Z=005cdc80

int NullModemConnClass::Send(char *buf, int buflen, void *extrabuf, int extralen, bool flagged, unsigned short id)
{
    if (PortHandle == -1) {
        return 0;
    }
    SerialHeaderType *header = (SerialHeaderType *)SendBuf;
    header->MagicNumber = 0xdabd;
    header->Length = (unsigned short)buflen;
    header->MagicNumber2 = 0xdeaf;
    unsigned long sendlen = sizeof(SerialHeaderType);
    memcpy(SendBuf + sendlen, buf, buflen);
    sendlen += buflen;
    int *ibuf = (int *)(SendBuf + sendlen);
    *ibuf = Compute_CRC(buf, buflen);
    sendlen += sizeof(int);
    *(SendBuf + sendlen) = '\r';
    sendlen += 1;
    SerialPort->Write_To_Serial_Port((unsigned char *)SendBuf, sendlen);
    return 1;
}
