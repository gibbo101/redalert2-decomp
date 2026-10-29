// int NullModemConnClass::Packet_Overhead_Size() (0x005CDCB0)
// The bytes a packet carries for the serial link only: the frame header and CRC
// (PACKET_SERIAL_OVERHEAD_SIZE) and the queue header (CommHeaderType).
#include "shared/null_modem.hpp"

int NullModemConnClass::Packet_Overhead_Size()
{
    return PACKET_SERIAL_OVERHEAD_SIZE + sizeof(CommHeaderType);
}
