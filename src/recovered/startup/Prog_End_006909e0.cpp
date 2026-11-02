// void __cdecl Prog_End() (0x006909E0): the program's exit cleanup, registered with atexit by
// WinMain and reached from the shutdown path 0x00691320. Frees the palettes, converters,
// surfaces, mixfiles, INI databases, lists and libraries the start-up made, then stops the
// mouse thread.
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/vector_class.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/session_state.hpp"
#include "shared/color_scheme.hpp"
#include "shared/movie_list.hpp"
#include "shared/command.hpp"
#include "shared/ccini_class.hpp"
#include "shared/mouse.hpp"
#include "shared/radar.hpp"
#include "shared/tab.hpp"
#include "shared/mouse_class.hpp"
#include "shared/map_view.hpp"
#include "shared/blit.hpp"
#include "shared/text_print.hpp"
#include "shared/convert.hpp"
#include "shared/light_convert.hpp"
#include "shared/gadget.hpp"
#include "shared/wwmouse.hpp"
#include "shared/unit_type.hpp"
#include "shared/building_type_class.hpp"
#include "shared/surface.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/cd.hpp"
#include "shared/tactical.hpp"
#include "shared/keyboard.hpp"
#include "shared/buffer.hpp"
#include "shared/rules.hpp"
#include "shared/id_source.hpp"
#include "shared/theme.hpp"
#include "shared/lobby.hpp"
#include "shared/com_registration.hpp"
#include "shared/cd_file_class.hpp"
#include "shared/win32_api.hpp"
#include "shared/com_api.hpp"
#include "shared/crt_memory.hpp"

// @ref ?Unit_Draw_Convert_008323C0@@3PAVConvertClass@@A=008323c0
// @ref ?Unknown_00521CB0@@YAXXZ=00521cb0
// @ref ?Unknown_00522930@@YAXXZ=00522930
// @ref ?Unknown_00562EA0@MapClass@@QAEXXZ=00562ea0
// @ref ?Unknown_0059D900@@YAXXZ=0059d900
// @ref ?Unknown_005BB5A0@@YAXXZ=005bb5a0
// @ref ?Unknown_005D5F40@@YAXXZ=005d5f40
// @ref ?Unknown_005DDB40@@YAXXZ=005ddb40
// @ref ?Unknown_005EAC20@@YAXXZ=005eac20
// @ref ?Unknown_00603FA0@@YAXXZ=00603fa0
// @ref ?Unknown_00613E40@@YAXXZ=00613e40
// @ref ?Unknown_006E7A70@ThemeClass@@QAEXXZ=006e7a70
// @ref ?Unknown_006F57E0@@YAXXZ=006f57e0
// @ref ?Unknown_00714860@@YAXXZ=00714860
// @ref ?unknown_active_object_abd484@@3KA=00abd484
// @ref ?unknown_block_a52eb0@@3PAXA=00a52eb0
// @ref ?unknown_block_a52eb4@@3PAXA=00a52eb4
// @ref ?unknown_block_a52eb8@@3PAXA=00a52eb8
// @ref ?unknown_block_a52ebc@@3PAXA=00a52ebc
// @ref ?unknown_block_a6e38c@@3PAXA=00a6e38c
// @ref ?unknown_buffer_a35e20@@3PAVBuffer@@A=00a35e20
// @ref ?unknown_drawer_8323b0@@3PAVConvertClass@@A=008323b0
// @ref ?unknown_drawer_8323b4@@3PAVConvertClass@@A=008323b4
// @ref ?unknown_grfxtxt_drawer_a41678@@3PAVConvertClass@@A=00a41678
// @ref ?unknown_grfxtxt_palette_a41670@@3PAXA=00a41670
// @ref ?unknown_grfxtxt_shape_a41674@@3PAXA=00a41674
// @ref ?unknown_handle_abd47c@@3PAXA=00abd47c
// @ref ?unknown_handle_abd480@@3PAXA=00abd480
// @ref ?unknown_language_mix_8374bc@@3PAVMixFileClass@@A=008374bc
// @ref ?unknown_mix_8374d8@@3PAVMixFileClass@@A=008374d8
// @ref ?unknown_mix_8374fc@@3PAVMixFileClass@@A=008374fc
// @ref ?unknown_mixes_837480@@3V?$DynamicVectorClass@PAVMixFileClass@@@@A=00837480
// @ref ?unknown_surface_839968@@3PAVSurface@@A=00839968
// @ref ?unknown_theater_mix_8374c0@@3PAVMixFileClass@@A=008374c0
// @ref ?unknown_theater_mix_8374c4@@3PAVMixFileClass@@A=008374c4
// @ref ?unknown_theater_mix_8374c8@@3PAVMixFileClass@@A=008374c8
// @ref ?unknown_theater_mix_8374cc@@3PAVMixFileClass@@A=008374cc
// @ref ?unknown_theater_mix_8374d0@@3PAVMixFileClass@@A=008374d0
// @ref __imp__RevokeActiveObject@8=0079a354
// @ref ?Kill_Mouse_Thread@@YIXXZ=007719a0
// Template copies the unit emits (UnknownIDSource's lists; radar.hpp's and map.hpp's list members),
// bound to the kept copies.
// @ref ??_7?$VectorClass@PAVTechnoTypeClass@@@@6B@=0079da14
// @ref ??_7?$VectorClass@H@@6B@=0079d9d4
// @ref ??_E?$DynamicVectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@UAEPAXI@Z=00634f90
// @ref ??_7?$VectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@6B@=007a8824
// @ref ??8?$VectorClass@H@@UBE_NABV0@@Z=0046d070
// @ref ?Resize@?$VectorClass@H@@UAE_NHPBH@Z=0046d0b0
// @ref ?Clear@?$VectorClass@H@@UAEXXZ=0046d160
// @ref ?ID@?$VectorClass@H@@UAEHABH@Z=0046d190
// @ref ?ID@?$VectorClass@H@@UAEHPBH@Z=0046d1d0
// @ref ?Fetch@?$VectorClass@H@@UBEHH@Z=0046ccd0
// @ref ??8?$VectorClass@PAVTechnoTypeClass@@@@UBE_NABV0@@Z=0046d400
// @ref ?Resize@?$VectorClass@PAVTechnoTypeClass@@@@UAE_NHPBQAVTechnoTypeClass@@@Z=0046d440
// @ref ?Clear@?$VectorClass@PAVTechnoTypeClass@@@@UAEXXZ=0046d4f0
// @ref ?ID@?$VectorClass@PAVTechnoTypeClass@@@@UAEHABQAVTechnoTypeClass@@@Z=0046d520
// @ref ?ID@?$VectorClass@PAVTechnoTypeClass@@@@UAEHPBQAVTechnoTypeClass@@@Z=0046d560
// @ref ?Fetch@?$VectorClass@PAVTechnoTypeClass@@@@UBEPAVTechnoTypeClass@@H@Z=0046cd30
// @ref ??8?$VectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@UBE_NABV0@@Z=00634c40
// @ref ?Resize@?$VectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@UAE_NHPBU?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@Z=00634ca0
// @ref ?Clear@?$VectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@UAEXXZ=00634da0
// @ref ?ID@?$VectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@UAEHABU?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@Z=00634dd0
// @ref ?ID@?$VectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@UAEHPBU?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@Z=00634e20
// @ref ?Fetch@?$VectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@UBE?AU?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@H@Z=00634c10
// @ref ??_G?$VectorClass@H@@UAEPAXI@Z=0046da70
// @ref ??_G?$VectorClass@PAVTechnoTypeClass@@@@UAEPAXI@Z=0046dac0
// @ref ??_ESubzoneTrackingStruct@@QAEPAXI@Z=0040afa0
// @ref ??_7?$VectorClass@USubzoneConnectionStruct@@@@6B@=0079a76c
// @ref ??8?$VectorClass@USubzoneConnectionStruct@@@@UBE_NABV0@@Z=0040b070
// @ref ?Resize@?$VectorClass@USubzoneConnectionStruct@@@@UAE_NHPBUSubzoneConnectionStruct@@@Z=0040b0b0
// @ref ?Clear@?$VectorClass@USubzoneConnectionStruct@@@@UAEXXZ=0040b1a0
// @ref ?ID@?$VectorClass@USubzoneConnectionStruct@@@@UAEHABUSubzoneConnectionStruct@@@Z=0040b1d0
// @ref ?ID@?$VectorClass@USubzoneConnectionStruct@@@@UAEHPBUSubzoneConnectionStruct@@@Z=0040b210
// @ref ?Fetch@?$VectorClass@USubzoneConnectionStruct@@@@UBE?AUSubzoneConnectionStruct@@H@Z=0040b050
// @ref ??_G?$VectorClass@USubzoneConnectionStruct@@@@UAEPAXI@Z=0040b230
// @ref ??_G?$VectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@UAEPAXI@Z=00635040


// (Query_DLL_Version 0x0049EE00 declares it with a strict HMODULE.)
WIN32_IMPORT BOOL WINAPI FreeLibrary(HANDLE module);

void Unknown_Free_Screen_Surfaces_0068E1C0();
void __fastcall Delete_All_Objects_00519960();
void RadarEventClass_unknown_delete_all_63b890();
void __fastcall Unknown_Free_All_Art_006F1D20();
void Speech_Free_All();
void Audio_Shutdown();
void Unknown_006F9D90();
void __cdecl CopyProtection_Shutdown_00491b00();

void __cdecl Prog_End()
{
    unknown_flag_a40958 = false;
    if (unknown_grfxtxt_shape_a41674) {
        delete unknown_grfxtxt_shape_a41674;
        unknown_grfxtxt_shape_a41674 = 0;
    }
    if (unknown_grfxtxt_drawer_a41678) {
        delete unknown_grfxtxt_drawer_a41678;
        unknown_grfxtxt_drawer_a41678 = 0;
    }
    if (unknown_grfxtxt_palette_a41670) {
        delete unknown_grfxtxt_palette_a41670;
        unknown_grfxtxt_palette_a41670 = 0;
    }
    unknown_session_a3d298.Free_Scenario_Descriptions();

    while (ColorSchemes.Count()) {
        delete ColorSchemes[0];
    }
    ColorSchemes.Clear();

    Delete_All_Objects_00519960();

    while (unknown_names_a71050.Count()) {
        free((void *)unknown_names_a71050[0]);
        unknown_names_a71050.Delete(0);
    }
    unknown_names_a71050.Clear();

    for (int index = 0; index < unknown_commands_832358.Count(); index++) {
        delete unknown_commands_832358[index];
    }
    unknown_commands_832358.Clear();

    if (unknown_ini_8396d0) {
        delete unknown_ini_8396d0;
        unknown_ini_8396d0 = 0;
    }
    unknown_ini_8397a0.Clear();
    ArtINI.Clear();
    unknown_ini_839860.Clear();
    unknown_ini_8396e0.Clear();
    unknown_ini_839740.Clear();
    unknown_ini_839740.Clear();
    Unknown_005DDB40();
    Unknown_00521CB0();

    if (WWMouse) {
        delete WWMouse;
        WWMouse = 0;
    }
    Map.unknown_slot23();
    Map.Unknown_00631E40();
    Unknown_Free_Screen_Surfaces_0068E1C0();
    if (ABufferPtr) {
        delete ABufferPtr;
        ABufferPtr = 0;
    }
    if (ZBufferPtr) {
        delete ZBufferPtr;
        ZBufferPtr = 0;
    }
    if (BitText) {
        delete BitText;
        BitText = 0;
    }
    if (unknown_drawer_8323b8) {
        delete unknown_drawer_8323b8;
        unknown_drawer_8323b8 = 0;
    }
    if (Unit_Draw_Convert_008323C0) {
        delete Unit_Draw_Convert_008323C0;
        Unit_Draw_Convert_008323C0 = 0;
    }
    if (unknown_drawer_8323c4) {
        delete unknown_drawer_8323c4;
        unknown_drawer_8323c4 = 0;
    }
    if (unknown_drawer_8323b4) {
        delete unknown_drawer_8323b4;
        unknown_drawer_8323b4 = 0;
    }
    if (unknown_convert_8323c8) {
        delete (ConvertClass *)unknown_convert_8323c8;
        unknown_convert_8323c8 = 0;
    }
    if (unknown_drawer_8323cc) {
        delete unknown_drawer_8323cc;
        unknown_drawer_8323cc = 0;
    }
    if (unknown_drawer_8323b0) {
        delete unknown_drawer_8323b0;
        unknown_drawer_8323b0 = 0;
    }
    if (unknown_drawer_ad0608) {
        delete unknown_drawer_ad0608;
        unknown_drawer_ad0608 = 0;
    }
    if (unknown_surface_ad0604) {
        delete unknown_surface_ad0604;
        unknown_surface_ad0604 = 0;
    }
    if (unknown_cloak_surface_8502a0) {
        delete unknown_cloak_surface_8502a0;
        unknown_cloak_surface_8502a0 = 0;
    }
    if (unknown_building_depth_shape_85029c) {
        delete unknown_building_depth_shape_85029c;
        unknown_building_depth_shape_85029c = 0;
    }
    Map.Unknown_00562EA0();

    for (int light = 0; light < unknown_LightConvertClass_list_00832398.Count(); light++) {
        delete unknown_LightConvertClass_list_00832398[light];
    }
    unknown_LightConvertClass_list_00832398.Clear();

    if (unknown_theater_mix_8374c0) {
        delete unknown_theater_mix_8374c0;
        unknown_theater_mix_8374c0 = 0;
    }
    if (unknown_theater_mix_8374c4) {
        delete unknown_theater_mix_8374c4;
        unknown_theater_mix_8374c4 = 0;
    }
    if (unknown_theater_mix_8374c8) {
        delete unknown_theater_mix_8374c8;
        unknown_theater_mix_8374c8 = 0;
    }
    if (unknown_theater_mix_8374cc) {
        delete unknown_theater_mix_8374cc;
        unknown_theater_mix_8374cc = 0;
    }
    if (unknown_theater_mix_8374d0) {
        delete unknown_theater_mix_8374d0;
        unknown_theater_mix_8374d0 = 0;
    }
    if (unknown_block_a6e38c) {
        delete unknown_block_a6e38c;
        unknown_block_a6e38c = 0;
    }
    if (unknown_block_a52eb0) {
        delete unknown_block_a52eb0;
        unknown_block_a52eb0 = 0;
    }
    if (unknown_block_a52eb4) {
        delete unknown_block_a52eb4;
        unknown_block_a52eb4 = 0;
    }
    if (unknown_block_a52eb8) {
        delete unknown_block_a52eb8;
        unknown_block_a52eb8 = 0;
    }
    if (unknown_block_a52ebc) {
        delete unknown_block_a52ebc;
        unknown_block_a52ebc = 0;
    }
    if (unknown_surface_839968) {
        delete unknown_surface_839968;
        unknown_surface_839968 = 0;
    }
    if (MoviesMix) {
        delete MoviesMix;
        MoviesMix = 0;
    }
    if (unknown_mix_8374d8) {
        delete unknown_mix_8374d8;
        unknown_mix_8374d8 = 0;
    }
    if (MainMix) {
        delete MainMix;
        MainMix = 0;
    }
    if (ConquerMix) {
        delete ConquerMix;
        ConquerMix = 0;
    }
    if (CameoMix) {
        delete CameoMix;
        CameoMix = 0;
    }
    while (unknown_expansion_mixes_837450.Count() > 0) {
        delete unknown_expansion_mixes_837450[0];
        unknown_expansion_mixes_837450.Delete(0);
    }
    if (unknown_cache_mix_8374e8) {
        delete unknown_cache_mix_8374e8;
        unknown_cache_mix_8374e8 = 0;
    }
    if (unknown_local_mix_8374ec) {
        delete unknown_local_mix_8374ec;
        unknown_local_mix_8374ec = 0;
    }
    if (unknown_mix_8374f0) {
        delete unknown_mix_8374f0;
        unknown_mix_8374f0 = 0;
    }
    if (unknown_mix_8374f8) {
        delete unknown_mix_8374f8;
        unknown_mix_8374f8 = 0;
    }
    if (unknown_mix_8374fc) {
        delete unknown_mix_8374fc;
        unknown_mix_8374fc = 0;
    }
    while (unknown_mixes_837480.Count() > 0) {
        delete unknown_mixes_837480[0];
        unknown_mixes_837480.Delete(0);
    }
    if (MapsMix) {
        delete MapsMix;
        MapsMix = 0;
    }
    if (MultiMix) {
        delete MultiMix;
        MultiMix = 0;
    }
    if (unknown_side_mix_837500) {
        delete unknown_side_mix_837500;
        unknown_side_mix_837500 = 0;
    }
    if (unknown_side_nc_mix_837504) {
        delete unknown_side_nc_mix_837504;
        unknown_side_nc_mix_837504 = 0;
    }
    if (unknown_ra2_mix_8374b8) {
        delete unknown_ra2_mix_8374b8;
        unknown_ra2_mix_8374b8 = 0;
    }
    if (unknown_language_mix_8374bc) {
        delete unknown_language_mix_8374bc;
        unknown_language_mix_8374bc = 0;
    }
    if (unknown_tactical_83996c) {
        delete unknown_tactical_83996c;
        unknown_tactical_83996c = 0;
    }
    RadarEventClass_unknown_delete_all_63b890();
    Map.unknown_slot50();
    Unknown_00603FA0();
    Unknown_0059D900();
    Unknown_005D5F40();
    Unknown_005EAC20();
    Unknown_00613E40();
    Unknown_Free_All_Art_006F1D20();
    Unknown_006F57E0();
    Unknown_00535970();
    MouseClass::Unknown_0059FEF0();
    Shutdown_Network_005bc4d0();
    Unknown_00714860();
    Speech_Free_All();
    CDFileClass::Clear_Search_Drives();
    if (WWKeyboard) {
        delete WWKeyboard;
        WWKeyboard = 0;
    }
    Unknown_005BB5A0();
    if (unknown_buffer_a35e20) {
        delete unknown_buffer_a35e20;
        unknown_buffer_a35e20 = 0;
    }
    if (Rules) {
        delete Rules;
        Rules = 0;
    }
    if (unknown_id_source_a3d290) {
        delete unknown_id_source_a3d290;
        unknown_id_source_a3d290 = 0;
    }

    for (int com = 0; com < unknown_unsigned_long_list_00abd428.Count(); com++) {
        CoRevokeClassObject(unknown_unsigned_long_list_00abd428[com]);
    }
    unknown_unsigned_long_list_00abd428.Clear();
    RevokeActiveObject(unknown_active_object_abd484, 0);
    if (unknown_instance_00851ca8) {
        FreeLibrary(unknown_instance_00851ca8);
    }
    if (unknown_handle_abd480) {
        CloseHandle(unknown_handle_abd480);
        unknown_handle_abd480 = 0;
    }
    if (unknown_handle_abd47c) {
        CloseHandle(unknown_handle_abd47c);
        unknown_handle_abd47c = 0;
    }
    Unknown_00522930();
    Theme.Unknown_006E7A70();
    Audio_Shutdown();
    Unknown_006F9D90();
    CopyProtection_Shutdown_00491b00();
    Kill_Mouse_Thread();
}
