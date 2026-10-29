// int WinModemClass::Send_Command_To_Modem(char const *command, char terminator, char *buffer,
//     int buffer_len, int delay, int retries, int timeout) (0x00735110; slot 7)
// Sends command plus terminator up to retries times and reads the reply: 3 for "0",
// 2 for "OK" or a three digit code (copied to buffer), 1 for "ERROR", 0 on timeout.
#include "shared/win_modem.hpp"
#include "shared/crt_string.hpp"
#include "shared/cd_timer.hpp"
#include "shared/system_timer.hpp"
#include "shared/crt_tokens.hpp"
extern "C" char *__cdecl strstr(char const *string, char const *search);
extern "C" char *__cdecl strncpy(char *destination, char const *source, unsigned int count);
// @ref _strstr=007836b0
// @ref _strncpy=007823d0
// @ref ?Read_From_Serial_Port@WinModemClass@@QAEHPAEH@Z=00734b30
// @ref ?Wait_For_Serial_Write@WinModemClass@@QAEXXZ=00734bc0
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
// @ref ??_C@_01FEHD@?$AN?$AA@=007e7dc8
// @ref ??_C@_01PLJA@0?$AA@=007e1a60
// @ref ??_C@_02HAGF@OK?$AA@=007d5a40
// @ref ??_C@_05EFDD@ERROR?$AA@=007fcdc8

int WinModemClass::Send_Command_To_Modem(char const *command, char terminator, char *buffer, int buffer_len,
                                         int delay, int retries, int timeout)
{
    char term_string[2];
    char send_string[80];
    char flush_buffer[80];

    term_string[0] = terminator;
    term_string[1] = '\0';
    strcpy(send_string, command);
    strcat(send_string, term_string);

    Read_From_Serial_Port((unsigned char *)flush_buffer, 80);
    Sleep(100);
    Read_From_Serial_Port((unsigned char *)flush_buffer, 80);

    for (int times = 0; times < retries; times++) {
        CDTimerClass<SystemTimerClass> timer(delay);
        Write_To_Serial_Port((unsigned char *)send_string, strlen(send_string));
        Wait_For_Serial_Write();
        if (timer.Value() <= 0) {
            return 0;
        }
        int wait = timer.Value() < 1 ? 1 : timer.Value();
        char reply[80];
        memset(reply, 0, 80);
        Get_Modem_Result(wait, reply, 80, timeout);
        if (strcmp(reply, "0") == 0) {
            return 3;
        }
        if (strstr(reply, "OK")) {
            return 2;
        }
        if (strstr(reply, "ERROR")) {
            return 1;
        }
        if (strlen(reply) == 3 && reply[0] >= '0' && reply[0] <= '9' && reply[1] >= '0' && reply[1] <= '9'
            && reply[2] >= '0' && reply[2] <= '9') {
            strncpy(buffer, reply, buffer_len < 80 ? buffer_len : 80);
            return 2;
        }
        strncpy(buffer, reply, buffer_len < 80 ? buffer_len : 80);
        Sleep(100);
        Write_To_Serial_Port((unsigned char *)"\r", 1);
        Wait_For_Serial_Write();
        Sleep(100);
    }
    return 0;
}
