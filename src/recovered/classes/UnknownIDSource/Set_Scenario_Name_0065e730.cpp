#include "shared/id_source.hpp"
#include "shared/crt_string.hpp"
// @ref _strncpy=007823d0
void UnknownIDSource::Set_Scenario_Name_0065e730(char const *name)
{
    if(name) {
        strncpy(FileName,name,sizeof(FileName));
        FileName[sizeof(FileName)-1]=0;
    }
}
