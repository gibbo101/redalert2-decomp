// bool VoxClass::Read_INI(CCINIClass &ini) (0x007161E0): the volume, type
// (QUEUE 1, STANDARD 0, INTERRUPT 2, QUEUED_INTERRUPT 3), priority (LOW 0,
// NORMAL 1, IMPORTANT 2, CRITICAL 3) and the Russian and Allied file names of
// the VoxClass's EVA.ini section; false without the section.
#include "shared/vox_speech.hpp"
#include "shared/ccini_class.hpp"
#include "shared/crt_string.hpp"
// @ref ??_C@_03HKLE@LOW?$AA@=007cccac
// @ref ??_C@_04FCOP@Type?$AA@=007d9eec
// @ref ??_C@_06OPOL@Volume?$AA@=007f9b30
// @ref ??_C@_08MJHG@Priority?$AA@=007f7038
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_06HDDE@NORMAL?$AA@=007ccca4
// @ref ??_C@_05KMHL@QUEUE?$AA@=007f9d6c
// @ref ??_C@_06FLKA@Allied?$AA@=007f9d30
// @ref ??_C@_07EPIJ@Russian?$AA@=007f9d38
// @ref ??_C@_08GGOH@STANDARD?$AA@=007f9d60
// @ref ??_C@_08NGAO@CRITICAL?$AA@=007ccc90
// @ref ??_C@_09DNFO@INTERRUPT?$AA@=007ccbf0
// @ref ??_C@_09MHOE@IMPORTANT?$AA@=007f9d40
// @ref ??_C@_0BB@CCNI@QUEUED_INTERRUPT?$AA@=007f9d4c

bool VoxClass::Read_INI(CCINIClass &ini)
{
    char buffer[500];
    Volume = 1.0f;
    if (ini.Is_Present(Name)) {
        Volume = (float)ini.Get_Double(Name, "Volume", Volume);
        ini.Get_String(Name, "Type", "", buffer, sizeof(buffer));
        if (strlen(buffer) != 0) {
            if (_stricmp(buffer, "QUEUE") == 0) {
                Type = 1;
            } else if (_stricmp(buffer, "STANDARD") == 0) {
                Type = 0;
            } else if (_stricmp(buffer, "INTERRUPT") == 0) {
                Type = 2;
            } else if (_stricmp(buffer, "QUEUED_INTERRUPT") == 0) {
                Type = 3;
            }
        }
        ini.Get_String(Name, "Priority", "", buffer, sizeof(buffer));
        if (strlen(buffer) != 0) {
            if (_stricmp(buffer, "LOW") == 0) {
                Priority = 0;
            } else if (_stricmp(buffer, "NORMAL") == 0) {
                Priority = 1;
            } else if (_stricmp(buffer, "IMPORTANT") == 0) {
                Priority = 2;
            } else if (_stricmp(buffer, "CRITICAL") == 0) {
                Priority = 3;
            }
        }
        ini.Get_String(Name, "Russian", "", buffer, sizeof(buffer));
        strncpy(Russian, buffer, sizeof(Russian));
        Russian[sizeof(Russian) - 1] = '\0';
        ini.Get_String(Name, "Allied", "", buffer, sizeof(buffer));
        strncpy(Allied, buffer, sizeof(Allied));
        Allied[sizeof(Allied) - 1] = '\0';
        return true;
    }
    return false;
}
