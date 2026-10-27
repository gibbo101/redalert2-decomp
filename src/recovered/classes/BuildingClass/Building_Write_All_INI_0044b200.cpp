// PRIVATE prototype hypotheses: free fastcall wrapper, Building member writer with INI reference.
#include "shared/building.hpp"
#include "shared/ini_class.hpp"
extern "C" char const *unknown_structure_section_0079cb88;
// @ref _unknown_structure_section_0079cb88=0079cb88
// @ref ?Write_Structure_INI_0044b250@BuildingClass@@QAEXAAVINIClass@@@Z=0044b250
void __fastcall Building_Write_All_INI_0044b200(INIClass *ini)
{
    ini->Clear(unknown_structure_section_0079cb88, 0);
    for (int index = 0; index < unknown_BuildingClass_list_00a40af8.Count(); ++index) {
        BuildingClass *building = unknown_BuildingClass_list_00a40af8[index];
        if (!building->unknown_76 && !building->Type->LaserFence)
            building->Write_Structure_INI_0044b250(*ini);
    }
}
