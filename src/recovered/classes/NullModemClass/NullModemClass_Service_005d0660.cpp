// int NullModemClass::Service() (0x005D0660, slot 1)
// Reads what the port has received into RXBuf, hands one complete frame with
// a good CRC to the connection, drops bytes up to the next start code, and
// services the connection's queues.
#include "shared/null_modem.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
// @ref ?SerialPort@@3PAVWinModemClass@@A=00b25bb0
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Read_From_Serial_Port@WinModemClass@@QAEHPAEH@Z=00734b30
// @ref ?Compute_CRC@NullModemConnClass@@SIHPADH@Z=005cdc80
// @ref _memmove=00783290
// @ref ??_C@_0CL@BLHK@Serial?5packet?5length?5too?5long?5by@=007e7a50
// @ref ??_C@_0CA@CLL@Serial?5packet?5failed?5CRC?5check?6?$AA@=007e7a30

int NullModemClass::Service()
{
    int pos;
    int i;
    unsigned short length;
    SerialHeaderType *header;
    SerialCRCType *crc;

    if (NumConnections == 0) {
        return 0;
    }

    RXCount += SerialPort->Read_From_Serial_Port((unsigned char *)(RXBuf + RXCount), RXSize - RXCount);

    if (RXCount < PACKET_SERIAL_OVERHEAD_SIZE + 1) {
        return Connection->Service();
    }

    pos = -1;
    for (i = 0; i <= RXCount - 2; i++) {
        if (*((unsigned short *)(RXBuf + i)) == 0xDABD) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        memmove(RXBuf, RXBuf + i, sizeof(short) - 1);
        RXCount = sizeof(short) - 1;
        return Connection->Service();
    }

    if ((RXCount - pos) < sizeof(SerialHeaderType)) {
        memmove(RXBuf, RXBuf + pos, RXCount - pos);
        RXCount -= pos;
        return Connection->Service();
    }

    header = (SerialHeaderType *)(RXBuf + pos);
    if (header->MagicNumber2 != 0xDEAF) {
        pos += sizeof(short);
        memmove(RXBuf, RXBuf + pos, RXCount - pos);
        RXCount -= pos;
        return Connection->Service();
    }

    length = header->Length;
    if (length > MaxLen) {
        Debug_Printf("Serial packet length too long by %d bytes\n", length - MaxLen);
        pos += sizeof(short);
        memmove(RXBuf, RXBuf + pos, RXCount - pos);
        RXCount -= pos;
        return Connection->Service();
    }

    if ((pos + length + PACKET_SERIAL_OVERHEAD_SIZE) > RXCount) {
        if (pos) {
            memmove(RXBuf, RXBuf + pos, RXCount - pos);
            RXCount -= pos;
        }
        return Connection->Service();
    }

    crc = (SerialCRCType *)(RXBuf + pos + sizeof(SerialHeaderType) + length);
    if (NullModemConnClass::Compute_CRC(RXBuf + pos + sizeof(SerialHeaderType), length) != crc->SerialCRC) {
        CRCErrors++;
        Debug_Printf("Serial packet failed CRC check\n");
        pos += sizeof(short);
        memmove(RXBuf, RXBuf + pos, RXCount - pos);
        RXCount -= pos;
        return Connection->Service();
    }

    if (!Connection->Receive_Packet(RXBuf + pos + sizeof(SerialHeaderType), length)) {
        ReceiveOverflows++;
    }

    pos += (PACKET_SERIAL_OVERHEAD_SIZE + length);
    memmove(RXBuf, RXBuf + pos, RXCount - pos);
    RXCount -= pos;
    return Connection->Service();
}
