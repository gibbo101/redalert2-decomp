#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/ccini_class.hpp"
extern "C" int __cdecl _stricmp(char const *left,char const *right);
// @ref __stricmp=00781f20
#include "shared/anim_type.hpp"
// @ref ?Theaters@@3PAUTheaterTypeStruct@@A=0079ab68
TheaterType __fastcall Theater_From_Name(char const *name)
{
    for (int index=0;index<3;++index)
        if (_stricmp(name,Theaters[index].Name)==0) return (TheaterType)index;
    return (TheaterType)-1;
}
