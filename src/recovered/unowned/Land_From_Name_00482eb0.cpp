#include "shared/ccini_class.hpp"
extern "C" int __cdecl _stricmp(char const *left,char const *right);
// @ref __stricmp=00781f20
extern char const *LandNames[12];
// @ref ?LandNames@@3PAPBDA=007d3878
extern char const none_name_007cdecc[];
// @ref ?none_name_007cdecc@@3QBDB=007cdecc
LandType __fastcall Land_From_Name(char const *name)
{
    // Original compares the sentinel before checking for a null input.
    if (_stricmp(none_name_007cdecc,name)!=0 && name) {
        for (int index=0;index<12;++index) {
            if (_stricmp(LandNames[index],name)==0) return (LandType)index;
        }
    }
    return (LandType)-1;
}
