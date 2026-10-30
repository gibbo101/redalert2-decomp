#include "shared/unknown_map_generator.hpp"
#include "shared/dialog_create.hpp"
#include "shared/map_preview.hpp"
#include "shared/raw_file_class.hpp"
#include "shared/unknown_globals.hpp"
class Surface;
int __fastcall Write_PCX_File(FileClass &file,Surface &picture,PaletteClass *palette);
void __fastcall unknown_dialog_5ff7c0(HWND window);
void __fastcall unknown_dialog_5ff6e0(HWND window);
void __fastcall unknown_517370(bool flag);
int __stdcall Map_Seed_Dialog_Proc_00577bd0(HWND,UINT,WPARAM,LPARAM);
bool Default_Map_Generation_Callback_00482100();
extern bool (*rmg_callback_7e09c4)();
extern char const rmg_preview_filename_7e1540[];
// @ref ?rmg_callback_7e09c4@@=007e09c4
// @ref ?rmg_preview_filename_7e1540@@=007e1540
// @ref ?Map_Seed_Dialog_Proc_00577bd0@@=00577bd0
// @ref ?Default_Map_Generation_Callback_00482100@@=00482100
// @ref ?Read_Settings_00579960@UnknownMapGenerator@@=00579960
// @ref ?unknown_map_generator_a6fd68@@=00a6fd68
// @ref ?unknown_preview_a6fee4@@=00a6fee4
// @ref ?Write_PCX_File@@YIHAAVFileClass@@AAVSurface@@PAVPaletteClass@@@Z=007698c0
// @ref ??0RawFileClass@@QAE@PBD@Z=00638b40
// @ref ??1RawFileClass@@UAE@XZ=00638ac0
// @ref ??1UnknownPreview_0061D430@@QAE@XZ=0061d440
// Free fastcall ECXcallback/EAXresult/RET0, independently observed. Callback bool intent follows AL0 at482100.
int __fastcall Do_Random_Map_Dialog_00577490(bool (*callback)())
{
    int result=0;
    unknown_map_generator_a6fd68.Read_Settings_00579960();
    HWND dialog=unknown_create_dialog_5ff610(0x105,Map_Seed_Dialog_Proc_00577bd0,0);
    if(dialog!=0) {
        rmg_callback_7e09c4=callback;
        unknown_map_generator_a6fd68.SeedOptions.unknown_14=(int)callback;
        SetWindowLongA(dialog,8,(LONG)&result);
        SendMessageA(dialog,0x4a9,0,1);
        unknown_dialog_5ff7c0(dialog);
        while(result==0) {
            if(unknown_6000d0()==true)break;
            if(callback!=0)callback();
            unknown_517370(false);
        }
        unknown_dialog_5ff6e0(dialog);
    }
    rmg_callback_7e09c4=Default_Map_Generation_Callback_00482100;
    unknown_map_generator_a6fd68.SeedOptions.unknown_14=0;
    if(unknown_preview_a6fee4!=0) {
        if(unknown_preview_a6fee4->unknown_00!=0) {
            RawFileClass file(rmg_preview_filename_7e1540);
            Write_PCX_File(file,*static_cast<Surface *>(unknown_preview_a6fee4->unknown_00),&unknown_palette_837e10);
        }
        delete unknown_preview_a6fee4;
        unknown_preview_a6fee4=0;
    }
    if(unknown_map_generator_a6fd68.unknown_178!=0) {
        delete reinterpret_cast<MapSeedClass *>(unknown_map_generator_a6fd68.unknown_178);
        unknown_map_generator_a6fd68.unknown_178=0;
    }
    return result;
}
