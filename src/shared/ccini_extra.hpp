// Game types the CCINIClass readers and writers use, declared only as far
// as CCINI.cpp needs them (fields and members not listed are not
// recovered). Proposed alongside shared/ccini_class.hpp; it pulls in
// shared/object_type.hpp, so a unit including it also gets the
// unknown_geometry header statics.
//
// Find_Index and From_Name (static, __fastcall) return the index in the
// type's global list of the type whose ID equals the name ignoring case,
// or -1.
#ifndef SHARED_CCINI_EXTRA_HPP
#define SHARED_CCINI_EXTRA_HPP

#include "shared/object_type.hpp"
#include "shared/hsv_class.hpp"
#include "shared/color_scheme.hpp"
#include "shared/ini_enums.hpp"
#include "shared/abilities.hpp"

// The techno types and their lists (TechnoTypes, InfantryTypes, UnitTypes,
// AircraftTypes, BuildingTypes) and the From_Name lookups.
#include "shared/infantry_type.hpp"
#include "shared/unit_type.hpp"
#include "shared/aircraft_type.hpp"
#include "shared/building_type.hpp"

// House (country) types and sides: shared/house_type.hpp, shared/side.hpp.
#include "shared/house_type.hpp"
#include "shared/house_screen.hpp"   // HouseClass, Houses (padded view; see house.hpp)
#include "shared/side.hpp"

// SpeedType, LandType, CategoryType and LevelType: shared/ini_enums.hpp.
char const *__fastcall Name_From_Speed(SpeedType speed);   // 0x00482F60 ("<none>" when out of range)
SpeedType __fastcall Speed_From_Name(char const *name);    // 0x00482F20 (-1 when unknown)

// Layers, named Underground, Surface, Ground, Air, Top (table 0x007D38C8).
enum LayerType {
    LAYER_NONE = -1
};
char const *__fastcall Name_From_Layer(LayerType layer);   // 0x00482FC0
LayerType __fastcall Layer_From_Name(char const *name);    // 0x00482F80

extern char const *LevelNames[];                            // 0x007D1A98

// The 18 veteran abilities, named FASTER, STRONGER, FIREPOWER, SCATTER,
// ROF, SIGHT, CLOAK, TIBERIUM_PROOF, VEIN_PROOF, SELF_HEAL, EXPLODES,
// RADAR_INVISIBLE, SENSORS, FEARLESS, C4, TIBERIUM_HEAL, GUARD_AREA,
// CRUSHER (table 0x007F9978); one flag each.
int __fastcall Ability_From_Name(char const *name);        // 0x00713300 (-1 when unknown)

// AbilitiesStruct: shared/abilities.hpp.

// TargetClass: shared/target.hpp.
#include "shared/target.hpp"

// ----- unit 3 (CCINI.cpp 0x004696B0-0x0046B0B0) -----

// ArmorType, ArmorNames and Armor_From_Name: shared/weapon_type.hpp.
#include "shared/weapon_type.hpp"

// CrateType and CrateNames: shared/ini_enums.hpp.
CrateType __fastcall Crate_From_Name(char const *name);    // 0x00482DA0

// Edges North, East, South, West, Air (names 0x0079AB50).
enum SourceType {
    SOURCE_NORTH
};
SourceType __fastcall Source_From_Name(char const *name);  // 0x00482AB0

// Theaters (TEMPERATE, ...): Theater_From_Name 0x00482B10.
enum TheaterType {
    THEATER_TEMPERATE
};
TheaterType __fastcall Theater_From_Name(char const *name); // 0x00482B10

char const *__fastcall Name_From_Land(LandType land);      // 0x00482F00
LandType __fastcall Land_From_Name(char const *name);      // 0x00482EB0

// Name_From_Category, Category_From_Name: shared/ini_enums.hpp.

// {name, value} tables searched by name.
struct NameValueStruct {
    char const *Name;
    int Value;
};
extern NameValueStruct PipNames[5];             // 0x007D1970 green, yellow, white, red, blue
extern NameValueStruct PipScaleNames[4];        // 0x007D1998 Ammo, Tiberium, Passengers, Power
extern NameValueStruct FoundationNames[22];     // 0x007D19B8 1x1, 2x1, ... 0x0
extern char const *MovementZoneNames[12];       // 0x007D1A68 Normal, Crusher, ... WaterBeach
extern char const *ActionNames[66];             // 0x0079D888 None, Move, NoMove, ...

// HSVClass: shared/hsv_class.hpp.

// AbstractClass kinds <none>, Unit, Aircraft, AircraftType, Anim, ...
// ({name, value} pairs at 0x007CD978).
enum RTTIType {
    RTTI_NONE
};
char const *__fastcall Name_From_RTTI(RTTIType rtti);      // 0x0040DB60
RTTIType __fastcall RTTI_From_Name(char const *name);      // 0x0040DB90

// BuildCat and its names: shared/building_type.hpp.


// Owner bits: 1 << the house type's index, or 0 for an unknown name.
int __fastcall Owner_From_Name(char const *name);          // 0x00482DE0

// HouseClass and Houses: shared/house.hpp.

// Super weapon types: shared/super_weapon_type.hpp.
#include "shared/super_weapon_type.hpp"

// EVA voices: shared/vox_class.hpp.
#include "shared/vox_class.hpp"

// The music player (ThemeClass, Theme): shared/theme.hpp.
#include "shared/theme.hpp"

// The movie names: shared/movie_list.hpp.
#include "shared/movie_list.hpp"

// Sound effects: Voc_Name (0x00714A00) is in shared/voc_class.hpp.
#include "shared/voc_class.hpp"

// Colour schemes (ColorScheme, ColorSchemes 0x00AB6EF8): shared/color_scheme.hpp.

// Edge names North, East, South, West, Air (0x0079AB50).
extern char const *SourceNames[];                           // 0x0079AB50

// Theater descriptions (Theaters, 0x0079AB68): shared/anim_type.hpp.

#endif
