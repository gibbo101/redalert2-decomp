#include "shared/map.hpp"
#include "shared/radar.hpp"
#include "shared/unknown_map_generator.hpp"
#include "shared/map_region.hpp"
#include "shared/cell.hpp"
#include "shared/id_source.hpp"
#include "shared/session_state.hpp"
#include "shared/progress_screen.hpp"
#include "shared/map_preview.hpp"
#include "shared/random2.hpp"
#include "shared/map_gaussian.hpp"
#define RA2_VEIN_HEAP_REMOVE_MIN_IMPLEMENTATION
#include "shared/tiberium.hpp"
#include "shared/debug_printf.hpp"
#include "shared/win32_api.hpp"
extern void (__cdecl *unknown_map_generation_callback_7e09c4)();
#include "shared/map_random.hpp"
extern DynamicVectorClass<MapRegionClass *> unknown_map_regions_a6fd28;
extern int unknown_a3d2a4;
bool __cdecl Generate_Starting_Points_00576420();
double __cdecl Map_Random_Fraction_00579770();
void __cdecl Make_Water_Regions_0056e890();
void __fastcall Make_Land_Regions_0056e910(bool flag);
void __fastcall Initialize_Vegetation_Weights_005850a0(UnknownMapGenerator *generator);
void Initialize_Grid_Thresholds_00585240();
// @ref ?Initialize_Grid_Thresholds_00585240@@=00585240
// @ref ??_GMapRegionClass@@QAEPAXI@Z=0058da70
// @ref ?unknown_map_generation_callback_7e09c4@@=007e09c4
// @ref ?unknown_map_random_a705c0@@=00a705c0
// @ref ?unknown_map_regions_a6fd28@@=00a6fd28
// @ref ?unknown_a3d2a4@@=00a3d2a4
// @ref ?Map_Random_Fraction_00579770@@=00579770
// @ref ?Make_Water_Regions_0056e890@@=0056e890
// @ref ?Make_Land_Regions_0056e910@@=0056e910
// @ref ?Initialize_Vegetation_Weights_005850a0@@=005850a0
// @ref ?Grow_Adjacent_Empty_Tiles_0057cf20@UnknownMapGenerator@@=0057cf20
// @ref ?Randomize_Tile_Group_0057de10@UnknownMapGenerator@@=0057de10
// @ref ?Init_Map_0057ae00@UnknownMapGenerator@@=0057ae00
// @ref ?Generate_Starting_Points_00576420@@=00576420
// @ref ?Generate_Neutral_Tech_Buildings_0058ad90@UnknownMapGenerator@@=0058ad90
// @ref ?Create_Resources_00583b80@UnknownMapGenerator@@=00583b80
// @ref ?Generate_Hills_00584dd0@UnknownMapGenerator@@=00584dd0
// @ref ?Generate_Vegetation_005852c0@UnknownMapGenerator@@=005852c0
// @ref ?unknown_005c7ef0@UnknownPreview_0061D430@@=005c7ef0
extern "C" char unknown_rmg_message_007e19b4[];
// @ref _unknown_rmg_message_007e19b4=007e19b4
extern "C" char unknown_rmg_message_007e19a0[];
// @ref _unknown_rmg_message_007e19a0=007e19a0
extern "C" char unknown_rmg_message_007e198c[];
// @ref _unknown_rmg_message_007e198c=007e198c
extern "C" char unknown_rmg_message_007e1974[];
// @ref _unknown_rmg_message_007e1974=007e1974
extern "C" char unknown_rmg_message_007e1950[];
// @ref _unknown_rmg_message_007e1950=007e1950
extern "C" char unknown_rmg_message_007e1930[];
// @ref _unknown_rmg_message_007e1930=007e1930
extern "C" char unknown_rmg_message_007e1914[];
// @ref _unknown_rmg_message_007e1914=007e1914
extern "C" char unknown_rmg_message_007e18fc[];
// @ref _unknown_rmg_message_007e18fc=007e18fc
extern "C" char unknown_rmg_message_007e18e4[];
// @ref _unknown_rmg_message_007e18e4=007e18e4
extern "C" char unknown_rmg_message_007e18c4[];
// @ref _unknown_rmg_message_007e18c4=007e18c4
extern "C" char unknown_rmg_message_007e18b4[];
// @ref _unknown_rmg_message_007e18b4=007e18b4
extern "C" char unknown_rmg_message_007e1898[];
// @ref _unknown_rmg_message_007e1898=007e1898
extern "C" char unknown_rmg_message_007e188c[];
// @ref _unknown_rmg_message_007e188c=007e188c
extern "C" char unknown_rmg_progress_shape_7e19cc[];
// @ref _unknown_rmg_progress_shape_7e19cc=007e19cc
#include "shared/map_gaussian.hpp"
MapGaussianClass::MapGaussianClass(UniformCallback callback)
    : HasSpare(false),Spare(0.0),Uniform(callback)
{
}

extern "C" char unknown_rmg_radar_message[];
// @ref _unknown_rmg_radar_message=007e1898
// Use the existing canonical progress operation at 0x0057BE50.
// Its accepted out-of-line copy lives in another population; this is the same real body.
// @ref ?Report_Generation_Progress_0057be50@@=0057be50
void __stdcall Report_Generation_Progress_0057be50(int progress)
{
    if (unknown_id_source_a3d290->unknown_22fc) {
        unknown_session_a3d298.Loading_Progress_00672160((int)((unsigned int)progress + 99u));
    } else {
        ProgressScreen.Set_Progress_006201c0(0, (double)progress, Point2D(-1, -1));
    }
}

// Init_Regions is evidenced by its original inline site (MapRegionClass::Destroy_Cell_Regions is defined out of
// line at 0x0056E790 and expanded inline here and in the generator destructor 0x005771B0).
inline void UnknownMapGenerator::Init_Regions()
{
    int index;
    MapRegionClass::Destroy_Cell_Regions();
    Make_Water_Regions_0056e890();
    for(index=0;index<unknown_map_regions_a6fd28.Count();++index) {
        MapRegionClass *region=unknown_map_regions_a6fd28[index];
        if(region->unknown_14) {
            int wetMap=SeedOptions.MapType==3 || SeedOptions.MapType==4;
            region->Grow_Border_00570040((region->CellCount>8000)+4+!(unsigned char)wetMap);
            region->Expand_Cells_005702b0();
        }
    }
    Make_Land_Regions_0056e910(false);
 }
// Existing public int,int/ECX/RET8 contract retained; low-byte flag and HWND intent are hypotheses.
void UnknownMapGenerator::Unknown_0057A0D0(int fullInit,int dialogValue)
{
    HWND window=(HWND)dialogValue;
    int index;
    CellClass *cell;
    if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
    unknown_map_random_a705c0=Random2Class(SeedOptions.Seed);
    unknown_map_gaussian_a6fd50=MapGaussianClass(Map_Random_Fraction_00579770);
    if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
    bool showProgress=!unknown_id_source_a3d290->unknown_22fc;
    if(showProgress) {
        ProgressScreen.Init(100.0,1,window);
        ProgressScreen.Load_Shape(unknown_rmg_progress_shape_7e19cc,0,0);
        ProgressScreen.Unknown_0061EFA0(Point2D(-1,-1),0,false,true);
        ProgressScreen.Draw_It(Point2D(-1,-1));
        HWND control=GetDlgItem(window,0x638);
        if(control)ShowWindow(control,5);
    }
    if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
    Debug_Printf(unknown_rmg_message_007e19b4);
    Init_Map_0057ae00(fullInit);
    if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
    unknown_a40774=(int)((unsigned)unknown_a40774+1u);
    if((unsigned char)fullInit) {
        unknown_preview_a6fee4->Unknown_0061D660();
        SendMessageA(window,15,0,0);
        if(unknown_session_a3d298.Type==4 && unknown_a3d2a4==2)unknown_preview_a6fee4->unknown_005c7ef0();
    }
    if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
    Read_Settings_00579960();
    Debug_Printf(unknown_rmg_message_007e19a0);
    if(SeedOptions.MapType==3 || SeedOptions.MapType==4) {
        if(SeedOptions.WaterAmount)Run_Region_Attempts_0057dd60();
    } else Initialize_Region_Map_0057bea0();
    Randomize_Tile_Group_0057de10();
    Report_Generation_Progress_0057be50(55);
    if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
    if((unsigned char)fullInit) {
        unknown_preview_a6fee4->Unknown_0061D660();
        SendMessageA(window,15,0,0);
        if(unknown_session_a3d298.Type==4 && unknown_a3d2a4==2)unknown_preview_a6fee4->unknown_005c7ef0();
    }
    if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
    Report_Generation_Progress_0057be50(60);
    if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
    if((unsigned char)fullInit) {
        unknown_preview_a6fee4->Unknown_0061D660();
        SendMessageA(window,15,0,0);
        if(unknown_session_a3d298.Type==4 && unknown_a3d2a4==2)unknown_preview_a6fee4->unknown_005c7ef0();
    }
    if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
    Debug_Printf(unknown_rmg_message_007e198c);
    Init_Regions();
    Report_Generation_Progress_0057be50(65);
    if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
    Debug_Printf(unknown_rmg_message_007e1974);
    if(SeedOptions.MapType==4 || SeedOptions.MapType==3) {
        MapRegionClass::Make_Ice_Regions_005704c0();
        MapRegionClass::Make_Regions_00570810();
        Adjust_Ramp_Junctions_005831c0();
        Map.Build_All_Cliffs(0,-1);
        unknown_00582fd0();
    }
    Report_Generation_Progress_0057be50(70);
    if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
    if((unsigned char)fullInit) {
        unknown_preview_a6fee4->Unknown_0061D660();
        SendMessageA(window,15,0,0);
        if(unknown_session_a3d298.Type==4 && unknown_a3d2a4==2)unknown_preview_a6fee4->unknown_005c7ef0();
    }
    if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
    Grow_Adjacent_Empty_Tiles_0057cf20();
    Debug_Printf(unknown_rmg_message_007e1950);
    Map.Unknown_0055A550();
    for(cell=Map.Unknown_0055A490();cell;cell=Map.Unknown_0055A490())cell->Unknown_00472540(-1);
    if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
    Report_Generation_Progress_0057be50(75);
    Debug_Printf(unknown_rmg_message_007e1930);
    bool starts=false;
    while(!starts) {
        starts=Generate_Starting_Points_00576420();
        if(starts)starts=Init_Start_Points_00583790();
    }
    Debug_Printf(unknown_rmg_message_007e1914);
    if(SeedOptions.MapType!=0)Generate_Neutral_Tech_Buildings_0058ad90();
    if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
    Debug_Printf(unknown_rmg_message_007e18fc);
    Create_Resources_00583b80();
    if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();

    if(unknown_map_cells_a70a24) {
        int size=(int)((unsigned)unknown_map_cell_side_84e804*(unsigned)unknown_map_cell_side_84e804);
        for(index=0;index<size;++index) {
            unknown_map_cells_a70a24[index].RegionIndex=-1;
            unknown_map_cells_a70a24[index].unknown_3c=-1;
        }
    }
    for(index=(int)((unsigned)unknown_map_regions_a6fd28.Count()-1u);index>=0;--index) {
        MapRegionClass *region=unknown_map_regions_a6fd28[index];
        if(region)delete region;
    }
    unknown_map_region_next_index_a70a28=0;
    Debug_Printf(unknown_rmg_message_007e1950);
    Map.Unknown_0055A550();
    for(cell=Map.Unknown_0055A490();cell;cell=Map.Unknown_0055A490())cell->Unknown_00472540(-1);
    Report_Generation_Progress_0057be50(80);
    if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
    if((unsigned char)fullInit) {
        unknown_preview_a6fee4->Unknown_0061D660();
        SendMessageA(window,15,0,0);
        if(unknown_session_a3d298.Type==4 && unknown_a3d2a4==2)unknown_preview_a6fee4->unknown_005c7ef0();
    }
    if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
    Report_Generation_Progress_0057be50(85);
    if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
    if((unsigned char)fullInit) {
        unknown_preview_a6fee4->Unknown_0061D660();
        SendMessageA(window,15,0,0);
        if(unknown_session_a3d298.Type==4 && unknown_a3d2a4==2)unknown_preview_a6fee4->unknown_005c7ef0();
    }
    if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
    Debug_Printf(unknown_rmg_message_007e1950);
    Map.Unknown_0055A550();
    for(cell=Map.Unknown_0055A490();cell;cell=Map.Unknown_0055A490())cell->Unknown_00472540(-1);
    if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
    Debug_Printf(unknown_rmg_message_007e18e4);
    Generate_Hills_00584dd0();
    Report_Generation_Progress_0057be50(90);
    if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
    if((unsigned char)fullInit) {
        unknown_preview_a6fee4->Unknown_0061D660();
        SendMessageA(window,15,0,0);
        if(unknown_session_a3d298.Type==4 && unknown_a3d2a4==2)unknown_preview_a6fee4->unknown_005c7ef0();
    }
    if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
    Debug_Printf(unknown_rmg_message_007e18c4);
    if(SeedOptions.Theater==0) {
        Initialize_Vegetation_Weights_005850a0(this);
        Generate_Vegetation_005852c0();
    } else {
        Initialize_Grid_Thresholds_00585240();
        Generate_Vegetation_00585a60();
    }
    if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
    Report_Generation_Progress_0057be50(95);
    if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
    if((unsigned char)fullInit) {
        unknown_preview_a6fee4->Unknown_0061D660();
        SendMessageA(window,15,0,0);
        if(unknown_session_a3d298.Type==4 && unknown_a3d2a4==2)unknown_preview_a6fee4->unknown_005c7ef0();
    }
    unknown_a40774=(int)((unsigned)unknown_a40774-1u);
    if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
    Debug_Printf(unknown_rmg_message_007e1950);
    Map.Unknown_0055A550();
    for(cell=Map.Unknown_0055A490();cell;cell=Map.Unknown_0055A490())cell->Unknown_00472540(-1);
    if(unknown_map_generation_callback_7e09c4)unknown_map_generation_callback_7e09c4();
    TiberiumClass::Init_Growth();
    TiberiumClass::Init_Spread();
    Debug_Printf(unknown_rmg_message_007e18b4);
    unknown_304=0;
    unknown_308=0;
    if(unknown_map_cells_a70a24!=0) {
        delete [] unknown_map_cells_a70a24;
        unknown_map_cells_a70a24=0;
    }
    for(index=(int)((unsigned int)unknown_map_regions_a6fd28.Count()-1u);index>=0;--index) {
        MapRegionClass *region=unknown_map_regions_a6fd28[index];
        if(region!=0)delete region;
    }
    unknown_map_region_next_index_a70a28=0;
    Map.Unknown_0054B2E0();
    Debug_Printf(unknown_rmg_radar_message);
    Map.RadarClass::unknown_slot29(Map.MapLocalSize);
    Map.Unknown_00630A00();
    Report_Generation_Progress_0057be50(100);
    Debug_Printf(unknown_rmg_message_007e188c);
    if(showProgress) {
        HWND control=GetDlgItem(window,0x638);
        if(control)ShowWindow(control,0);
        Report_Generation_Progress_0057be50(0);
        ProgressScreen.Clear_Window();
    }
}
