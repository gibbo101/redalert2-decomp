// void WinModemClass::Dial_Modem(char const *dial_number) (0x00734F50; slot 6)
// Sends "ATDT<number>\r" (ATDP for pulse dialling) and waits for the write.
#include "shared/win_modem.hpp"
#include "shared/crt_string.hpp"
#include "shared/crt_tokens.hpp"
#include "shared/debug_printf.hpp"
// @ref ??_C@_01FEHD@?$AN?$AA@=007e7dc8
// @ref ??_C@_01KGOM@T?$AA@=007f326c
// @ref ??_C@_01MLA@P?$AA@=007f3268
// @ref ??_C@_03ECIG@ATD?$AA@=007fcdac
// @ref ??_C@_0BD@JAIA@Dial?5type?5is?5tone?6?$AA@=007fcd98
// @ref ??_C@_0BD@LCDB@Send?5to?5modem?3?5?$CFs?6?$AA@=007fcd3c
// @ref ??_C@_0BE@NNPM@Dial?5type?5is?5pulse?6?$AA@=007fcd84
// @ref ??_C@_0BG@BLBP@Creating?5dial?5string?6?$AA@=007fcdb0
// @ref ??_C@_0BH@NKJG@Appending?5dial?5string?6?$AA@=007fcd6c
// @ref ??_C@_0BL@OPMN@Appending?5carriage?5return?6?$AA@=007fcd50
// @ref ??_C@_0CN@JKPG@Writing?5to?5port?5handle?5failed?5wi@=007fcd0c
// @ref ?Wait_For_Serial_Write@WinModemClass@@QAEXXZ=00734bc0

void WinModemClass::Dial_Modem(char const *dial_number)
{
    char dial_string[80];
    Debug_Printf("Creating dial string\n");
    strcpy(dial_string, "ATD");
    if (DialingMethod == 0) {
        strcat(dial_string, "T");
        Debug_Printf("Dial type is tone\n");
    } else {
        Debug_Printf("Dial type is pulse\n");
        strcat(dial_string, "P");
    }
    Debug_Printf("Appending dial string\n");
    strcat(dial_string, dial_number);
    Debug_Printf("Appending carriage return\n");
    strcat(dial_string, "\r");
    Debug_Printf("Send to modem: %s\n", dial_string);
    Write_To_Serial_Port((unsigned char *)dial_string, strlen(dial_string));
    Wait_For_Serial_Write();
}
