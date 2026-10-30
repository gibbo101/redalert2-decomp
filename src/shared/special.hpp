// SpecialClass: the "SpecialFlags" game options, one 32-bit word of bit
// fields (Special.cpp, unit 0x0068B130-0x0068B93F; names after the INI keys
// written/read by 0x0068B430 and 0x0068B5A0; bits 0-2, 4 and 13 are not
// named by any recovered member).
#ifndef RA2_SHARED_SPECIAL_HPP
#define RA2_SHARED_SPECIAL_HPP

#include "shared/ini_class.hpp"

class SpecialClass {
public:
    void Init();                                // 0x0068B320 (defaults, EscapeMovies from the registry)
    bool Equals_Options(SpecialClass const &other) const;   // 0x0068B3F0 (name hypothesis)
    void Write_INI(INIClass &ini) const;        // 0x0068B430 (name hypothesis)
    void Read_INI(INIClass &ini);               // 0x0068B5A0 (name hypothesis)
    void Unknown_0068B410();                    // 0x0068B410 (Read_Scenario_INI, on the global options)
    void Unknown_0068B420();                    // 0x0068B420 (the modem host's first setup, on the global options)

    unsigned unknown_bits_0 : 2;                // bits 0-1
    unsigned IsFromInstall : 1;                 // bit 2 play the intro movies (RA2.INI [Intro] Play)
    unsigned EscapeMovies : 1;                  // bit 3 (registry value)
    unsigned unknown_bit_4 : 1;
    unsigned Inert : 1;                         // bit 5
    unsigned TiberiumGrows : 1;                 // bit 6
    unsigned TiberiumSpreads : 1;               // bit 7
    unsigned MCVDeploy : 1;                     // bit 8
    unsigned InitialVeteran : 1;                // bit 9
    unsigned FixedAlliance : 1;                 // bit 10
    unsigned HarvesterImmune : 1;               // bit 11
    unsigned FogOfWar : 1;                      // bit 12
    unsigned unknown_bit_13 : 1;
    unsigned TiberiumExplosive : 1;             // bit 14
    unsigned DestroyableBridges : 1;            // bit 15
    unsigned Meteorites : 1;                    // bit 16
    unsigned IonStorms : 1;                     // bit 17
    unsigned Visceroids : 1;                    // bit 18
    unsigned unknown_bits_19 : 13;              // bits 19-31
};

// The game options outside a scenario (0x00A40920; copied into the scenario's
// own by Read_Scenario_INI in a multiplayer game).
extern SpecialClass unknown_special_a40920;

#endif
