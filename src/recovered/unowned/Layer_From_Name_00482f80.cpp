#include "shared/ccini_class.hpp"
extern "C" int __cdecl _stricmp(char const *left,char const *right);
// @ref __stricmp=00781f20
extern char const *LayerNames[5];
// @ref ?LayerNames@@3PAPBDA=007d38c8
LayerType __fastcall Layer_From_Name(char const *name)
{
    if (name) {
        for (int index=0;index<5;++index) {
            if (_stricmp(LayerNames[index],name)==0) return (LayerType)index;
        }
    }
    return (LayerType)-1;
}
