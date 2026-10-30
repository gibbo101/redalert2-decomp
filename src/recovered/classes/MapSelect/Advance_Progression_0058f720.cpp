#include "shared/map_select.hpp"
#include "shared/id_source.hpp"
#include "shared/house_type.hpp"
#include "shared/side.hpp"
extern char const unknown_mapselect_invalid_side_7e1c44[];
// @ref ?unknown_mapselect_invalid_side_7e1c44@@=007e1c44
extern char const unknown_mapselect_side_7e1c30[];
// @ref ?unknown_mapselect_side_7e1c30@@=007e1c30
extern char const unknown_mapselect_invalid_choices_7e1c04[];
// @ref ?unknown_mapselect_invalid_choices_7e1c04@@=007e1c04
extern char const unknown_mapselect_invalid_stage_7e1be8[];
// @ref ?unknown_mapselect_invalid_stage_7e1be8@@=007e1be8
extern char const unknown_mapselect_empty_83c55c[];
// @ref ?unknown_mapselect_empty_83c55c@@=0083c55c
// @ref ?Set_Scenario_Name_0065e730@UnknownIDSource@@=0065e730
bool MapSelect::Advance_Progression_0058f720(UnknownIDSource *scenario,Wstring const &name)
{
    if(!scenario || name==(char const *)0)return false;
    SideClass *side=Sides[HouseTypes[scenario->unknown_11fc]->Side];
    if(!side) {
        Debug_Printf(unknown_mapselect_invalid_side_7e1c44);
        return false;
    }
    Debug_Printf(unknown_mapselect_side_7e1c30,(char const *)side->ID);
    bool failed;
    {
        Wstring sideName((char const *)side->ID);
        failed=!Choices.Load(sideName);
    }
    if(failed) {
        Choices.Clear();
        Debug_Printf(unknown_mapselect_invalid_choices_7e1c04);
        return false;
    }
    MapStage *stage=Choices.Get_Stage(scenario->unknown_2304);
    if(!stage) {
        Choices.Clear();
        Debug_Printf(unknown_mapselect_invalid_stage_7e1be8);
        return false;
    }
    scenario->Set_Scenario_Name_0065e730(unknown_mapselect_empty_83c55c);
    for(int index=0;index<stage->Selections.Count();++index) {
        MapSelection *selection=stage->Selections[index];
        if(selection) {
            MapStage *next=Choices.Find_Stage(selection->Name);
            Wstring candidate(next->Scenario);
            candidate.To_Lower();
            Wstring requested(name);
            requested.To_Lower();
            if(next && candidate==requested) {
                scenario->Set_Scenario_Name_0065e730(next->Scenario.Peek_Buffer());
                scenario->unknown_2304=(unsigned short)Choices.Stage_Index(next);
                break;
            }
        }
    }
    Choices.Clear();
    return strlen(scenario->FileName)>0;
}
