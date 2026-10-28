// MSChoice.cpp ("D:\Ra2\MSChoice.cpp", 0x005AFEF0-0x005B2BBF): the map
// selection screen data read from MAPSEL.INI - stages, their text lines and
// clickable selections, the screen's animations and sound effects.
//
// Names: MapStage, MapSelection, MSTextEntry, MSAnimEntry and MSSfxEntry come
// from the RTTI of their DynamicVectorClass instances. MapSelectData is a
// hypothesis for the nonpolymorphic helper (the "MapSelect:" debug strings);
// original RTTI names its MSEngine-derived owner MapSelect. Layouts
// from the constructors 0x005AFF10, 0x005B13D0, 0x005B14C0, 0x005B15B0 and
// the destructors 0x005AFFA0, 0x005B11B0. Method and member names other than
// the INI keys are hypotheses.
#ifndef RA2_SHARED_MS_CHOICE_HPP
#define RA2_SHARED_MS_CHOICE_HPP

#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/vector_class.hpp"
#include "shared/rect.hpp"
#include "shared/shape_file.hpp"
#include "shared/wstring.hpp"
#include "shared/wide_string.hpp"
#include "shared/string_table.hpp"
#include "shared/ini_class.hpp"

// One text line of a stage: "x,y,unknown,text" (0x10 bytes).
class MSTextEntry {
public:
    MSTextEntry(WideString const &line);                // 0x005B13D0

    int X;                      // +0x00
    int Y;                      // +0x04
    int unknown_08;             // +0x08
    WideString Text;            // +0x0C
};

// One "name,a,b,c" animation line of the screen (0x10 bytes).
class MSAnimEntry {
public:
    MSAnimEntry(Wstring const &line);                   // 0x005B14C0

    Wstring Name;               // +0x00
    int unknown_04;             // +0x04
    int unknown_08;             // +0x08
    int unknown_0C;             // +0x0C
};

// One [Sounds] entry: key name, "file,volume%" (0x10 bytes).
class MSSfxEntry {
public:
    MSSfxEntry(Wstring const &name, Wstring const &line);   // 0x005B15B0
    ~MSSfxEntry();                                      // 0x005B16C0
    void Play();                                        // 0x005B16D0 empty in this build

    Wstring Name;               // +0x00
    bool unknown_04;            // +0x04
    int unknown_08;             // +0x08
    int Volume;                 // +0x0C 0..255 (255 unless given)
};

// A clickable choice on a stage: the [stage] key 0..255 and the value
// (0x0C bytes from operator new in the MapStage loader).
class MapSelection {
public:
    MapSelection(Wstring const &name, char key) : Name(name), Key(key) {}

    Wstring Name;               // +0x00
    char Key;                   // +0x04
    int unknown_08;             // +0x08 not set by the loader
};

// One stage of the map selection (0x6C bytes from operator new).
class MapStage {
public:
    MapStage(INIClass &ini, Wstring const &section);    // 0x005B0A20 (loads the stage)
    ~MapStage();                                        // 0x005B11B0

    MapSelection *Find_Selection(char const *name) const;   // 0x005B12D0 case-insensitive
    Wstring Selection_Name(char key) const;            // 0x005B1380

    // Member names other than Name follow the MAPSEL.INI keys the loader reads.
    Wstring Name;               // +0x00 section name
    Wstring Scenario;           // +0x04 "Scenario"
    Wstring MapVQ;              // +0x08 "MapVQ"
    Wstring VoiceOver;          // +0x0C "VoiceOver"
    WideString Description;     // +0x10 "Description" (string-table label)
    int OverlayCount;           // +0x14 "Overlays" entries read (0..2)
    Wstring Overlays[2];        // +0x18 "Overlays"
    Wstring ClickMap;           // +0x20 "ClickMap"
    DynamicVectorClass<Point2D> Targets;            // +0x24 "Targets" count,x,y,...
    DynamicVectorClass<MSTextEntry *> Texts;        // +0x3C "Text1".."Text7"
    DynamicVectorClass<MapSelection *> Selections;  // +0x54 keys "0".."255"
};

// The map selection screen (0x5C bytes).
class MapSelectData {
public:
    MapSelectData();                                        // 0x005AFF10
    ~MapSelectData();                                       // 0x005AFFA0

    bool Load(Wstring const &section);                  // 0x005B0030 (MAPSEL.INI)
    void Clear();                                       // 0x005B0730
    MapStage *Find_Stage(Wstring const &name) const;    // 0x005B07F0 by Name
    MapStage *Find_Stage_04(Wstring const &name) const; // 0x005B08A0 by Scenario
    MapStage *Get_Stage(unsigned short index) const;    // 0x005B0950
    int Stage_Index(MapStage *stage);                   // 0x005B0970
    MSSfxEntry *Find_Sound(Wstring const &name) const;  // 0x005B0980

    DynamicVectorClass<MapStage *> Stages;              // +0x00
    Rect TextRect;                                      // +0x18 default 0,0,640,400
    Wstring Palette;                                    // +0x28
    DynamicVectorClass<MSAnimEntry *> Anims;            // +0x2C
    DynamicVectorClass<MSSfxEntry *> Sounds;            // +0x44
};

#include "shared/sound_available.hpp"
#include "shared/debug_printf.hpp"
// Decimal text of a number (0x0076F580, sprintf "%d"; result through ECX).
Wstring __fastcall Int_To_Wstring(int value);
// Wstring.cpp helpers used by the MapStage loader (both return through ECX):
// "text" + string (0x0076F6B0) and the 16-bit copy of a string (0x007711C0;
// name is a hypothesis).
Wstring __fastcall operator+(char const *left, Wstring const &right);
WideString __fastcall Wstring_To_Wide(Wstring const &string);

#endif
