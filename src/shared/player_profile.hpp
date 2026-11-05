// PlayerProfile: the Wonline profile layout established by original ctor00738C40 and RTTI.
#ifndef RA2_SHARED_PLAYER_PROFILE_HPP
#define RA2_SHARED_PLAYER_PROFILE_HPP
#include "shared/reference_counted.hpp"
#include "shared/wstring.hpp"
struct HWND__;
namespace WOL { struct Ladder; }
class PlayerProfile : public ReferenceCounted {
public:
    virtual ~PlayerProfile() {}
    PlayerProfile(Wstring const &server, int locale, bool verified, int unknown_18, int country, int color,
                  int rank, int points, int wins, int losses, int disconnects);   // 0x00738C40
    static rc_ptr<PlayerProfile> __fastcall Load_Default();                          // 0x00738670
    static rc_ptr<PlayerProfile> __fastcall Load_00738880(Wstring const &name);
    void Populate_Dialog_00739b70(HWND__ *dialog, Wstring const &name, bool update);
    bool unknown_08;                // +0x08 cleared by the constructor
    Wstring Server;                 // +0x0C
    int unknown_10;                 // +0x10 the locale
    bool Verified;                  // +0x14
    int unknown_18;                 // +0x18
    int Country;                    // +0x1C
    int Color;                      // +0x20
    int Rank;                       // +0x24
    int Points;                     // +0x28
    int Wins;                       // +0x2C
    int Losses;                     // +0x30
    int Disconnects;                // +0x34
    int Unknown_Value_10() const { return unknown_10; }
    Wstring const &Get_Server() const { return Server; }
    // Sets the locale (+0x10; source 2: from the server) (0x00739950; name hypothesis).
    void Set_Locale_00739950(int locale, int source);
    void Set_Server_00739920(Wstring const &server);
    unsigned int Set_Country_007399b0(unsigned int country);
    unsigned int Set_Color_007399d0(unsigned int color);
    void Set_Ladder_007399f0(WOL::Ladder *entry);
    // Writes the profile for a nickname into wolinfo.ini (0x007395D0; name hypothesis).
    void Save_007395d0(Wstring const &name);
    // size 0x38 (operator new in Load_Default 0x00738670)
};
#endif
