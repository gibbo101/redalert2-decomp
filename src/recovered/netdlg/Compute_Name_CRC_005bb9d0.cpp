// unsigned long __fastcall Compute_Name_CRC(char const *name) (0x005BB9D0)
// TibSun netdlg.cpp shape: the CRC of the upper-cased name.
#include "shared/netdlg.hpp"
#include "shared/crt_string.hpp"
#include "shared/winsock_interface.hpp"

unsigned long __fastcall Compute_Name_CRC(char const *name)
{
    char buf[80];
    unsigned long crc = 0;
    int i;

    strcpy(buf, name);
    _strupr(buf);

    for (i = 0; (unsigned)i < strlen(buf); i++) {
        Add_CRC(&crc, (unsigned long)buf[i]);
    }

    return crc;
}
