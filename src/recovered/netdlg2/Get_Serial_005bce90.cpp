// bool __fastcall Get_Serial_005bce90(char *serial) (0x005BCE90)
#include "shared/lobby.hpp"
#include "shared/crt_stdio.hpp"
#include "shared/crt_memory.hpp"
// @ref ??_C@_01LHO@r?$AA@=007e6acc
// @ref ??_C@_06CFKC@Serial?$AA@=007e6ad0
// @ref ??_C@_0BO@MFMF@SOFTWARE?2Westwood?2Red?5Alert?52?$AA@=007e6ad8
// @ref ??_C@_0M@LBCF@woldata?4key?$AA@=007e6ac0
// @ref _fgetc=00784a0b

bool __fastcall Get_Serial_005bce90(char *serial)
{
    HKEY key;
    DWORD size;
    DWORD type;
    char buffer[128];

    memset(buffer, '0', 22);
    buffer[22] = 0;
    strcpy(serial, buffer);
    memset(buffer, 0, sizeof(buffer));
    char const *path = "SOFTWARE\\Westwood\\Red Alert 2";
    if (path != 0 && strlen(path) != 0) {
        char name[256];
        strcpy(name, path);
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, name, 0, KEY_READ, &key) == 0) {
            size = sizeof(buffer);
            RegQueryValueExA(key, "Serial", 0, &type, (BYTE *)buffer, &size);
            RegCloseKey(key);
        }
    }
    buffer[22] = 0;
    strcpy(serial, buffer);
    int i = 0;
    _iobuf *file = fopen("woldata.key", "r");
    if (file == 0) {
        return false;
    }
    int c;
    while ((c = fgetc(file)) != -1) {
        buffer[i] = (((buffer[i] - '0') % 10) - c + 1000) % 10 + '0';
        i++;
        if (i == (int)strlen(buffer)) {
            i = 0;
        }
    }
    fclose(file);
    strcpy(serial, buffer);
    return true;
}
