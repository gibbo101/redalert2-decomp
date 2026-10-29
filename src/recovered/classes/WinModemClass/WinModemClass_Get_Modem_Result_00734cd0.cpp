// int WinModemClass::Get_Modem_Result(int delay, char *buffer, int buffer_len, int timeout)
// (0x00734CD0; slot 5)
// Collects the modem reply into buffer until delay runs out or a line ends and the
// timeout passes, drops echoed "AT" lines and leading line breaks; returns the time
// left of delay, 0 when the application lost focus, or the abort function's result.
#include "shared/win_modem.hpp"
#include "shared/crt_string.hpp"
#include "shared/cd_timer.hpp"
#include "shared/system_timer.hpp"
#include "shared/unknown_globals.hpp"
extern "C" char *__cdecl strchr(char const *string, int character);
extern "C" char *__cdecl strrchr(char const *string, int character);
extern "C" char *__cdecl strstr(char const *string, char const *search);
// @ref _memmove=00783290
// @ref _strchr=00784130
// @ref _strrchr=00781ff0
// @ref _strstr=007836b0
// @ref ?Read_From_Serial_Port@WinModemClass@@QAEHPAEH@Z=00734b30
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
// @ref ?unknown_flag_a40d28@@3_NA=00a40d28
// @ref ??_C@_02BKOD@AT?$AA@=007e7ca8

int WinModemClass::Get_Modem_Result(int delay, char *buffer, int buffer_len, int timeout)
{
    CDTimerClass<SystemTimerClass> timer;
    CDTimerClass<SystemTimerClass> cr_timer;
    int pos = 0;
    char *cr_ptr;

    memset(buffer, 0, buffer_len);
    cr_timer = timeout;
    do {
        timer = delay;
        for (;;) {
            if (AbortFunction) {
                int abort = AbortFunction();
                if (abort) {
                    return abort;
                }
            }
            if (!unknown_flag_a40d28) {
                return 0;
            }
            int bytes = Read_From_Serial_Port((unsigned char *)buffer + pos, (buffer_len - pos < 0 ? 0 : buffer_len - pos));
            if (bytes) {
                pos += bytes;
                cr_timer = timeout;
            }
            if (!timer || pos >= buffer_len) {
                break;
            }
            if (strchr(buffer, '\r')) {
                if (timeout == -1 || !cr_timer) {
                    break;
                }
            }
        }

        buffer[buffer_len - 1] = '\0';
        cr_ptr = strstr(buffer, "AT");
        if (cr_ptr) {
            if (buffer[0] == 'A' && buffer[1] == 'T' && strchr(buffer, '\r')) {
                cr_ptr = strchr(buffer, '\r');
            }
        }
        if (!cr_ptr) {
            if (buffer[0] != '\r' && buffer[0] != '\n') {
                break;
            }
            cr_ptr = strchr(buffer, '\r');
            char *lf_ptr = strchr(buffer, '\n');
            if (!cr_ptr || (lf_ptr && lf_ptr < cr_ptr)) {
                cr_ptr = strchr(buffer, '\n');
            }
            if (!cr_ptr) {
                break;
            }
        }
        while (*cr_ptr == '\r' || *cr_ptr == '\n') {
            cr_ptr++;
        }
        if (cr_ptr != buffer) {
            int skip = cr_ptr - buffer;
            memmove(buffer, cr_ptr, buffer_len - skip);
            pos -= skip;
        }
    } while (cr_ptr);

    if (strrchr(buffer, '\r')) {
        *strrchr(buffer, '\r') = '\0';
    }
    return timer;
}
