#include "shared/map_select.hpp"
#include "shared/id_source.hpp"
#include "shared/theme.hpp"
extern char unknown_map_select_a6ebd0;
// @ref ?unknown_map_select_a6ebd0@@=00a6ebd0
extern char const unknown_map_select_stage_7e1c78[];
// @ref ?unknown_map_select_stage_7e1c78@@=007e1c78
extern char const unknown_map_select_theme_7e1c70[];
// @ref ?unknown_map_select_theme_7e1c70@@=007e1c70
extern char const unknown_map_select_selected_7e1c60[];
// @ref ?unknown_map_select_selected_7e1c60@@=007e1c60
// @ref ?Set_Scenario_Name_0065e730@UnknownIDSource@@=0065e730
bool MapSelect::Presentation_0058f900(UnknownIDSource *scenario)
{
    if(!Init_0058fa20(scenario))return false;
    unknown_map_select_a6ebd0=0;
    MapStage *stage;
    {
        Wstring name(scenario->FileName);
        stage=Choices.Find_Stage_04(name);
    }
    Debug_Printf(unknown_map_select_stage_7e1c78,stage->Name.Buffer);
    if(stage->MapVQ!=(char const *)0) {
        Theme.Play_Song(Theme.From_Name(unknown_map_select_theme_7e1c70));
        char const *selected=stage->Selections[0]->Name.Peek_Buffer();
        if(selected) {
            Debug_Printf(unknown_map_select_selected_7e1c60,selected);
            {
                Wstring name(selected);
                stage=Choices.Find_Stage(name);
            }
            Wstring scenarioName(stage->Scenario);
            if(scenarioName.Length()!=0) {
                scenario->Set_Scenario_Name_0065e730(scenarioName.Get());
                scenario->unknown_2304=(unsigned short)Choices.Stage_Index(stage);
            }
        }
    }
    Deinit_0058fc60();
    return true;
}
