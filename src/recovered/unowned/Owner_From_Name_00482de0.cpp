#include "shared/house_type.hpp"
// @ref ?Find_Index@HouseTypeClass@@SIHPBD@Z=004f94d0
int __fastcall Owner_From_Name(char const *name)
{
    int result=0;
    int index=HouseTypeClass::Find_Index(name);
    if (index!=-1) result=(int)(1U << index);
    return result;
}
