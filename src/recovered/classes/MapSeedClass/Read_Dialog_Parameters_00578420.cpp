#include "shared/map_seed.hpp"
#include "shared/map_preview.hpp"
extern bool unknown_map_dialog_modified_a70068;
// @ref ?unknown_map_dialog_modified_a70068@@3_NA=00a70068
// @ref ?unknown_preview_a6fee4@@3PAVUnknownPreview_0061D430@@A=00a6fee4
// @ref ??1UnknownPreview_0061D430@@QAE@XZ=0061d440
// @ref ?Randomize_Parameters_005789f0@MapSeedClass@@=005789f0
// @ref ?Clamp_Parameters_00578d80@MapSeedClass@@=00578d80
void MapSeedClass::Read_Dialog_Parameters_00578420(HWND dialog)
{
    {
        int previous=MapType;
        HWND control=GetDlgItem(dialog,0x405);
        MapType=(int)SendMessageA(control,0x150,SendMessageA(control,0x147,0,0),0);
        if(previous!=MapType) unknown_map_dialog_modified_a70068=true;
    }
    {
        int previous=Theater;
        HWND control=GetDlgItem(dialog,0x407);
        Theater=(int)SendMessageA(control,0x150,SendMessageA(control,0x147,0,0),0);
        if(previous!=Theater) unknown_map_dialog_modified_a70068=true;
    }
    {
        int previous=Resources;
        HWND control=GetDlgItem(dialog,0x408);
        Resources=(int)SendMessageA(control,0x150,SendMessageA(control,0x147,0,0),0);
        if(previous!=Resources) unknown_map_dialog_modified_a70068=true;
    }
    {
        int previous=Time;
        HWND control=GetDlgItem(dialog,0x3ea);
        Time=(int)SendMessageA(control,0x150,SendMessageA(control,0x147,0,0),0);
        if(previous!=Time) unknown_map_dialog_modified_a70068=true;
    }
    {
        int previous=Width;
        HWND control=GetDlgItem(dialog,0x406);
        Width=(int)SendMessageA(control,0x150,SendMessageA(control,0x147,0,0),0);
        Height=Width;
        if(previous!=Width) unknown_map_dialog_modified_a70068=true;
    }
    int previous=NumPlayers;
    HWND control=GetDlgItem(dialog,0x3eb);
    NumPlayers=(int)SendMessageA(control,0x400,0,0);
    if(previous!=NumPlayers) unknown_map_dialog_modified_a70068=true;
    if(unknown_map_dialog_modified_a70068) {
        Randomize_Parameters_005789f0(MapType);
        delete unknown_preview_a6fee4;
        unknown_preview_a6fee4=0;
        unknown_map_dialog_modified_a70068=false;
    }
    Clamp_Parameters_00578d80();
}
