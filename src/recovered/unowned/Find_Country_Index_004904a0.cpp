#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/house_type.hpp"
extern "C" int __cdecl _stricmp(char const *, char const *);
// @ref ??_C@_08PECD@?$DMrandom?$DO?$AA@=007d1f18
int __fastcall Find_Country_Index_004904A0(char const *name)
{
    if (_stricmp(name, "<random>") == 0) return -2;
    if (name) {
        for (int index = 0; index < HouseTypes.Count(); ++index) {
            HouseTypeClass *country = HouseTypes[index];
            if (_stricmp(country->Name, name) == 0 || _stricmp(country->ID, name) == 0)
                return index;
        }
    }
    return -1;
}