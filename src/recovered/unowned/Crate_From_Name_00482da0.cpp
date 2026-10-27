#include "shared/ccini_class.hpp"
extern "C" int __cdecl _stricmp(char const *left,char const *right);
// @ref __stricmp=00781f20
extern char const *CrateNames[19];
// @ref ?CrateNames@@3PAPBDA=0079de54
CrateType __fastcall Crate_From_Name(char const *name)
{
    if (name) {
        for (int index=0;index<19;++index) {
            if (_stricmp(name,CrateNames[index])==0) return (CrateType)index;
        }
    }
    return (CrateType)0;
}
