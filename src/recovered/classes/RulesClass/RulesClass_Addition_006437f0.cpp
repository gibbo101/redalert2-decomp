// RulesClass::Addition (0x006437F0)
// Reads every rules section of an INI in order: colours, countries, sides,
// the type lists, the settings sections, the objects' own sections, the
// tiberiums and the advanced command bar of the session kind.
// @ref ?Addition@RulesClass@@QAE_NAAVCCINIClass@@@Z=006437f0
// @ref ?Special_Weapons@RulesClass@@QAE_NAAVCCINIClass@@@Z=00643b80
// @ref ?Audio_Visual@RulesClass@@QAE_NAAVCCINIClass@@@Z=00643e10
// @ref ?Crate_Rules@RulesClass@@QAE_NAAVCCINIClass@@@Z=006469b0
// @ref ?Combat_Damage@RulesClass@@QAE_NAAVCCINIClass@@@Z=00646c60
// @ref ?Radiation@RulesClass@@QAE_NAAVCCINIClass@@@Z=00647b60
// @ref ?Elevation_Model@RulesClass@@QAE_NAAVCCINIClass@@@Z=00647d40
// @ref ?Wall_Model@RulesClass@@QAE_NAAVCCINIClass@@@Z=00647de0
// @ref ?Colors@RulesClass@@QAE_NAAVCCINIClass@@@Z=00647e60
// @ref ?General@RulesClass@@QAE_NAAVCCINIClass@@@Z=00647f40
// @ref ?MPlayer@RulesClass@@QAE_NAAVCCINIClass@@@Z=0064b690
// @ref ?Heap_Maximums@RulesClass@@QAE_NAAVCCINIClass@@@Z=0064ba00
// @ref ?Infantry@RulesClass@@QAE_NAAVCCINIClass@@@Z=0064ba50
// @ref ?Countries@RulesClass@@QAE_NAAVCCINIClass@@@Z=0064bac0
// @ref ?Vehicles@RulesClass@@QAE_NAAVCCINIClass@@@Z=0064bb30
// @ref ?Aircraft@RulesClass@@QAE_NAAVCCINIClass@@@Z=0064bba0
// @ref ?Sides@RulesClass@@QAE_NAAVCCINIClass@@@Z=0064bc10
// @ref ?Super_Weapons@RulesClass@@QAE_NAAVCCINIClass@@@Z=0064bdc0
// @ref ?Buildings@RulesClass@@QAE_NAAVCCINIClass@@@Z=0064be30
// @ref ?Terrains@RulesClass@@QAE_NAAVCCINIClass@@@Z=0064bea0
// @ref ?Teams@RulesClass@@QAE_NAAVCCINIClass@@@Z=0064bf10
// @ref ?Smudges@RulesClass@@QAE_NAAVCCINIClass@@@Z=0064bfa0
// @ref ?Overlays@RulesClass@@QAE_NAAVCCINIClass@@@Z=0064c010
// @ref ?Animations@RulesClass@@QAE_NAAVCCINIClass@@@Z=0064c080
// @ref ?Voxel_Anims@RulesClass@@QAE_NAAVCCINIClass@@@Z=0064c0f0
// @ref ?Warheads@RulesClass@@QAE_NAAVCCINIClass@@@Z=0064c160
// @ref ?Particles@RulesClass@@QAE_NAAVCCINIClass@@@Z=0064c1d0
// @ref ?Particle_Systems@RulesClass@@QAE_NAAVCCINIClass@@@Z=0064c240
// @ref ?AI@RulesClass@@QAE_NAAVCCINIClass@@@Z=0064c2b0
// @ref ?Movies@RulesClass@@QAE_NAAVCCINIClass@@@Z=0064dc90
// @ref ?Advanced_Command_Bar@RulesClass@@QAE_NAAVCCINIClass@@_N@Z=0064dd90
// @ref ?Powerups@RulesClass@@QAE_NAAVCCINIClass@@@Z=0064d490
// @ref ?Land_Types@RulesClass@@QAE_NAAVCCINIClass@@@Z=0064d610
// @ref ?IQ@RulesClass@@QAE_NAAVCCINIClass@@@Z=0064d850
// @ref ?Jumpjet_Controls@RulesClass@@QAE_NAAVCCINIClass@@@Z=0064d9e0
// @ref ?Objects@RulesClass@@QAE_NAAVCCINIClass@@@Z=00652270
// @ref ?Difficulty@RulesClass@@QAE_NAAVCCINIClass@@@Z=0064db10
// @ref ?Read_Types@TiberiumClass@@SI_NAAVCCINIClass@@@Z=006e8ff0
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"
#include "shared/anim.hpp"
#include "shared/tiberium.hpp"

bool RulesClass::Addition(CCINIClass &ini)
{
    Colors(ini);
    Countries(ini);
    Sides(ini);
    Overlays(ini);
    Super_Weapons(ini);
    Warheads(ini);
    Smudges(ini);
    Terrains(ini);
    Buildings(ini);
    Vehicles(ini);
    Aircraft(ini);
    Infantry(ini);
    Animations(ini);
    Voxel_Anims(ini);
    Particles(ini);
    Particle_Systems(ini);
    Jumpjet_Controls(ini);
    MPlayer(ini);
    AI(ini);
    Powerups(ini);
    Land_Types(ini);
    IQ(ini);
    General(ini);
    Objects(ini);
    Difficulty(ini);
    Crate_Rules(ini);
    Combat_Damage(ini);
    Radiation(ini);
    Elevation_Model(ini);
    Wall_Model(ini);
    Audio_Visual(ini);
    Special_Weapons(ini);
    TiberiumClass::Read_Types(ini);
    return Advanced_Command_Bar(ini, unknown_game_mode_a3d298 != 0 && unknown_game_mode_a3d298 != 5);
}
