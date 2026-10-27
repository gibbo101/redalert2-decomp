#include "shared/map_seed.hpp"
// @ref ?Save_Dialog_0053b1b0@LoadOptionsClass@@=0053b1b0
bool MapSeedClass::Save_Or_Prompt_00578ed0(char const *filename)
{
    if(filename) return Save(filename,DescriptionBuffer);
    return Save_Dialog_0053b1b0(DescriptionBuffer)!=0 ? true : false;
}
