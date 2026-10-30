#include "shared/map_select.hpp"
#include "shared/id_source.hpp"
#include "shared/house_type.hpp"
#include "shared/side.hpp"
#include "shared/dsurface.hpp"
extern char const unknown_mapselect_invalid_scenario_7e1cb4[];
// @ref ?unknown_mapselect_invalid_scenario_7e1cb4@@=007e1cb4
extern char const unknown_mapselect_invalid_side_7e1c44[];
// @ref ?unknown_mapselect_invalid_side_7e1c44@@=007e1c44
extern char const unknown_mapselect_side_7e1c30[];
// @ref ?unknown_mapselect_side_7e1c30@@=007e1c30
extern char const unknown_mapselect_invalid_choices_7e1c04[];
// @ref ?unknown_mapselect_invalid_choices_7e1c04@@=007e1c04
extern char const unknown_mapselect_invalid_stage_7e1be8[];
// @ref ?unknown_mapselect_invalid_stage_7e1be8@@=007e1be8
extern char const unknown_mapselect_invalid_font_7e1c90[];
// @ref ?unknown_mapselect_invalid_font_7e1c90@@=007e1c90
// @ref ?HouseTypes@@=00a35d08
// @ref ?Sides@@=008661b0
// @ref ?Load@MapSelectData@@=005b0030
// @ref ?Find_Stage_04@MapSelectData@@=005b08a0
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0MSFont@@=005b3f40
// @ref ?unknown_surface_839954@@=00839954
// @ref ??0WideString@@QAE@ABV0@@Z=0076fa10
// @ref ??1WideString@@=0076fa50
// @ref ?unknown_wrap_text_5ae9a0@@=005ae9a0
// @ref ?Get_Stage@MapSelectData@@=005b0950
// @ref ??4Wstring@@QAEAAV0@PBD@Z=0076dbc0
// @ref ?Deinit_0058fc60@MapSelect@@=0058fc60
bool MapSelect::Init_0058fa20(UnknownIDSource *scenario)
{
    AnimDrawer=0;
    OverlayDrawer=0;
    Font=0;
    if(!scenario) {
        Debug_Printf(unknown_mapselect_invalid_scenario_7e1cb4);
        return false;
    }
    SideClass *side=Sides[HouseTypes[scenario->unknown_11fc]->Side];
    if(!side) {
        Debug_Printf(unknown_mapselect_invalid_side_7e1c44);
        return false;
    }
    Debug_Printf(unknown_mapselect_side_7e1c30,(char const *)side->ID);
    if(!Choices.Load((char const *)side->ID)) {
        Choices.Clear();
        Debug_Printf(unknown_mapselect_invalid_choices_7e1c04);
        return false;
    }
    MapStage *stage=Choices.Find_Stage_04(scenario->FileName);
    if(!stage) {
        Debug_Printf(unknown_mapselect_invalid_stage_7e1be8);
        Deinit_0058fc60();
        return false;
    }
    Font=new MSFont(true);
    if(!Font) {
        Debug_Printf(unknown_mapselect_invalid_font_7e1c90);
        Deinit_0058fc60();
        return false;
    }
    XOffset=(unknown_surface_839954->Get_Width()-640)/2;
    YOffset=(unknown_surface_839954->Get_Height()-400)/2;
    Rect const *textBounds=&Choices.TextRect;
    TextRect=*textBounds;
    TextRect.X+=XOffset;
    TextRect.Y+=YOffset;
    int index=0;
    do {
        WideString description(stage->Description);
        unknown_wrap_text_5ae9a0(description,Font,TextRect.Width);
        stage=Choices.Get_Stage(++index);
    } while(stage);
    VoiceName=(char const *)0;
    VoiceTimer=0;
    VoiceHandle=-1;
    return true;
}
