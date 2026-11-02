// int __fastcall Init_Game() -- 0x005116A0
// Body 0x005116A0-0x005127E3 (4420 bytes). Tiberian Sun's Init_Game with its Bootstrap, Init_Mouse and
// Init_CDROM_Access expanded inline: scenario and rules, the bootstrap mixfiles, palettes and drawers,
// the CD check, the secondary mixfiles, SOUND/EVA/THEME.INI, the bulk data and the rules, the intro
// movies and the multiplayer score records.
#include "shared/crt_memory.hpp"
#include "shared/house.hpp"
#include "shared/id_source.hpp"
#include "shared/rules.hpp"
#include "shared/keyboard.hpp"
#include "shared/mono_class.hpp"
#include "shared/text_print.hpp"
#include "shared/audio.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/ccini_class.hpp"
#include "shared/convert.hpp"
#include "shared/matrix3d.hpp"
#include "shared/mouse.hpp"
#include "shared/wwmouse.hpp"
#include "shared/gadget.hpp"
#include "shared/dsurface.hpp"
#include "shared/display.hpp"
#include "shared/mouse_class.hpp"
#include "shared/cd.hpp"
#include "shared/cd_file_class.hpp"
#include "shared/special.hpp"
#include "shared/wol_registry_options.hpp"
#include "shared/ww_message_box.hpp"
#include "shared/string_table.hpp"
#include "shared/options.hpp"
#include "shared/movie.hpp"
#include "shared/tactical.hpp"
#include "shared/voc_class.hpp"
#include "shared/vox_class.hpp"
#include "shared/vox_speech.hpp"
#include "shared/theme.hpp"
#include "shared/session_state.hpp"
#include "shared/multiplayer_game_mode.hpp"
#include "shared/progress_screen.hpp"
#include "shared/exit.hpp"
#include "shared/ms_engine.hpp"
#include "shared/debug_printf.hpp"
#include "shared/unknown_globals.hpp"

// @ref ??_C@_03JIMF@?$DP?3?2?$AA@=007db914
// @ref ??_C@_04NHBG@Play?$AA@=007db8c0
// @ref ??_C@_07KCPG@?5?4?4?4OK?6?$AA@=007db97c
// @ref ??_C@_07PMMH@EVA?4INI?$AA@=007db700
// @ref ??_C@_08BBIA@ANIM?4PAL?$AA@=007db9b8
// @ref ??_C@_08GIBP@WESTLOGO?$AA@=007db604
// @ref ??_C@_08OJE@A00_F00E?$AA@=007db5f8
// @ref ??_C@_09IAGH@SOUND?4INI?$AA@=007db754
// @ref ??_C@_09MAMJ@THEME?4INI?$AA@=007db6a8
// @ref ??_C@_09NCG@CAMEO?4PAL?$AA@=007d61a0
// @ref ??_C@_0BA@BFDB@Init?5Bulk?5Data?6?$AA@=007db660
// @ref ??_C@_0BA@EEEN@Init?5Campaigns?6?$AA@=007db810
// @ref ??_C@_0BA@LKCD@TXT_CD_DIALOG_1?$AA@=007d2124
// @ref ??_C@_0BB@DOIO@Reading?5EVA?4INI?6?$AA@=007db708
// @ref ??_C@_0BC@HJLC@Init?5Anim?5System?6?$AA@=007db7c8
// @ref ??_C@_0BD@FOEM@Reading?5THEME?4INI?6?$AA@=007db6b4
// @ref ??_C@_0BD@NKAM@Reading?5SOUND?4INI?6?$AA@=007db760
// @ref ??_C@_0BG@KONK@Creating?5TacticalMap?6?$AA@=007db794
// @ref ??_C@_0BG@LODO@Game?5Init?5Completed?4?6?$AA@=007db5b8
// @ref ??_C@_0BG@NMBK@VolumeCheck?5FAILED?$CB?$CB?6?$AA@=007db8fc
// @ref ??_C@_0BH@GBOL@Reading?5Game?5Settings?6?$AA@=007db7dc
// @ref ??_C@_0BI@JCIB@Playing?5startup?5movie?4?6?$AA@=007db5e0
// @ref ??_C@_0BJ@BBBF@Init?5Color?5Remap?5Tables?6?$AA@=007db7ac
// @ref ??_C@_0BJ@GAGG@Failed?5to?5load?5EVA?4INI?$CB?6?$AA@=007db6c8
// @ref ??_C@_0BJ@KLOC@Failed?5to?5find?5EVA?4INI?$CB?6?$AA@=007db6e4
// @ref ??_C@_0BJ@OOPG@?5?4?4Failed?5to?5bootstrap?$CB?6?$AA@=007db9fc
// @ref ??_C@_0BL@CDPF@Failed?5to?5find?5SOUND?4INI?$CB?6?$AA@=007db738
// @ref ??_C@_0BL@GKBN@Failed?5to?5load?5THEME?4INI?$CB?6?$AA@=007db670
// @ref ??_C@_0BL@ICJJ@Failed?5to?5load?5SOUND?4INI?$CB?6?$AA@=007db71c
// @ref ??_C@_0BL@MLHB@Failed?5to?5find?5THEME?4INI?$CB?6?$AA@=007db68c
// @ref ??_C@_0BM@CGBJ@Calling?5Force_CD_Available?6?$AA@=007db93c
// @ref ??_C@_0BN@GAPD@Init?5Secondary?5Mixfiles?4?4?4?4?4?$AA@=007db898
// @ref ??_C@_0BN@OMBN@Failed?5to?5initialize?5Rules?$CB?6?$AA@=007db634
// @ref ??_C@_0BO@MLNI@Failed?5to?5instantiate?5Rules?$CB?6?$AA@=007dba54
// @ref ??_C@_0BP@EKGM@Failed?5to?5create?5TacticalMap?$CB?6?$AA@=007db774
// @ref ??_C@_0CB@HNMK@Failed?5to?5instantiate?5Scenario?$CB?6@=007dba74
// @ref ??_C@_0CE@IBDP@Failed?5to?5initialize?5CDROM?5acces@=007db864
// @ref ??_C@_0CE@NPLN@Failed?5to?5find?5disk?5?$CIuser?5cancel@=007db918
// @ref ??_C@_0CE@OGHH@Playing?5first?5time?5intro?5sequenc@=007db610
// @ref ??_C@_0CK@KLIP@Failed?5to?5initialize?5bootstrap?5m@=007dba18
// @ref ??_C@_0ED@GEKD@?9CD?5parameter?5was?5specified?4?5No?5@=007db820
// @ref ??_C@_0L@BPJI@Init?5Game?6?$AA@=007dba98
// @ref ??_C@_0L@PNLO@voxels?4vpl?$AA@=007db9c4
// @ref ??_C@_0M@DJNJ@PALETTE?4PAL?$AA@=007db9ac
// @ref ??_C@_0M@GNGH@Init?5Mouse?6?$AA@=007db970
// @ref ??_C@_0M@LLJJ@Init?5Rules?6?$AA@=007db654
// @ref ??_C@_0M@MECD@Init?5Heaps?6?$AA@=007db804
// @ref ??_C@_0M@MMB@GRFXTXT?4PAL?$AA@=007db990
// @ref ??_C@_0M@NDOD@Init?5CDROM?6?$AA@=007db958
// @ref ??_C@_0M@OJA@GRFXTXT?4SHP?$AA@=007db984
// @ref ??_C@_0M@PNFA@UNITSNO?4PAL?$AA@=007db9f0
// @ref ??_C@_0N@GAOD@TEMPERAT?4PAL?$AA@=007db9e0
// @ref ??_C@_0N@KHCO@MOUSEPAL?4PAL?$AA@=007db99c
// @ref ??_C@_0N@MFMP@WAYPOINT?4PAL?$AA@=007db9d0
// @ref ??_C@_0O@NGN@TXT_CD_ERROR1?$AA@=007db8d4
// @ref ??_C@_0O@NKKK@Init?5Threads?6?$AA@=007db7f4
// @ref ??_C@_0P@CBHO@Init?5Commands?6?$AA@=007db5d0
// @ref ??_C@_0P@DHOH@?5?4?4?4Failed?$CB?$CB?$CB?6?$AA@=007db888
// @ref ??_C@_0P@FNJN@Bootstrap?4?4?4?4?4?$AA@=007dba44
// @ref ??_C@_05MDNJ@Intro?$AA@=007d9d98
// @ref ??_C@_06DN@TXT_OK?$AA@=007db8f4
// @ref ??_C@_07IBND@RA2?4INI?$AA@=007db8b8
// @ref ??_C@_09JKEA@MOUSE?4SHP?$AA@=007db964
// @ref ??_C@_0L@NPIH@TXT_CANCEL?$AA@=007db8c8
// @ref ??_C@_0BA@NANB@D?3?2Ra2?2Init?4CPP?$AA@=007db8e4
// @ref ??_C@_13ECNF@?$AA?5?$AA?$AA@=007d64f4
// @ref ??_H@YGXPAXIHP6EX0@Z@Z=0040aed0
// @ref ??_GINIClass@@UAEPAXI@Z=004deef0
// @ref ??0CCINIClass@@QAE@XZ=0051ade0
// @ref ??0INIClass@@QAE@XZ=0051ad50
// @ref ??0RGBClass@@QAE@EEE@Z=00432d70
// @ref ??1CCFileClass@@UAE@XZ=0051ad20
// @ref ??1CDFileClass@@UAE@XZ=0051ad10
// @ref ??4PaletteClass@@QAEAAV0@ABV0@@Z=00603080
// @ref ?Draw_Loading_Screen@@YIXXZ=00516560
// @ref ?Init_Commands_005173C0@@YIXXZ=005173c0
// @ref ?Init_Rules@@YI_NXZ=005129c0
// @ref ?Play_Movie_005A02B0@@YIXPBDH_N11@Z=005a02b0
// @ref ?Play_Movie_005A02D0@@YIXPBDH_N111@Z=005a02d0
// @ref ?Unknown_0059DA50@@YIPAVMonoClass@@H@Z=0059da50
// @ref ?Unknown_005EAC10@@YIXXZ=005eac10
// @ref ?Unknown_006E7890@ThemeClass@@QAEXAAVCCINIClass@@@Z=006e7890
// @ref ?Unknown_00718060@@YIXXZ=00718060
// @ref ?unknown_004ff2b0@WolRegistryOptions@@QBE_NXZ=004ff2b0
// @ref ?unknown_004ff2d0@WolRegistryOptions@@QBE_NXZ=004ff2d0
// @ref ?unknown_audio_7f4cc8@@3HA=007f4cc8
// @ref ?unknown_camera_angle_79acf4@@3MA=0079acf4
// @ref ?unknown_camera_angle_839a5c@@3MA=00839a5c
// @ref ?unknown_hicolor_7ce008@@3_NA=007ce008
// @ref ?unknown_light_angle_79acf0@@3MA=0079acf0
// @ref ?unknown_loading_time_a41668@@3_KA=00a41668
// @ref ?unknown_palette_837510@@3VPaletteClass@@A=00837510
// @ref ?unknown_palette_838110@@3VPaletteClass@@A=00838110
// @ref ?unknown_palette_838410@@3VPaletteClass@@A=00838410
// @ref ?unknown_palette_838a10@@3VPaletteClass@@A=00838a10
// @ref ?unknown_palette_838d10@@3VPaletteClass@@A=00838d10
// @ref ?unknown_remap_name_7d83b4@@3PBDB=007d83b4
// @ref ??_C@_04HPIL@Grey?$AA@=007d83b8
// @ref ?unknown_use_voxel_cache_839a58@@3_NA=00839a58
// @ref ?unknown_voxel_colors_ae3008@@3PAVRGBClass@@A=00ae3008

extern PaletteClass unknown_palette_837510;     // 0x00837510 black (TS BlackPalette)
extern PaletteClass unknown_palette_837810;     // 0x00837810 WAYPOINT.PAL
extern PaletteClass unknown_palette_838110;     // 0x00838110 the theater palette as loaded (TS OriginalPalette)
extern PaletteClass unknown_palette_838410;     // 0x00838410 (TS WhitePalette)
extern PaletteClass unknown_palette_838a10;     // 0x00838A10 the unit palette (TS SchemePalette)
extern PaletteClass unknown_palette_838d10;     // 0x00838D10 the voxel palette
extern RGBClass unknown_voxel_colors_ae3008[256];   // 0x00AE3008 voxels.vpl's colours
extern bool unknown_hicolor_7ce008;             // 0x007CE008 (TS HicolorFlag)
extern int unknown_audio_7f4cc8;                // 0x007F4CC8 Audio_Init's argument
extern bool unknown_use_voxel_cache_839a58;     // 0x00839A58
extern float unknown_camera_angle_839a5c;       // 0x00839A5C
extern Matrix3D unknown_voxel_transform_839a70; // 0x00839A70
extern float unknown_camera_angle_79acf4;       // 0x0079ACF4 default
extern float unknown_light_angle_79acf0;        // 0x0079ACF0 default
extern int unknown_af6614;                      // 0x00AF6614
extern int unknown_af6610;                      // 0x00AF6610
extern MouseClass Map;                          // 0x008324E0
extern char const *unknown_remap_name_7d83b4;   // 0x007D83B4
extern unsigned __int64 unknown_loading_time_a41668;
extern ConvertClass *unknown_drawer_8323c8;     // 0x008323C8 (TS MouseDrawer)    // 0x00A41668 when the loading screen may go

MonoClass *__fastcall Unknown_0059DA50(int page);       // 0x0059DA50
bool __fastcall Init_Bootstrap_Mixfiles();              // 0x00515C90
void __fastcall Unknown_005EAC10();                     // 0x005EAC10
void __fastcall Unknown_006F1B60();                     // 0x006F1B60
void __fastcall Draw_Loading_Screen();                  // 0x00516560
int __fastcall unknown_run_716f40(void *file);          // 0x00716F40 (TS VoxelDrawSystem::Load_VPL_File)
void __stdcall Unknown_00717FB0(float angle);           // 0x00717FB0 (TS Set_Voxel_Light_Angle)
void __fastcall Unknown_00718060();                     // 0x00718060 (TS Init_Voxel_Matrices)
bool Init_Expansion_Files();                            // 0x00515AF0
bool __fastcall Init_Secondary_Mixfiles();              // 0x00515E70
void __fastcall Read_Battle_Files();                    // 0x005127F0
bool __fastcall Init_Bulk_Data();                       // 0x00516900
bool __fastcall Init_Rules();                           // 0x005129C0
void __fastcall Play_Movie_005A02B0(char const *name, int theme, bool a, bool b, bool c);          // 0x005A02B0
void __fastcall Play_Movie_005A02D0(char const *name, int theme, bool a, bool b, bool c, bool d);  // 0x005A02D0
void __fastcall Init_Commands_005173C0();
void __fastcall Init_Random();                          // 0x00515710               // 0x005173C0

// Tiberian Sun's Set_Voxel_Camera_Angle.
inline void Set_Voxel_Camera_Angle(float angle)
{
    unknown_camera_angle_839a5c = angle;
    unknown_voxel_transform_839a70.Make_Identity();
}

static void Init_Heaps() {}
static void Init_Threads() {}
static bool Bootstrap();
static void Init_Mouse();
static bool Init_CDROM_Access();

int __fastcall Init_Game()
{
    Debug_Printf("Init Game\n");

    unknown_id_source_a3d290 = new UnknownIDSource;
    if (unknown_id_source_a3d290 == 0) {
        Debug_Printf("Failed to instantiate Scenario!\n");
        return -1;
    }

    Rules = new RulesClass;
    if (Rules == 0) {
        Debug_Printf("Failed to instantiate Rules!\n");
        return -1;
    }

    Debug_Printf("Bootstrap.....");
    if (!Bootstrap()) {
        Unknown_00496460(" ..Failed to bootstrap!\n");
        return -1;
    }
    Unknown_00496460(" ...OK\n");

    Debug_Printf("Init Mouse\n");
    Init_Mouse();

    Debug_Printf("Init CDROM\n");
    if (!Init_CDROM_Access()) {
        Debug_Printf("Failed to initialize CDROM access!\n");
        return 1;
    }

    Debug_Printf("Init Secondary Mixfiles.....");
    if (!Init_Secondary_Mixfiles()) {
        Unknown_00496460(" ...Failed!!!\n");
        return -1;
    }
    Unknown_00496460(" ...OK\n");

    Debug_Printf("Init Campaigns\n");
    Read_Battle_Files();

    Debug_Printf("Init Heaps\n");
    Init_Heaps();

    Debug_Printf("Init Threads\n");
    Init_Threads();

    Debug_Printf("Reading Game Settings\n");
    Options.Load_Settings();

    Debug_Printf("Init Anim System\n");
    VQA_Unknown_0071DB20();
    VQA_Unknown_0071DB60(0);

    Debug_Printf("Init Color Remap Tables\n");
    unknown_remap_name_7d83b4 = "Grey";

    Debug_Printf("Creating TacticalMap\n");
    delete unknown_tactical_83996c;
    unknown_tactical_83996c = new Tactical;
    if (unknown_tactical_83996c == 0) {
        Debug_Printf("Failed to create TacticalMap!\n");
        return -1;
    }

    Surface *hidden = unknown_surface_839954;
    unknown_surface_83995c = hidden;

    Debug_Printf("Reading SOUND.INI\n");
    CCFileClass voc_file("SOUND.INI");
    if (voc_file.Is_Available() == false) {
        Debug_Printf("Failed to find SOUND.INI!\n");
        return -1;
    }
    CCINIClass voc_ini;
    if (!voc_ini.Load(voc_file, false)) {
        Debug_Printf("Failed to load SOUND.INI!\n");
        return -1;
    }
    Unknown_00714860();
    VocClass::Process(voc_ini);

    Debug_Printf("Reading EVA.INI\n");
    CCFileClass eva_file("EVA.INI");
    if (eva_file.Is_Available() == false) {
        Debug_Printf("Failed to find EVA.INI!\n");
        return -1;
    }
    CCINIClass eva_ini;
    if (!eva_ini.Load(eva_file, false)) {
        Debug_Printf("Failed to load EVA.INI!\n");
        return -1;
    }
    Speech_Free_All();
    VoxClass::Process(eva_ini);

    Debug_Printf("Reading THEME.INI\n");
    CCFileClass theme_file("THEME.INI");
    if (theme_file.Is_Available() == false) {
        Debug_Printf("Failed to find THEME.INI!\n");
        return -1;
    }
    CCINIClass theme_ini;
    if (!theme_ini.Load(theme_file, false)) {
        Debug_Printf("Failed to load THEME.INI!\n");
        return -1;
    }
    Theme.Unknown_006E7A70();
    Theme.Unknown_006E7890(theme_ini);
    Theme.Scan();

    Debug_Printf("Init Bulk Data\n");
    if (!Init_Bulk_Data()) {
        return -1;
    }

    Debug_Printf("Init Rules\n");
    if (!Init_Rules()) {
        Debug_Printf("Failed to initialize Rules!\n");
        return -1;
    }

    while (Audio_Now() < unknown_loading_time_a41668) {
    }

    if (unknown_special_a40920.IsFromInstall == true) {
        Debug_Printf("Playing first time intro sequence.\n");
        if (unknown_special_a40920.EscapeMovies) {
            Play_Movie_005A02D0("WESTLOGO", -1, true, true, true, false);
            Play_Movie_005A02D0("A00_F00E", -1, false, true, true, false);
        } else {
            Play_Movie_005A02B0("WESTLOGO", -1, true, true, true);
            Play_Movie_005A02B0("A00_F00E", -1, false, true, true);
        }
    } else {
        Debug_Printf("Playing startup movie.\n");
        Play_Movie_005A02D0("WESTLOGO", -1, true, true, true, false);
    }
    unknown_5159b0(0, true);
    unknown_481fb0();

    unknown_max_players_a3d558 = Rules->MaxPlayers;
    unknown_remap_name_7d83b4 = "Grey";

    unknown_session_a3d298.unknown_22f4 = 0;
    unknown_session_a3d298.ScoreCount = 0;
    unknown_session_a3d298.unknown_2300 = 0;
    for (int i = 0; i < 8; i++) {
        unknown_session_a3d298.Scores[i].Name[0] = 0;
        unknown_session_a3d298.Scores[i].Winner = 0;
        for (int j = 0; j < 4; j++) {
            unknown_session_a3d298.Scores[i].KillCounts[j] = -1;
            unknown_session_a3d298.Scores[i].LostCounts[j] = -1;
            unknown_session_a3d298.Scores[i].BuiltCounts[j] = -1;
            unknown_session_a3d298.Scores[i].ScoreCounts[j] = -1;
        }
    }
    memset(unknown_flags_a3f118, true, sizeof(unknown_flags_a3f118));

    Init_Random();
    Debug_Printf("Init Commands\n");
    Init_Commands_005173C0();
    Debug_Printf("Game Init Completed.\n");
    MultiplayerGameMode::unknown_init_modes_5b8bd0();
    return 0;
}

static bool Bootstrap()
{
    int index;

    if (!unknown_hicolor_7ce008) {
        Unknown_004955D0(&unknown_palette_837510, 0, 0);
    }

    if (CD::IsLocal == true) {
        CD::Set_Required_CD(-2);
    }

    do {
        WWKeyboard->Check();
    } while (!unknown_flag_a40d28);

    unknown_redraw_8523dc = false;
    Unknown_0059DA50(4)->Clear();

    if (!Init_Bootstrap_Mixfiles()) {
        Debug_Printf("Failed to initialize bootstrap mixfiles!\n");
        return false;
    }

    BitText = new BitTextClass;
    Unknown_005EAC10();
    Unknown_006F1B60();
    Audio_Init(unknown_audio_7f4cc8);
    Draw_Loading_Screen();
    WWKeyboard->Clear();

    memmove(&unknown_palette_838a10[0], MixFileClass::Retrieve("UNITSNO.PAL"), sizeof(unknown_palette_838a10));
    for (index = 0; index < 256; index++) {
        unknown_palette_838a10[index] = RGBClass(
            (unsigned char)(unknown_palette_838a10[index].Red << 2),
            (unsigned char)(unknown_palette_838a10[index].Green << 2),
            (unsigned char)(unknown_palette_838a10[index].Blue << 2));
    }

    memmove(&unknown_palette_837e10[0], MixFileClass::Retrieve("TEMPERAT.PAL"), sizeof(unknown_palette_837e10));
    for (index = 0; index < 256; index++) {
        unknown_palette_837e10[index] = RGBClass(
            (unsigned char)(unknown_palette_837e10[index].Red << 2),
            (unsigned char)(unknown_palette_837e10[index].Green << 2),
            (unsigned char)(unknown_palette_837e10[index].Blue << 2));
    }
    unknown_palette_838110 = unknown_palette_837e10;
    unknown_palette_838710 = unknown_palette_837e10;
    unknown_palette_838410[0] = unknown_palette_837510[0];

    memmove(&unknown_palette_837810[0], MixFileClass::Retrieve("WAYPOINT.PAL"), sizeof(unknown_palette_837810));
    for (index = 0; index < 256; index++) {
        unknown_palette_837810[index] = RGBClass(
            (unsigned char)(unknown_palette_837810[index].Red << 2),
            (unsigned char)(unknown_palette_837810[index].Green << 2),
            (unsigned char)(unknown_palette_837810[index].Blue << 2));
    }

    CCFileClass vplfile("voxels.vpl");
    unknown_run_716f40(&vplfile);
    for (int i = 0; i < 256; i++) {
        unknown_palette_838d10[i] = RGBClass(unknown_voxel_colors_ae3008[i].Red, unknown_voxel_colors_ae3008[i].Green,
            unknown_voxel_colors_ae3008[i].Blue);
    }
    unknown_use_voxel_cache_839a58 = true;
    Set_Voxel_Camera_Angle(unknown_camera_angle_79acf4);
    Unknown_00717FB0(unknown_light_angle_79acf0);
    unknown_af6614 = 1;
    unknown_af6610 = 0;
    Unknown_00718060();

    unknown_drawer_8323b8 = new ConvertClass(unknown_palette_837e10, unknown_palette_837e10, unknown_surface_839950, 0x35, false);

    PaletteClass pal;
    memmove(&pal[0], MixFileClass::Retrieve("ANIM.PAL"), sizeof(pal));
    for (index = 0; index < 256; index++) {
        pal[index] = RGBClass((unsigned char)(pal[index].Red << 2), (unsigned char)(pal[index].Green << 2),
            (unsigned char)(pal[index].Blue << 2));
    }
    Unit_Draw_Convert_008323C0 = new ConvertClass(pal, unknown_palette_837e10, unknown_surface_839950, 0x35, false);

    memmove(&pal[0], MixFileClass::Retrieve("PALETTE.PAL"), sizeof(pal));
    for (index = 0; index < 256; index++) {
        pal[index] = RGBClass((unsigned char)(pal[index].Red << 2), (unsigned char)(pal[index].Green << 2),
            (unsigned char)(pal[index].Blue << 2));
    }
    unknown_drawer_8323c4 = new ConvertClass(pal, unknown_palette_837e10, unknown_surface_839950, 0x35, false);

    memmove(&pal[0], MixFileClass::Retrieve("UNITSNO.PAL"), sizeof(pal));
    for (index = 0; index < 256; index++) {
        pal[index] = RGBClass((unsigned char)(pal[index].Red << 2), (unsigned char)(pal[index].Green << 2),
            (unsigned char)(pal[index].Blue << 2));
    }
    unknown_drawer_8323b4 = new ConvertClass(pal, unknown_palette_837e10, unknown_surface_839950, 0x35, false);

    memmove(&pal[0], MixFileClass::Retrieve("CAMEO.PAL"), sizeof(pal));
    for (index = 0; index < 256; index++) {
        pal[index] = RGBClass((unsigned char)(pal[index].Red << 2), (unsigned char)(pal[index].Green << 2),
            (unsigned char)(pal[index].Blue << 2));
    }
    unknown_drawer_8323b0 = new ConvertClass(pal, unknown_palette_837e10, unknown_surface_839950, 0x35, false);

    memmove(&pal[0], MixFileClass::Retrieve("MOUSEPAL.PAL"), sizeof(pal));
    for (index = 0; index < 256; index++) {
        pal[index] = RGBClass((unsigned char)(pal[index].Red << 2), (unsigned char)(pal[index].Green << 2),
            (unsigned char)(pal[index].Blue << 2));
    }
    unknown_drawer_8323c8 = new ConvertClass(pal, unknown_palette_837e10, unknown_surface_839950, 1, false);

    unknown_drawer_8323bc = unknown_drawer_8323b4;

    CCFileClass palfile("GRFXTXT.PAL");
    if (palfile.Is_Available()) {
        unknown_grfxtxt_palette_a41670 = Load_Alloc_Data(palfile);
        palfile.Close();
        for (index = 0; index < 256; index++) {
            (*(PaletteClass *)unknown_grfxtxt_palette_a41670)[index] = RGBClass(
                (unsigned char)((*(PaletteClass *)unknown_grfxtxt_palette_a41670)[index].Red << 2),
                (unsigned char)((*(PaletteClass *)unknown_grfxtxt_palette_a41670)[index].Green << 2),
                (unsigned char)((*(PaletteClass *)unknown_grfxtxt_palette_a41670)[index].Blue << 2));
        }
    }
    if (unknown_grfxtxt_palette_a41670 != 0) {
        unknown_grfxtxt_drawer_a41678 = new ConvertClass(*(PaletteClass *)unknown_grfxtxt_palette_a41670,
            unknown_palette_837e10, unknown_surface_839950, 1, false);
    }

    CCFileClass shpfile("GRFXTXT.SHP");
    if (shpfile.Is_Available()) {
        unknown_grfxtxt_shape_a41674 = Load_Alloc_Data(shpfile);
        shpfile.Close();
    }

    Init_Expansion_Files();
    return true;
}

static void Init_Mouse()
{
    unknown_block_abd488 = (void *)Unknown_Load_Shape_00495270("MOUSE.SHP", unknown_flag_abd48c);
    if (unknown_block_abd488 != 0) {
        WWMouse->Hide_Mouse();
        Point2D pt = Point2D(0, 0);
        WWMouse->Set_Cursor(pt, (ShapeFileStruct const *)unknown_block_abd488, 0);
    }
    Map.Set_Default_Mouse(0, false);
    unknown_481fb0();
}

static bool Init_CDROM_Access()
{
    if (CDFileClass::First == 0) {
        Debug_Printf("Calling Force_CD_Available\n");
        if (!CD().Force_Available(-1)) {
            Debug_Printf("Failed to find disk (user cancel)!\n");
            return false;
        }

        int error;
        do {
            error = CDFileClass::Set_Search_Drives("?:\\");
            switch (error) {
                case 1:
                    Unknown_004955D0(&unknown_palette_837e10, 0, 0);
                    WWMessageBox(L" ").Process(StringTable::Load_String("TXT_CD_ERROR1", 0, "D:\\Ra2\\Init.CPP", 0x104D),
                        StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\Init.CPP", 0x104D), 0, 0, false);
                    return false;

                case 2:
                    Unknown_004955D0(&unknown_palette_837e10, 0, 0);
                    if (WWMessageBox(L" ").Process(StringTable::Load_String("TXT_CD_DIALOG_1", 0, "D:\\Ra2\\Init.CPP", 0x1056),
                            StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\Init.CPP", 0x1056),
                            StringTable::Load_String("TXT_CANCEL", 0, "D:\\Ra2\\Init.CPP", 0x1056), 0, false) == 1) {
                        Debug_Printf("Failed to find disk (user cancel)!\n");
                        return false;
                    }
                    break;

                default:
                    if (!CD().Force_Available(CD::RequiredCD)) {
                        Debug_Printf("Failed to find disk (user cancel)!\n");
                        return false;
                    }
                    break;
            }
        } while (error);

        CD::Set_Required_CD(-1);
        if (!VolumeCheck()) {
            Debug_Printf("VolumeCheck FAILED!!\n");
            WWMessageBox(L" ").Process(StringTable::Load_String("TXT_CD_ERROR1", 0, "D:\\Ra2\\Init.CPP", 0x106F),
                StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\Init.CPP", 0x106F), 0, 0, false);
            return false;
        }

        int disk = Unknown_0046E4C0(60);
        if (!unknown_special_a40920.IsFromInstall && disk > -1) {
            unknown_special_a40920.IsFromInstall = unknown_ini_839740.Get_Bool("Intro", "Play", true);
        }

        WolRegistryOptions options;
        options.Read_004ff200();
        if (!options.unknown_004ff2b0() && !options.unknown_004ff2d0() && !options.unknown_004ff2c0()) {
            unknown_special_a40920.EscapeMovies = true;
        }

        if (unknown_special_a40920.IsFromInstall == true) {
            CCFileClass ra2_ini("RA2.INI");
            if (disk > -1) {
                unknown_special_a40920.IsFromInstall = unknown_ini_839740.Put_Bool("Intro", "Play", false);
            }
            unknown_ini_839740.Save(ra2_ini, false);
        }
    } else {
        Debug_Printf("-CD parameter was specified. No CD init - all files must be local\n");
        CD::Set_Required_CD(-2);
    }
    return true;
}
