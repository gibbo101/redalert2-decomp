// unsigned long __fastcall Compute_Name_CRC(wchar_t const *name) (0x005BBA50)
// The wide-character Compute_Name_CRC: the CRC of the upper-cased name.
#include "shared/netdlg.hpp"
#include "shared/winsock_interface.hpp"

unsigned long __fastcall Compute_Name_CRC(wchar_t const *name)
{
    wchar_t buf[80];
    unsigned long crc = 0;
    int i;

    wcscpy(buf, name);
    _wcsupr(buf);

    for (i = 0; (unsigned)i < wcslen(buf); i++) {
        Add_CRC(&crc, (unsigned long)buf[i]);
    }

    return crc;
}
