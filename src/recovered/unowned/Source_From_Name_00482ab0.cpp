#include "shared/ccini_class.hpp"
extern "C" int __cdecl _stricmp(char const *left,char const *right);
// @ref __stricmp=00781f20
extern char const *SourceNames[5];
// @ref ?SourceNames@@3PAPBDA=0079ab50
SourceType __fastcall Source_From_Name(char const *name)
{
    if (name) {
        for (int index=0;index<5;++index) {
            if (_stricmp(SourceNames[index],name)==0) return (SourceType)index;
        }
    }
    return (SourceType)-1;
}
