// void __fastcall Unknown_0063B090(UnknownIDSource *scenario) -- 0x0063B090 (Restate.cpp; TibSun Restate_Mission)
// Restates the mission: shows the scenario's [Briefing] text from MISSION.INI (or Brief:Error)
// in dialog 0x10C and waits until it is closed or the game must quit.
#define GENERIC_LIST_IMPLEMENT_CONSTRUCTOR  // the unit calls GenericList::GenericList 0x00490E80 (shared/ini_class.hpp)
#define INDEX_DECLARE_CONSTRUCTOR          // and IndexClass<int, INISection *>::IndexClass 0x004910C0
#include "shared/cc_file_class.hpp"
#include "shared/ccini_class.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/dialog_create.hpp"
#include "shared/string_table.hpp"
#include "shared/keyboard.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
// @ref ??0CCFileClass@@QAE@XZ=00468fd0
// @ref ?Close@CCFileClass@@UAEXXZ=004691f0
// @ref ?Set_Name@CDFileClass@@UAEPBDPBD@Z=00470150
// @ref ?Is_Available@CCFileClass@@UAE_NH@Z=004691a0
// @ref ?Load@CCINIClass@@QAEHAAVFileClass@@_N1@Z=004696b0
// @ref ?Find_Section@INIClass@@QBEPAUINISection@1@PBD@Z=0050c9b0
// @ref ?Find_Entry@INIClass@@QBEPAUINIEntry@1@PBD0@Z=0050cca0
// @ref ?Get_String@INIClass@@QBEHPBD00PADH@Z=0050e9a0
// @ref ??1INIClass@@UAE@XZ=0050b8d0
// @ref ??1Buffer@@QAE@XZ=00438410
// @ref ??1BufferIOFileClass@@UAE@XZ=0042f350
// @ref ??0?$IndexClass@HPAUINISection@INIClass@@@@QAE@XZ=004910c0
// @ref ??0GenericList@@QAE@XZ=00490e80
// @ref ??_7CCINIClass@@6B@=0079aae4
// @ref ??_7INIClass@@6B@=0079aaec
// @ref ??_7CCFileClass@@6B@=0079a6a0
// @ref ??_7CDFileClass@@6B@=0079a658
// @ref ??_7?$List@PAUINISection@INIClass@@@@6B@=0079aaec
// @ref ??_G?$List@PAUINISection@INIClass@@@@UAEPAXI@Z=0040e300
// @ref ??_7GenericList@@6B@=0079aaf4
// @ref ??_GGenericList@@UAEPAXI@Z=0040e220
// @ref ??_7GenericNode@@6B@=0079aafc
// @ref ??_GGenericNode@@UAEPAXI@Z=0040e1d0
// @ref ??_GINIClass@@UAEPAXI@Z=004deef0
// @ref ??_GCCINIClass@@UAEPAXI@Z=0040e2e0
// @ref ??_GCCFileClass@@UAEPAXI@Z=004019a0
// @ref ??_GCDFileClass@@UAEPAXI@Z=00401950
// @ref ?File_Name@RawFileClass@@UBEPBDXZ=00401940
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ?unknown_create_dialog_5ff610@@YIPAUHWND__@@HP6GHPAU1@IIJ@ZH@Z=005ff610
// @ref ?unknown_dialog_5ff7c0@@YIXPAUHWND__@@@Z=005ff7c0
// @ref ?unknown_dialog_5ff6e0@@YIXPAUHWND__@@@Z=005ff6e0
// @ref ?unknown_6000d0@@YA_NXZ=006000d0
// @ref __imp__SetWindowLongA@12=0079a488
// @ref ?Clear@WWKeyboardClass@@QAEXXZ=005329f0
// @ref ?WWKeyboard@@3PAVWWKeyboardClass@@A=00832468
// @ref ?Flag_To_Redraw@GScreenClass@@UAEXH@Z=004e09a0
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_flag_a40d04@@3_NA=00a40d04
// @ref ?unknown_flag_a40d44@@3_NA=00a40d44
// @ref ?unknown_string_83c55c@@3PADA=0083c55c
// @ref ?Restate_Ini_Name_007ee578@@3QBDB=007ee578
// @ref ?Restate_Section_Entry_007ee57c@@3QBDB=007ee57c
// @ref ??_C@_0BD@OOJI@D?3?2Ra2?2Restate?4cpp?$AA@=007ee5a4
// @ref ??_C@_0M@CCIA@Brief?3Error?$AA@=007ee598
// @ref ?Restate_Text_00ab66e8@@3PBGB=00ab66e8
// @ref ?Restate_Dialog_Proc_0063b270@@YGHPAUHWND__@@IIJ@Z=0063b270

extern char const *const Restate_Ini_Name_007ee578;        // "MISSION.INI"
extern char const *const Restate_Section_Entry_007ee57c;   // "Briefing"
extern wchar_t const *Restate_Text_00ab66e8;               // the text dialog 0x10C shows

int __stdcall Restate_Dialog_Proc_0063b270(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

void __fastcall Unknown_0063B090(UnknownIDSource *scenario)
{
    bool old = unknown_flag_a40d04;
    unknown_flag_a40d04 = false;

    CCFileClass file;
    CCINIClass ini;

    file.Close();
    file.Set_Name(Restate_Ini_Name_007ee578);
    if (file.Is_Available()) {
        ini.Load(file, false, false);

        if (ini.Is_Present(scenario->FileName, Restate_Section_Entry_007ee57c)) {
            char buffer[256];
            ini.Get_String(scenario->FileName, Restate_Section_Entry_007ee57c, unknown_string_83c55c, buffer, sizeof(buffer));
            Restate_Text_00ab66e8 = StringTable::Load_String(buffer, 0, "D:\\Ra2\\Restate.cpp", 0x87);
        } else {
            Restate_Text_00ab66e8 = StringTable::Load_String("Brief:Error", 0, "D:\\Ra2\\Restate.cpp", 0x8A);
        }

        HWND dialog = unknown_create_dialog_5ff610(0x10C, Restate_Dialog_Proc_0063b270, 0);
        unknown_flag_a40d44 = true;
        WWKeyboard->Clear();
        if (dialog) {
            int result;
            SetWindowLongA(dialog, 8, (LONG)&result);
            unknown_dialog_5ff7c0(dialog);
            result = 0;
            while (true) {
                if (unknown_6000d0()) {
                    result = 0x423;
                    break;
                }
                if (result != 0) {
                    break;
                }
            }
            unknown_dialog_5ff6e0(dialog);
        }
        WWKeyboard->Clear();
        unknown_flag_a40d44 = unknown_id_source_a3d290->unknown_2306;
        Map.Flag_To_Redraw(2);
    }

    unknown_flag_a40d04 = old;
}
