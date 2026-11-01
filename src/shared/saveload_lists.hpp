// Objects and writers the save/load unit (0x00654A50) calls that no other header
// declares in the form Put_All 0x006558B0 and Get_All 0x00656B80 use them.
#ifndef RA2_SHARED_SAVELOAD_LISTS_HPP
#define RA2_SHARED_SAVELOAD_LISTS_HPP

#include "shared/com_persist.hpp"
#include "shared/layer.hpp"
#include "shared/object.hpp"
#include "shared/rect.hpp"

// The release build's DebugString (TibSun dbgprint.h): an empty inline whose calls emit nothing
// (a varargs inline would not be expanded by VC6).
inline void DebugString(char const *string) {}

// The unit's own misc-value writer and reader (0x00657A60, 0x00657C40).
HRESULT __fastcall Save_Misc_Values(IStream *stream);
HRESULT __fastcall Load_Misc_Values(IStream *stream);

// Red Alert's Logic (RTTI LogicClass, a LayerClass; shared/unknown_list_832470.hpp
// declares the same object without the base).
class LogicClass : public LayerClass {
};
extern LogicClass Logic;                                    // 0x00832470

// The planted bombs and the BombSight units (shared/techno.hpp's unknown_list_8322e0).
extern BombListClass BombList;                              // 0x008322E0

// Writes the static sound list at 0x00AD07D0 (0x00714A90, not recovered; Voc_Static_Load 0x00714B80
// reads it back).
HRESULT __fastcall Voc_Static_Save(IStream *stream);        // 0x00714A90

// Writes the speech markers 'SxoV'/'ExoV' (unknown_save_vox_markers 0x00716790, declared void by
// its own source; Speech_Load 0x007167D0 reads them); Put_All returns early on a failed result.
HRESULT __fastcall Speech_Save(IStream *stream);            // 0x00716790
HRESULT __fastcall Voc_Static_Load(IStream *stream);        // 0x00714B80
HRESULT __fastcall Speech_Load(IStream *stream);            // 0x007167D0

// Reads every radar event (RadarEventClass_unknown_load_all 0x0063C380).
bool __fastcall RadarEventClass_unknown_load_all(IStream *stream);

// The out-of-line object reader (TibSun's Load_Vector; 0x00654C40).
HRESULT __fastcall Skip_Objects(IStream *stream);

// The tactical view rectangle (0x006F1F30; shared/display.hpp, shared/planning.hpp).
Rect __fastcall Unknown_006F1F30();

// Writes every radar event (RadarEventClass_unknown_save_all 0x0063C310).
bool __fastcall RadarEventClass_unknown_save_all(IStream *stream);

#endif
