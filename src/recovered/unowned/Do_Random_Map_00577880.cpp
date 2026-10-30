#include "shared/unknown_map_generator.hpp"
#include "shared/map_preview.hpp"
#include "shared/options_dialog.hpp"
#include "shared/wdt_territory.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/raw_file_class.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/id_source.hpp"
class Surface;
int __fastcall Write_PCX_File(FileClass &,Surface &,PaletteClass *);
void __fastcall unknown_517370(bool);
char *Random_Map_CRC_005c8420();
void __fastcall Clean_Up_RMCache_005775b0();
extern bool (*rmg_callback_7e09c4)();
extern char const rmg_preview_filename_7e1540[];
extern char const rmg_cache_prefix_7e15f0[];
extern char const rmg_cache_suffix_7e15e8[];
extern char const rmg_cache_directory_7e15d4[];
extern char const rmg_description_7e15dc[];
extern "C" {
__declspec(dllimport) BOOL __stdcall CopyFileA(char const *,char const *,BOOL);
void *__cdecl memset(void *,int,unsigned);
void *__cdecl memcpy(void *,void const *,unsigned);
char *__cdecl strncpy(char *,char const *,unsigned);
char *__cdecl strncat(char *,char const *,unsigned);
}
// @ref ?rmg_callback_7e09c4@@=007e09c4
// @ref ?rmg_preview_filename_7e1540@@=007e1540
// @ref ?rmg_cache_prefix_7e15f0@@=007e15f0
// @ref ?rmg_cache_suffix_7e15e8@@=007e15e8
// @ref ?rmg_cache_directory_7e15d4@@=007e15d4
// @ref ?rmg_description_7e15dc@@=007e15dc
// @ref ?Random_Map_CRC_005c8420@@YAPADXZ=005c8420
// @ref ?Write_PCX_File@@YIHAAVFileClass@@AAVSurface@@PAVPaletteClass@@@Z=007698c0
// @ref ?unknown_005c7ef0@UnknownPreview_0061D430@@=005c7ef0
// @ref ?Load_0061E170@UnknownPreview_0061D430@@QAE_NPBD@Z=0061e170
// @ref ?Clean_Up_RMCache_005775b0@@=005775b0
// ECX dialog/EDX callback, no stack arguments, plain RET. Name from reference operation; callback intent qualified.
void __fastcall Do_Random_Map_00577880(HWND dialog,bool (*callback)())
{
    rc_ptr<WDTTerritory> territory;
    if(unknown_game_mode_a3d298==4 && unknown_a3d2a4==2)territory=Unknown_Territory_00769690(unknown_session_a3d2a0);
    if(territory.Get()!=0)unknown_map_generator_a6fd68.SeedOptions.NumPlayers=4;
    char *digest=Random_Map_CRC_005c8420();
    char name[128];
    memset(name,0,sizeof(name));
    strncpy(name,rmg_cache_prefix_7e15f0,sizeof(name));
    strncat(name,digest,sizeof(name));
    delete digest;
    strncat(name,rmg_cache_suffix_7e15e8,sizeof(name));
    CCFileClass cached(name);
    if(cached.Is_Available()) {
        if(unknown_preview_a6fee4==0)unknown_preview_a6fee4=new UnknownPreview_0061D430;
        if(unknown_preview_a6fee4->Load_0061E170(name)) {
            RawFileClass file(rmg_preview_filename_7e1540);
            Write_PCX_File(file,*static_cast<Surface *>(unknown_preview_a6fee4->unknown_00),&unknown_palette_837e10);
            delete unknown_preview_a6fee4;
            unknown_preview_a6fee4=0;
            return;
        }
        delete unknown_preview_a6fee4;
        unknown_preview_a6fee4=0;
    }
    rmg_callback_7e09c4=callback;
    unknown_map_generator_a6fd68.SeedOptions.unknown_14=(int)callback;
    if(unknown_map_generator_a6fd68.SeedOptions.Seed==-1)
        unknown_map_generator_a6fd68.SeedOptions.Seed=unknown_random_839218(0,65535);
    unknown_map_generator_a6fd68.Unknown_0057A0D0(1,(int)dialog);
    unknown_preview_a6fee4->Unknown_0061D660();
    if(unknown_game_mode_a3d298==4 && unknown_a3d2a4==2)unknown_preview_a6fee4->unknown_005c7ef0();
    if(unknown_map_generator_a6fd68.unknown_178!=0)delete reinterpret_cast<MapSeedClass *>(unknown_map_generator_a6fd68.unknown_178);
    unknown_map_generator_a6fd68.unknown_178=(int)new MapSeedClass;
    memcpy((void*)unknown_map_generator_a6fd68.unknown_178,&unknown_map_generator_a6fd68.SeedOptions,sizeof(MapSeedClass));
    unknown_id_source_a3d290->Set_Scenario_Name_0065e730(rmg_description_7e15dc);
    unknown_517370(false);
    if(unknown_preview_a6fee4!=0) {
        if(unknown_preview_a6fee4->unknown_00!=0) {
            RawFileClass file(rmg_preview_filename_7e1540);
            Write_PCX_File(file,*static_cast<Surface *>(unknown_preview_a6fee4->unknown_00),&unknown_palette_837e10);
            WIN32_FIND_DATA find;
            if(FindFirstFileA(rmg_cache_directory_7e15d4,&find)==(HANDLE)-1)CreateDirectoryA(rmg_cache_directory_7e15d4,0);
            CopyFileA(rmg_preview_filename_7e1540,name,0);
            Clean_Up_RMCache_005775b0();
        }
        delete unknown_preview_a6fee4;
        unknown_preview_a6fee4=0;
    }
    if(unknown_map_generator_a6fd68.unknown_178!=0) {
        delete reinterpret_cast<MapSeedClass *>(unknown_map_generator_a6fd68.unknown_178);
        unknown_map_generator_a6fd68.unknown_178=0;
    }
}
