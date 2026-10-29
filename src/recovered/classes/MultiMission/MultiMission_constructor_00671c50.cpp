#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#include "shared/multi_mission.hpp"
#include "shared/crt_string.hpp"
#include "shared/string_table.hpp"
extern "C" unsigned short *__cdecl wcscpy(unsigned short *dest, unsigned short const *source);
extern "C" unsigned short *__cdecl wcsncpy(unsigned short *dest, unsigned short const *source, unsigned int count);

MultiMission::MultiMission(char const *filename, unsigned short const *description, char const *digest, bool official,
                           char const *modes, int unknown_180, int players)
{
    if (filename) {
        strncpy(unknown_58, filename, sizeof(unknown_58));
        unknown_58[sizeof(unknown_58) - 1] = '\0';
    } else {
        strcpy(unknown_58, "No File Name");
    }
    if (description) {
        wcsncpy(Description, description, 0x2C);
        Description[0x2B] = 0;
    } else {
        wcscpy(Description, StringTable::Load_String("MSG:NoDescription", 0, "D:\\Ra2\\Session.CPP", 0xb0a));
    }
    if (digest) {
        strncpy(unknown_15c, digest, sizeof(unknown_15c));
        unknown_15c[sizeof(unknown_15c) - 1] = '\0';
    } else {
        strcpy(unknown_15c, "No Digest");
    }
    unknown_17c = official;
    this->unknown_180 = unknown_180;
    unknown_184 = players;
    DiskIDs.Clear();
    DiskIDs.Add((DiskID)-2);
    if (modes) {
        Wstring list(modes);
        if (list.Length() > 0) {
            Wstring token;
            int position = list.Get_Token(0, ",", token);
            while (position != -1) {
                token.Trim_Leading(" ");
                token.Trim_Trailing(" ");
                GameModes.Add(token);
                position = list.Get_Token(position, ",", token);
            }
        }
    }
}
// @ref ??0?$VectorClass@W4DiskID@@@@QAE@IPBW4DiskID@@@Z=00674aa0
// @ref ??0?$VectorClass@VWstring@@@@QAE@IPBVWstring@@@Z=00674af0
// @ref ??_7?$TypeList@W4DiskID@@@@6B@=007a9684
// @ref ??_7?$DynamicVectorClass@VWstring@@@@6B@=007a9664
// @ref ??_C@_01FCOA@?5?$AA@=007e613c
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref ??_C@_0BC@IPHL@MSG?3NoDescription?$AA@=007f39c0
// @ref ??_E?$TypeList@W4DiskID@@@@UAEPAXI@Z=006739f0
// @ref ??8?$VectorClass@W4DiskID@@@@UBE_NABV0@@Z=00673a40
// @ref ?Resize@?$DynamicVectorClass@W4DiskID@@@@UAE_NHPBW4DiskID@@@Z=00673bc0
// @ref ?Clear@?$DynamicVectorClass@W4DiskID@@@@UAEXXZ=006737d0
// @ref ?ID@?$DynamicVectorClass@W4DiskID@@@@UAEHABW4DiskID@@@Z=00673c70
// @ref ?ID@?$DynamicVectorClass@W4DiskID@@@@UAEHPBW4DiskID@@@Z=00673800
// @ref ?Fetch@?$VectorClass@W4DiskID@@@@UBE?AW4DiskID@@H@Z=00673820
