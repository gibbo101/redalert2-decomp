// Complete original 0x57AE00..0x57BE4E, followed by one frozen NOP.
// Source intent follows target operations; int/low-byte full-init ABI is retained.
#include "shared/unknown_map_generator.hpp"
#include "shared/map_region.hpp"
#include "shared/map_random.hpp"
#include "shared/mouse_class.hpp"
#include "shared/id_source.hpp"
#include "shared/ccini_class.hpp"
#include "shared/session_state.hpp"
#include "shared/map_preview.hpp"
#include "shared/tactical.hpp"
#include "shared/unit.hpp"
#include "shared/infantry.hpp"
#include "shared/building.hpp"
#include "shared/terrain.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
#include "shared/terrain_type.hpp"
#include "shared/overlay_type.hpp"
#include "shared/building_type_class.hpp"
#include "shared/anim_type.hpp"
#include "shared/smudge_type.hpp"
#include "shared/isometric_tile.hpp"
#include "shared/isometric_tile_type.hpp"
#include "shared/rules.hpp"
#include "shared/cell.hpp"
#include "shared/progress_screen.hpp"
#include "shared/crt_memory.hpp"

extern void (__cdecl *unknown_map_generation_callback_7e09c4)();
extern int const unknown_width_min_7a5b6c[7], unknown_width_max_7a5b88[7];
extern int const unknown_height_min_7a5ba4[7], unknown_height_max_7a5bc0[7];
extern float const unknown_waterfall_probability_7a5b68;
// @ref ?unknown_waterfall_probability_7a5b68@@=007a5b68
extern DynamicVectorClass<MapRegionClass *> unknown_map_regions_a6fd28;
// Existing scenario waypoint-clear operation; canonical provider identity/ABI retained.
namespace seed_00663220 { void __fastcall FUN_00663220(int address); }
// @ref ?FUN_00663220@=00663220
void __stdcall Report_Generation_Progress_0057be50(int progress);
void __fastcall Delete_All_Objects_00519960();
void Clear_Tiberium_Spread_006e9670();
void Clear_Tiberium_Growth_006ea130();
void __fastcall Read_Tile_Control_00529870(int theater,bool reload);
void Clear_Tile_Use_Counts_0052b650();
void __fastcall Load_Isometric_Tiles_0052b2e0(bool first,bool second);
extern "C" unsigned int __cdecl wcslen(wchar_t const *text);
extern "C" wchar_t *__cdecl wcscpy(wchar_t *target,wchar_t const *text);
// @ref ?unknown_map_generation_callback_7e09c4@@=007e09c4
// @ref ?unknown_width_min_7a5b6c@@=007a5b6c
// @ref ?unknown_width_max_7a5b88@@=007a5b88
// @ref ?unknown_height_min_7a5ba4@@=007a5ba4
// @ref ?unknown_height_max_7a5bc0@@=007a5bc0
// @ref ?unknown_map_random_a705c0@@=00a705c0
// @ref ?unknown_map_regions_a6fd28@@=00a6fd28
// @ref ?Clear_Tiberium_Spread_006e9670@@=006e9670
// @ref ?Clear_Tiberium_Growth_006ea130@@=006ea130
// @ref ?Read_Tile_Control_00529870@@=00529870
// @ref ?Clear_Tile_Use_Counts_0052b650@@=0052b650
// @ref ?Load_Isometric_Tiles_0052b2e0@@=0052b2e0
// @ref ?unknown_slot28@RadarClass@@=00630300
// @ref ??0UnknownPreview_0061D430@@=0061d430
// @ref ??0Tactical@@=006a24b0
// @ref _wcslen=00783605
// @ref _wcscpy=00783689
// @ref ??0?$List@PAUINISection@INIClass@@@@QAE@XZ=00490ff0
// @ref ??0?$IndexClass@HPAUINISection@INIClass@@@@QAE@XZ=004910c0
// @ref ??_7?$List@PAUINISection@INIClass@@@@6B@=0079aaec
// @ref ??_7CCINIClass@@6B@=0079aae4
// @ref ??_7GenericList@@6B@=0079aaf4
// @ref ??_7GenericNode@@6B@=0079aafc
// @ref ??_GGenericNode@@UAEPAXI@Z=0040e1d0
// @ref ??_GGenericList@@UAEPAXI@Z=0040e220
// @ref ??_GCCINIClass@@UAEPAXI@Z=0040e2e0
// @ref ??_G?$List@PAUINISection@INIClass@@@@UAEPAXI@Z=0040e300

double __cdecl Map_Random_Fraction_00579770();
// Existing region teardown operation, whose accepted separate copy remains authoritative.
// @ref ?Clear_Map_Regions_0056da00@@=0056da00
void __fastcall Clear_Map_Regions_0056da00()
{
    unknown_map_region_next_index_a70a28=0;
    for (int index=(int)((unsigned)unknown_map_regions_a6fd28.Count()-1u);index>=0;--index) {
        delete unknown_map_regions_a6fd28[index];
    }
}

void UnknownMapGenerator::Init_Map_0057ae00(int fullInit)
{
    int index;
    int sizeIndex=SeedOptions.NumPlayers-2;
    float widthFraction=SeedOptions.Width*(1.0f/3.0f);
    float heightFraction=SeedOptions.Height*(1.0f/3.0f);
    Read_Settings_00579960();
    if(SeedOptions.MapType!=3 && SeedOptions.MapType!=4) {
        widthFraction=widthFraction<1.2 ? widthFraction : 1.2;
        heightFraction=heightFraction<1.2 ? heightFraction : 1.2;
    }
    unknown_180=(int)(unknown_width_min_7a5b6c[sizeIndex]*(1.0f-widthFraction)+unknown_width_max_7a5b88[sizeIndex]*widthFraction);
    unknown_184=(int)(unknown_height_min_7a5ba4[sizeIndex]*(1.0f-heightFraction)+unknown_height_max_7a5bc0[sizeIndex]*heightFraction);
    Rect size(0,0,unknown_180+4,unknown_184+12);
    Rect localSize(2,5,unknown_180,unknown_184);
    unknown_30c=4;
    CCINIClass ini;
    ini.Clear();
    unknown_30c=4;
    ini.Put_String("Map","Theater",Theaters[SeedOptions.Theater].Name);
    ini.Put_Rect("Map","Size",*(INIRect const*)&size);
    ini.Put_Rect("Map","LocalSize",*(INIRect const*)&localSize);
    ini.Put_Int("Map","Level",unknown_30c,0);
    ini.Put_String(HouseTypes[0]->ID,"TechLevel","0");
    ini.Put_String("Basic","Player",HouseTypes[0]->ID);
    double ambient=(SeedOptions.Theater==0 ? unknown_1a4[SeedOptions.Time] : unknown_1c0[SeedOptions.Time])*0.01;
    ini.Put_Double("Lighting","Ambient",ambient);
    ini.Put_Double("Lighting","RedTint",1.0);
    ini.Put_Double("Lighting","GreenTint",1.0);
    ini.Put_Double("Lighting","BlueTint",1.0);
    ini.Put_Double("Lighting","Ground",0.0);
    ini.Put_Double("Lighting","Level",(double)(unknown_188[SeedOptions.Time]/100));
    ini.Put_Double("Lighting","IonAmbient",ambient);
    ini.Put_Double("Lighting","IonRed",0.3);
    ini.Put_Double("Lighting","IonGreen",0.4);
    ini.Put_Double("Lighting","IonBlue",0.75);
    ini.Put_Double("Lighting","IonGround",0.0);
    ini.Put_Double("Lighting","IonLevel",0.0);
    if(!unknown_id_source_a3d290->unknown_22fc)ProgressScreen.Set_Progress_006201c0(0,1.0,Point2D(-1,-1));
    if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
    Clear_Tiberium_Spread_006e9670();
    Clear_Tiberium_Growth_006ea130();
    if(!(unsigned char)fullInit) {
        unknown_a40774=(int)((unsigned)unknown_a40774+1u);
        unknown_id_source_a3d290->Set_Scenario_Name_0065e730("");
        if(unknown_flag_a40d13)Clear_Scenario_0065d370();
        Read_Scenario_INI(ini,true);
        Fill_In_Data_0065cdd0();
        Cell center(Map.MapSize.Width/2+Map.MapSize.Height/2+1,Map.MapSize.Width/2+Map.MapSize.Height/2);
        unknown_id_source_a3d290->Set_Waypoint_Location(99,center);
        unknown_id_source_a3d290->Set_Waypoint_Location(unknown_id_source_a3d290->HomeCell,unknown_id_source_a3d290->Get_Waypoint_Location(99));
        Map[unknown_id_source_a3d290->Get_Waypoint_Location(unknown_id_source_a3d290->HomeCell)].unknown_140|=4;
        Map.RadarClass::unknown_slot52(unknown_id_source_a3d290->Waypoint_Coord(unknown_id_source_a3d290->HomeCell));
        unknown_a40774--;
    } else {
        unknown_id_source_a3d290->Set_Defaults();
        if(!unknown_17c)unknown_17c=(int)new UnknownPreview_0061D430;
        Report_Generation_Progress_0057be50(2);
        int theater=SeedOptions.Theater;
        bool changed=true;
        int lastTheater=unknown_id_source_a3d290->Theater;
        if(unknown_178) {
            MapSeedClass const *previous=(MapSeedClass*)unknown_178;
            lastTheater=previous->Theater;
            if(previous->Width==SeedOptions.Width && previous->Height==SeedOptions.Height && lastTheater==theater && previous->NumPlayers==SeedOptions.NumPlayers)changed=false;
        }
        if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
        if(!unknown_178 || theater!=lastTheater || changed) {
            for(index=AbstractTypes.Count()-1;index>=0;--index)if(AbstractTypes[index]->What_Am_I()==0x12)AbstractTypes.Delete(index);
            if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
            Delete_All_Objects_00519960();
            if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
            for(index=0;index<IsoTileTypes.Count();++index)AbstractTypes.Add(IsoTileTypes[index]);
        }
        Report_Generation_Progress_0057be50(5);
        if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
        if(changed) {
            Map.MouseClass::Init_Clear();
            Map.RadarClass::unknown_slot28(&size,true,false,true);
            Map.RadarClass::unknown_slot29(localSize);
            if(unknown_tactical_83996c)delete unknown_tactical_83996c;
            unknown_tactical_83996c=new Tactical;
            unknown_tactical_83996c->Reset_Dirty_Rectangles();
        }
        Report_Generation_Progress_0057be50(10);
        while(Units.Count()>0)delete Units[Units.Count()-1];
        while(Infantry.Count()>0)delete Infantry[Infantry.Count()-1];
        while(unknown_BuildingClass_list_00a40af8.Count()>0)delete unknown_BuildingClass_list_00a40af8[unknown_BuildingClass_list_00a40af8.Count()-1];
        while(Terrains.Count()>0)delete Terrains[Terrains.Count()-1];
        if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
        Map.Unknown_0055A550();
        CellClass *cell=Map.Unknown_0055A490();
        while(cell) {
            cell->unknown_11c=0;cell->unknown_11b=4;cell->IsoTileIndex=0;
            cell->unknown_11a=0;cell->OverlayIndex=-1;cell->OverlayData=0;
            cell=Map.Unknown_0055A490();
        }
        if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
        Report_Generation_Progress_0057be50(15);
        Map.Unknown_0054FDA0();Map.Unknown_0054EBD0();Map.Unknown_00563D40();
        Report_Generation_Progress_0057be50(20);
        if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
        // The canonical legacy provider takes the scenario address as a 32-bit ECX argument.
        seed_00663220::FUN_00663220(reinterpret_cast<int>(unknown_id_source_a3d290));
        Cell center(Map.MapSize.Width/2+Map.MapSize.Height/2+1,Map.MapSize.Width/2+Map.MapSize.Height/2);
        unknown_id_source_a3d290->Set_Waypoint_Location(99,center);
        unknown_id_source_a3d290->Set_Waypoint_Location(98,unknown_id_source_a3d290->Get_Waypoint_Location(99));
        Map[unknown_id_source_a3d290->Get_Waypoint_Location(98)].unknown_140|=4;
        Map.RadarClass::unknown_slot52(unknown_id_source_a3d290->Waypoint_Coord(98));
        Report_Generation_Progress_0057be50(25);
        if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
        unknown_a40774=(int)((unsigned)unknown_a40774+1u);
        if(theater!=unknown_id_source_a3d290->Theater) {Init_Theater_00519e70(theater);unknown_id_source_a3d290->Theater=theater;}
        Report_Generation_Progress_0057be50(30);
        if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
        if(!unknown_178 || theater!=lastTheater || changed) {Rules->Process(*unknown_ini_8396d0);unknown_id_source_a3d290->Read_Global_Variables(*unknown_ini_8396d0);}
        Report_Generation_Progress_0057be50(35);
        if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
        if(!unknown_178 || theater!=lastTheater || changed) {
            if(Houses.Count()==0)for(index=0;index<HouseTypes.Count();++index) {HouseClass *house=new HouseClass(HouseTypes[index]);house->Read_INI(ini);}
            if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
            TerrainTypeClass::Init(unknown_id_source_a3d290->Theater);
            if(unknown_id_source_a3d290->Theater!=unknown_loaded_theater_7d88dc)Read_Tile_Control_00529870(unknown_id_source_a3d290->Theater,true);else Clear_Tile_Use_Counts_0052b650();
            OverlayTypeClass::Init(unknown_id_source_a3d290->Theater);
            if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
            if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
            if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
            BuildingTypeClass::Init(unknown_id_source_a3d290->Theater);
            if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
            AnimTypeClass::Init(unknown_id_source_a3d290->Theater);
            if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
            SmudgeTypeClass::Init(unknown_id_source_a3d290->Theater);
            if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
            Load_Isometric_Tiles_0052b2e0(false,true);
        }
        unknown_loaded_theater_7d88dc=unknown_id_source_a3d290->Theater;
        unknown_a40774--;
    }
    Report_Generation_Progress_0057be50(40);
    if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
    if(unknown_map_cells_a70a24)delete [] unknown_map_cells_a70a24;
    unknown_map_cells_a70a24=new UnknownMapGenerationCell[(unsigned)unknown_map_cell_side_84e804*(unsigned)unknown_map_cell_side_84e804];
    Map.Unknown_0055A550();
    CellClass *cell=Map.Unknown_0055A490();
    while(cell) {
        Cell position=cell->MapCoords;
        unknown_map_cells_a70a24[position.Y*unknown_map_cell_side_84e804+position.X].Position=position;
        cell->unknown_11b=(char)unknown_30c;cell=Map.Unknown_0055A490();
    }
    Report_Generation_Progress_0057be50(45);
    if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
    Clear_Map_Regions_0056da00();
    unknown_304=0;unknown_308=0;
    unknown_310=Map_Random_Fraction_00579770()<unknown_waterfall_probability_7a5b68;
    Map.Unknown_00631E40();Map.RadarClass::unknown_slot29(localSize);Map.Unknown_00631C80();Map.Unknown_00630A00();
    unknown_id_source_a3d290->unknown_22a8=SeedOptions.Theater==0 ? unknown_1a4[SeedOptions.Time] : unknown_1c0[SeedOptions.Time];
    unknown_id_source_a3d290->AmbientLevel=unknown_188[SeedOptions.Time];
    unknown_id_source_a3d290->AmbientRed=SeedOptions.Theater==0 ? unknown_1dc[SeedOptions.Time] : unknown_230[SeedOptions.Time];
    unknown_id_source_a3d290->AmbientGreen=SeedOptions.Theater==0 ? unknown_1f8[SeedOptions.Time] : unknown_24c[SeedOptions.Time];
    unknown_id_source_a3d290->AmbientBlue=SeedOptions.Theater==0 ? unknown_214[SeedOptions.Time] : unknown_268[SeedOptions.Time];
    unknown_id_source_a3d290->IonAmbient=87;unknown_id_source_a3d290->IonRed=30;unknown_id_source_a3d290->IonGreen=40;unknown_id_source_a3d290->IonBlue=75;unknown_id_source_a3d290->IonGround=0;unknown_id_source_a3d290->IonLevel=0;
    Report_Generation_Progress_0057be50(50);
    if(wcslen(SeedOptions.DescriptionBuffer)==0)wcscpy(SeedOptions.DescriptionBuffer,StringTable::Load_String("TXT_RANDOM_MAP_DESCRIPTION",0,"D:\\Ra2\\MapGen.cpp",0x19b5));
}
// @ref ??_C@_07FLDP@RedTint?$AA@=007e1a34
// @ref ??_C@_08JCNO@BlueTint?$AA@=007e1a1c
// @ref ??_C@_09CJGJ@GreenTint?$AA@=007e1a28
// @ref ??_C@_09OOBE@LocalSize?$AA@=007d5e14
// @ref __real@4@3ffdaaaaab0000000000=007a5ea8
// @ref __real@8@3fff9999999999999800=0079dda8
// @ref __real@4@3ffd8000000000000000=007a5b68
