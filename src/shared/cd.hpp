// CD: asks the player for a game disk and swaps the per-disk mixfiles
// (Westwood's CD.CPP, "D:\Ra2\CD.CPP").
//
// Name from RTTI (.?AVCD@@, vtable 0x0079D868, three slots). CCFileClass::
// Error (0x00469000) builds a CD on the stack and calls slot 0 with
// RequiredCD; the object holds only the vptr and the theme to restart.
//
// Slot names are hypotheses: slot 0 (0x0046E4F0) returns at once for disk -2
// or when IsLocal is set, else resets LastTheme and calls 0x004985C0; slot 1
// (0x0046E520) shows the insert-disk dialog for the disk (TXT_CD_DIALOG_*)
// with the music stopped and the mouse visible, and returns the answer;
// slot 2 (0x0046E750) logs "Swapping to disk %d" and recreates the five
// per-disk mixfiles.
#ifndef RA2_SHARED_CD_HPP
#define RA2_SHARED_CD_HPP

#include "shared/theme.hpp"
#include "shared/string_table.hpp"

class CCFileClass;
class PKey;
template <class T> class MixFileClass;

class CD {
public:
    CD() {}
    virtual bool Force_Available(int cd);      // slot 0, 0x0046E4F0
    virtual bool Insert_Disk(int cd);          // slot 1, 0x0046E520
    virtual bool Swap_Disk(int cd);            // slot 2, 0x0046E750

    // Defined in another unit (0x004985C0, __thiscall, ret 4): the search for
    // the disk that Force_Available falls back to (hypothesis).
    bool Unknown_004985C0(int cd);

    ThemeType LastTheme;    // +0x04 theme to restart after the dialog, THEME_NONE when none

    // Records the disk the next file needs (-2 when IsLocal).
    static void __fastcall Set_Required_CD(int cd);   // 0x0046E4D0

    static int RequiredCD;  // 0x007D20E0 disk the current file needs (initially -1; -2: any)
    static bool IsLocal;    // 0x00850828 (hypothesis: all files are on the hard disk)
};

// The per-disk mixfiles Swap_Disk recreates (names hypotheses from the
// archive names it opens).
extern MixFileClass<CCFileClass> *AudioMix;    // 0x00831444 AUDIO.MIX (the audio library's archive)
extern MixFileClass<CCFileClass> *MoviesMix;   // 0x008374D4 MOVIES%02d.MIX
extern MixFileClass<CCFileClass> *ThemeMix;    // 0x00831448 THEME.MIX
extern MixFileClass<CCFileClass> *MultiMix;    // 0x00837498 MULTI.MIX
extern MixFileClass<CCFileClass> *MapsMix;     // 0x008374F4 MAPS%02d.MIX
extern MixFileClass<CCFileClass> *MainMix;     // 0x008374DC MAIN.MIX
extern MixFileClass<CCFileClass> *unknown_mix_8374f0;   // 0x008374F0 (released by 0x0051A270, reopened by 0x0051A2B0)
// The expansion mixfiles Init_Expansion_Files opens (0x00837450).
extern DynamicVectorClass<MixFileClass<CCFileClass> *> unknown_expansion_mixes_837450;
extern PKey FastKey;                           // 0x00839010 key the mixfiles are opened with

// Checks the volume of the game disk (its debug strings name it
// "VolumeCheck()"); true when the disk is present (hypothesis).
bool VolumeCheck();                            // 0x00715090
// Modal dialog with the text; false when the player cancels (hypothesis).
bool __fastcall Unknown_00600C80(wchar_t const *text);   // 0x00600C80
// Get_CD_Index for the current CD drive (hypothesis).
int __fastcall Unknown_0046E4C0(int timeout);  // 0x0046E4C0
#include "shared/debug_printf.hpp"

#endif
