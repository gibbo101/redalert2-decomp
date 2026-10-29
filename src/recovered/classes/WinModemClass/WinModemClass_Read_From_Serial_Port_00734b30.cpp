// int WinModemClass::Read_From_Serial_Port(unsigned char *dest_ptr, int buffer_len) (0x00734B30)
// Copies at most buffer_len received bytes out of the circular buffer, echoing
// every byte but carriage returns; returns the count copied (0 when nothing arrived).
#include "shared/win_modem.hpp"
// @ref ?Read_Serial_Chars@WinModemClass@@QAE_NXZ=00734980

int WinModemClass::Read_From_Serial_Port(unsigned char *dest_ptr, int buffer_len)
{
    int bytes_to_copy = 0;
    if (Read_Serial_Chars()) {
        bytes_to_copy = SerialBufferWritePtr - SerialBufferReadPtr;
        if (bytes_to_copy < 0) {
            bytes_to_copy += SIZE_OF_WINDOWS_SERIAL_BUFFER;
        }
        if (bytes_to_copy > buffer_len) {
            bytes_to_copy = buffer_len;
        }
        for (int index = 0; index < bytes_to_copy; index++) {
            if (EchoFunction && SerialBuffer[SerialBufferReadPtr] != '\r') {
                EchoFunction(SerialBuffer[SerialBufferReadPtr]);
            }
            *dest_ptr++ = SerialBuffer[SerialBufferReadPtr];
            SerialBufferReadPtr = (SerialBufferReadPtr + 1) & (SIZE_OF_WINDOWS_SERIAL_BUFFER - 1);
        }
    }
    return bytes_to_copy;
}
