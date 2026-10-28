// int NullModemConnClass::Send(char *buf, int buflen, void *extrabuf, int extralen, bool flagged, unsigned short id) -- 0x005CDBD0
// Slot 9: frames the packet for the serial line (magic 0xDABD, length,
// magic 0xDEAF, the data, a rotating checksum of the data and a carriage
// return) in SendBuf and writes it through the serial port object (pointer
// 0x00B25BB0, WinModemClass; Write 0x00734C70). Nothing is sent without an
// open port. The extra buffer and flags are unused here.
#include "shared/crt_memory.hpp"
// @ref ?SerialPort@@3PAVWinModemClass@@A=00b25bb0
// @ref ?Write@WinModemClass@@QAEXPAXH@Z=00734c70

class WinModemClass {
public:
    void Write(void *buffer, int length);       // 0x00734C70 (name hypothesis)
};
extern WinModemClass *SerialPort;

// The serial frame header (6 bytes).
struct SerialHeaderType {
    unsigned short MagicNumber;     // 0xDABD
    unsigned short Length;
    unsigned short MagicNumber2;    // 0xDEAF
};

// The rotating checksum of the data (expanded inline; no out-of-line copy).
static inline int Compute_CRC(char *buf, int buflen)
{
    unsigned int sum = 0;
    unsigned int hibit;
    for (int index = 0; index < buflen; index++) {
        if (sum & 0x80000000) {
            hibit = 1;
        } else {
            hibit = 0;
        }
        sum <<= 1;
        sum += hibit;
        sum += (unsigned char)buf[index];
    }
    return (int)sum;
}

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
    SerialPort->Write(SendBuf, sendlen);
    return 1;
}
