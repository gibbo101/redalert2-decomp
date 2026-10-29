// Rules enumerations the INI readers return (CCINIClass::Get_SpeedType
// 0x0046C400, Get_LandType 0x0046A970, Get_CategoryType 0x00469EA0,
// Get_Level 0x0046C9D0). Only the values recovered so far.
#ifndef RA2_SHARED_INI_ENUMS_HPP
#define RA2_SHARED_INI_ENUMS_HPP

// Movement types, named Foot, Track, Wheel, Hover, Winged, Float,
// Amphibious, FloatBeach (table 0x007D38A8); names of the values are not
// recovered.
enum SpeedType {
    SPEED_NONE = -1
};

// Land types Clear, Road, Water, Rock, ... (names 0x007D3878).
enum LandType {
    LAND_CLEAR
};

// Unit categories Soldier, Civilian, VIP, Recon, AFV, IFV, LRFS, Support,
// Transport, AirPower, AirLift ({description, name} pairs at 0x007D17E0).
enum CategoryType {
    CATEGORY_NONE = -1,
    CATEGORY_SOLDIER,
    CATEGORY_COUNT = 11
};
struct CategoryNameStruct {
    char const *Description;    // "VIP/Agent", "Armored Fighting Vehicle", ...
    char const *Name;           // "VIP", "AFV", ... (the INI name)
};
extern CategoryNameStruct CategoryNames[CATEGORY_COUNT];             // 0x007D17E0
char const *__fastcall Description_From_Category(CategoryType category);   // 0x00468EA0
char const *__fastcall Name_From_Category(CategoryType category);   // 0x00468EC0
CategoryType __fastcall Category_From_Name(char const *name);       // 0x00468EE0

// Crate powerups Money, Unit, HealBase, Cloak, ... Pod (names 0x0079DE54;
// CCINIClass::Get_CrateType 0x0046AE30, RulesClass's [CrateRules]).
enum CrateType {
    CRATE_MONEY
};
extern char const *CrateNames[];                            // 0x0079DE54

// A three-level setting named None, Normal, Strong (name table 0x007D1A98,
// read by CCINIClass::Get_Level 0x0046C9D0); TechnoTypeClass reads VHPScan
// with it.
enum LevelType {
    LEVEL_NONE,
    LEVEL_NORMAL,
    LEVEL_STRONG
};

#endif
