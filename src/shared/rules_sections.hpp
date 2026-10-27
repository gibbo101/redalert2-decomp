// The rules.ini section names of the Rules unit: pointer variables of the unit's own data
// (0x007A9038 on, after the header statics of shared/unknown_geometry.hpp). Each
// reader reloads the pointer for every call, as a file-static
// (`static char const * const`; VC6 does not fold such a pointer) does. Include only from Rules-unit sources.
#ifndef RA2_SHARED_RULES_SECTIONS_HPP
#define RA2_SHARED_RULES_SECTIONS_HPP

static char const * const RulesSection_SpecialWeapons = "SpecialWeapons";            // 0x007A9038
static char const * const RulesSection_AudioVisual = "AudioVisual";               // 0x007A903C
static char const * const RulesSection_CrateRules = "CrateRules";                // 0x007A9040
static char const * const RulesSection_CombatDamage = "CombatDamage";              // 0x007A9044
static char const * const RulesSection_Radiation = "Radiation";                 // 0x007A9048
static char const * const RulesSection_ElevationModel = "ElevationModel";            // 0x007A904C
static char const * const RulesSection_WallModel = "WallModel";                 // 0x007A9050
static char const * const RulesSection_Colors = "Colors";                    // 0x007A9054
static char const * const RulesSection_General = "General";                   // 0x007A9058
static char const * const RulesSection_MultiplayerDialogSettings = "MultiplayerDialogSettings"; // 0x007A905C
static char const * const RulesSection_Maximums = "Maximums";                  // 0x007A9060
static char const * const RulesSection_InfantryTypes = "InfantryTypes";             // 0x007A9064
static char const * const RulesSection_Countries = "Countries";                 // 0x007A9068
static char const * const RulesSection_VehicleTypes = "VehicleTypes";              // 0x007A906C
static char const * const RulesSection_AircraftTypes = "AircraftTypes";             // 0x007A9070
static char const * const RulesSection_Sides = "Sides";                     // 0x007A9074
static char const * const RulesSection_SuperWeaponTypes = "SuperWeaponTypes";          // 0x007A9078
static char const * const RulesSection_BuildingTypes = "BuildingTypes";             // 0x007A907C
static char const * const RulesSection_TerrainTypes = "TerrainTypes";              // 0x007A9080
static char const * const RulesSection_Teams = "Teams";                     // 0x007A9084
static char const * const RulesSection_SmudgeTypes = "SmudgeTypes";               // 0x007A9088
static char const * const RulesSection_OverlayTypes = "OverlayTypes";              // 0x007A908C
static char const * const RulesSection_AI = "AI";                        // 0x007A9090
static char const * const RulesSection_Powerups = "Powerups";                  // 0x007A9094
static char const * const RulesSection_IQ = "IQ";                        // 0x007A9098
static char const * const RulesSection_JumpjetControls = "JumpjetControls";           // 0x007A909C
static char const * const RulesSection_Movies = "Movies";                    // 0x007A90A0
static char const * const RulesSection_AdvancedCommandBar = "AdvancedCommandBar";        // 0x007A90A4
static char const * const RulesSection_MultiplayerAdvancedCommandBar = "MultiplayerAdvancedCommandBar"; // 0x007A90A8
static char const * const RulesSection_ButtonList = "ButtonList";                // 0x007A90AC
static char const * const RulesSection_None = "";                   // 0x007A90B0 (the empty default of ButtonList=)

#endif
