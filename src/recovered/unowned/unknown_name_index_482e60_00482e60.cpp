#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/ccini_class.hpp"
extern "C" int __cdecl _stricmp(char const *left,char const *right);
// @ref __stricmp=00781f20
extern DynamicVectorClass<char const *> unknown_names_a71050;
extern char const none_name_007cdecc[];
// @ref ?unknown_names_a71050@@3V?$DynamicVectorClass@PBD@@A=00a71050
// @ref ?none_name_007cdecc@@3QBDB=007cdecc
int __fastcall unknown_name_index_482e60(char const *name)
{
    if (name && _stricmp(none_name_007cdecc,name)!=0) {
        for (int index=0;index<unknown_names_a71050.Count();++index)
            if (_stricmp(name,unknown_names_a71050[index])==0) return index;
    }
    return -1;
}
