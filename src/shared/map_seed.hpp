// MapSeedClass and its RTTI base LoadOptionsClass.
// Base extent0x38: constructor0053B0E0 and member vector RTTI007A5844.
// MapSeed extent0x178: original allocation at00577EC5 and94-DWORD copy at00577EE1.
// Description buffer is128 wide characters at+0x78, also bounded by005791C0.
#ifndef RA2_SHARED_MAP_SEED_HPP
#define RA2_SHARED_MAP_SEED_HPP

#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif
#include "shared/vector_class.hpp"
#include "shared/string_table.hpp"
#include "shared/file_entry.hpp"
#include "shared/win32_find.hpp"
class LoadOptionsClass {
public:
    LoadOptionsClass(); // 0053B0E0
    virtual ~LoadOptionsClass(); // 0053B130 non-deleting destructor
    // Virtual interface spellings/qualifiers are hypotheses pending each method sweep.
    virtual bool Load(char const *filename);
    virtual bool Save(char const *filename,wchar_t const *description);
    virtual bool Delete_File(char const *filename);
    virtual bool Read_File_Description(FileEntryClass *entry,WIN32_FIND_DATA const *find);
    virtual wchar_t const *Load_Menu_Name() const;
    virtual wchar_t const *Save_Menu_Name() const;
    virtual wchar_t const *Delete_Menu_Name() const;
    virtual wchar_t const *Saved_Message() const;
    char Load_Dialog_0053b190();
    char Save_Dialog_0053b1b0(wchar_t *description);
    int unknown_04;
    char const *Extension; // +08: SAV in base, SED in MapSeed
    wchar_t *Description; // +0C: points into MapSeed's inline buffer
    int unknown_10;
    int unknown_14;
    unsigned char unknown_18[8]; // unidentified base storage before the evidenced vector
    DynamicVectorClass<FileEntryClass *> Files; // +20, size18; RTTI confirms element type
};
class MapSeedClass : public LoadOptionsClass {
public:
    MapSeedClass(); // 00576F50
    void Set_Default_Description_00576fe0();
    void Populate_Dialog_Parameters_00578600(HWND dialog); // operation name is a hypothesis
    void Apply_WDT_Territory_00578bc0(); // inferred operation name
    void Clamp_Parameters_00578d80();
    void Read_Dialog_Parameters_00578420(HWND dialog); // original receiver+HWND/RET4; new nonvirtual declaration
    void Randomize_00578b10();
    void Randomize_Parameters_005789f0(int map_type);
    bool Save_Or_Prompt_00578ed0(char const *filename);
    bool Load_Or_Prompt_005791a0(char const *filename);
    virtual bool Load(char const *filename); // 005791C0
    virtual bool Save(char const *filename,wchar_t const *description); // 00578F00
    virtual bool Delete_File(char const *filename); // 005794D0
    virtual bool Read_File_Description(FileEntryClass *entry,WIN32_FIND_DATA const *find); // 005794E0
    virtual wchar_t const *Load_Menu_Name() const; // 005796F0
    virtual wchar_t const *Save_Menu_Name() const; // 00579710
    virtual wchar_t const *Delete_Menu_Name() const; // 00579730
    virtual wchar_t const *Saved_Message() const; // 00579750
    int Theater; // +38, names from original INI keys in005791C0
    int MapType;
    int Resources;
    int Ruggedness;
    int Time;
    int WaterAmount;
    int NumPlayers;
    int Tiberium;
    int TiberiumLayout;
    int Vegetation;
    int UrbanPresence;
    int Width;
    int Height;
    int Accessibility;
    int RegionSize;
    int Seed;
    wchar_t DescriptionBuffer[128]; // +78
};
// Proposed complete-owner global view at0x00A6FD68 is declared in
// unknown_map_generator.hpp; MapSeedClass remains its0x178-byte SeedOptions prefix.
// Composition/original complete-owner type remain explicit hypotheses.
typedef char LoadOptionsClass_size[(sizeof(LoadOptionsClass)==0x38)?1:-1];
typedef char MapSeedClass_size[(sizeof(MapSeedClass)==0x178)?1:-1];
typedef char MapSeedClass_description_offset[(((unsigned int)&(((MapSeedClass*)0)->DescriptionBuffer))==0x78)?1:-1];
#endif
