#include "shared/ccini_class.hpp"
extern "C" int __cdecl _stricmp(char const *left,char const *right);
// @ref __stricmp=00781f20
extern char const *SpeedNames[8];
// @ref ?SpeedNames@@3PAPBDA=007d38a8
SpeedType __fastcall Speed_From_Name(char const *name)
{
    if (name) {
        for (int index=0;index<8;++index) {
            if (_stricmp(SpeedNames[index],name)==0) return (SpeedType)index;
        }
    }
    return (SpeedType)-1;
}
