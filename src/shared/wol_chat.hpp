// The Westwood Online chat interface (IChat) and the records its methods take (Server, Update,
// Squad, Channel; WOL::User is in shared/unknown_globals.hpp). Moved from shared/wol_sink.hpp so that
// callers outside wonline.cpp (netshare.cpp's game options senders 0x005C3C60/0x005C3D90) need not
// include the event sinks, whose templates make such units emit COMDATs the original does not have.
#ifndef RA2_WOL_CHAT_HPP
#define RA2_WOL_CHAT_HPP

#include "shared/unknown_globals.hpp"
#include "shared/com_api.hpp"

namespace WOL {
struct Server {
    char unknown_00[0x14];
    Server *next;                       // +0x14
    char name[0x5f - 0x18];
    char kind[5];                       // +0x5f: IRC, LAD, GAM, WDT or MGL
    char connection[128];              // +0x64
    char nickname[10];                 // +0xe4
    char password[10];                 // +0xee
};
// An available patch (the WOL API Update record; the field names are the Renegade WOLAPI ones).
struct Update {
    unsigned long SKU;                  // +0x00
    unsigned long version;              // +0x04
    int required;                       // +0x08
    Update *next;                       // +0x0C
    char server[0x51 - 0x10];           // +0x10
    char patchpath[0x151 - 0x51];       // +0x51
    char patchfile[0x172 - 0x151];      // +0x151
    char login[0x193 - 0x172];          // +0x172
    char password[0x1D4 - 0x193];       // +0x193
    char localpath[0x2D4 - 0x1D4];      // +0x1D4
};
struct Squad {
    char unknown_00[0x168];
    char abbreviation[0x191 - 0x168];   // +0x168
    char name[1];                       // +0x191 (extent unknown)
};
struct Channel;
struct User;


// WOL::User is in shared/unknown_globals.hpp.

struct Channel {
    int unknown_00;
    union {
        char unknown_04[0x14 - 4];
        struct { unsigned int minUsers,maxUsers,currentUsers,official; };
    };
    int unknown_14;                     // +0x14
    union {
        char unknown_18[0x20 - 0x18];
        struct { unsigned int ingame,flags; };
    };
    unsigned int unknown_20;            // +0x20 flags (OnGameStart keeps the low byte; bits 8, 11, 12 tested by 0x0073C340..0x0073C400)
    char unknown_24[0x28 - 0x24];
    int ping;
    int unknown_2c;
    Channel *next;
    union { char name[0x10c - 0x34]; struct { char channel_name[17],topic[81],location[65],key[9],exInfo[41]; char unknown_109[3]; }; };
};
// Only slot 42 is called here; unused interface signatures are hypotheses.
struct __declspec(novtable) IChat : public IUnknown {
    virtual void __stdcall unknown_slot03() = 0;
    // IChat slot4, original744AF4: SDK RequestServerList; no prior callers of the placeholder.
    virtual HRESULT __stdcall Request_Server_List(unsigned long sku,unsigned long version,char const *login,char const *password,int timeout) = 0;
    virtual HRESULT __stdcall RequestConnection(Server *server,int timeout,int mangle) = 0;
    virtual HRESULT __stdcall unknown_slot06(int channel_type,int autoping) = 0;
    virtual void __stdcall unknown_slot07() = 0;
    virtual HRESULT __stdcall unknown_slot08(Channel *channel) = 0;
    virtual HRESULT __stdcall unknown_slot09() = 0;
    virtual void __stdcall unknown_slot10() = 0;
    virtual HRESULT __stdcall unknown_slot11(char const *text) = 0;
    virtual HRESULT __stdcall unknown_slot12(User *users,char const *options) = 0;
    virtual HRESULT __stdcall unknown_slot13() = 0;
    virtual HRESULT __stdcall unknown_slot14(User *user, char const *text) = 0;
    virtual HRESULT __stdcall unknown_slot15(char const *text) = 0;
    virtual void __stdcall unknown_slot16() = 0;
    virtual void __stdcall unknown_slot17() = 0;
    virtual HRESULT __stdcall RequestGameStart(User *users) = 0; // SDK IChat slot18; original73D39F
    virtual void __stdcall unknown_slot19() = 0;
#ifdef RA2_WOL_CHAT_STARTUP_SIGNATURES
    virtual HRESULT __stdcall GetVersion(unsigned long *version) = 0; // SDK slot20, original74156A.
#else
    virtual void __stdcall unknown_slot20() = 0;
#endif
    virtual HRESULT __stdcall unknown_slot21(User *user) = 0;
    virtual void __stdcall unknown_slot22() = 0;
    virtual HRESULT __stdcall Game_Icon(long id, long format, void **bitmap, void **palette, int *width, int *height) = 0;
    virtual HRESULT __stdcall unknown_slot24(User *user) = 0;   // OnBuddyList: a zeroed User with the name
    virtual void __stdcall unknown_slot25() = 0;
#ifdef RA2_WOL_CHAT_SETTINGS_SIGNATURES
    virtual HRESULT __stdcall SetFindPage(int find_on, int page_on) = 0; // SDK IChat slot26; original73C9BC.
#else
    virtual void __stdcall unknown_slot26() = 0;
#endif
    virtual void __stdcall unknown_slot27() = 0;
    virtual void __stdcall unknown_slot28() = 0;
    virtual void __stdcall unknown_slot29() = 0;
    virtual void __stdcall unknown_slot30() = 0;
#ifdef RA2_WOL_CHAT_SETTINGS_SIGNATURES
    virtual HRESULT __stdcall SetLangFilter(int on_off) = 0; // SDK IChat slot31; original73C9A3.
#else
    virtual void __stdcall unknown_slot31() = 0;
#endif
    virtual void __stdcall unknown_slot32() = 0;
    virtual HRESULT __stdcall Game_Types(char const **types) = 0;
    virtual void __stdcall unknown_slot34() = 0;
    virtual HRESULT __stdcall unknown_slot35(unsigned long sku) = 0;
    virtual HRESULT __stdcall unknown_slot36(int index,char const **nick,char const **password) = 0;
    virtual HRESULT __stdcall unknown_slot37(int index,char const *nick,char const *password,int mangle) = 0;
    virtual void __stdcall unknown_slot38() = 0;
    virtual HRESULT __stdcall unknown_slot39(char const *text) = 0;
    virtual void __stdcall unknown_slot40() = 0;
#ifdef RA2_WOL_CHAT_STARTUP_SIGNATURES
    virtual HRESULT __stdcall SetAttributeValue(char const *attribute,char const *value) = 0; // SDK slot41, original74159D.
#else
    virtual void __stdcall unknown_slot41() = 0;
#endif
    virtual HRESULT __stdcall unknown_slot42(char const *text) = 0;
    virtual void __stdcall unknown_slot43() = 0;
    virtual HRESULT __stdcall unknown_slot44(unsigned int value) = 0;
#ifdef RA2_WOL_CHAT_SETTINGS_SIGNATURES
    virtual void __stdcall unknown_slot45(int team) = 0; // 0x00743720 passes the WDT team
#else
    virtual void __stdcall unknown_slot45() = 0;
#endif
    virtual HRESULT __stdcall RequestSetLocale(int locale) = 0;
    virtual HRESULT __stdcall RequestUserLocale(User *users) = 0;
#ifdef RA2_WOL_WAIT_CALLBACK_SIGNATURES
    virtual HRESULT __stdcall RequestUserTeam(User *users) = 0; // SDK IChat slot48; original73E3BB.
#else
    virtual void __stdcall unknown_slot48() = 0;
#endif
    virtual void __stdcall unknown_slot49() = 0;
    virtual HRESULT __stdcall unknown_slot50(int index,int locale) = 0;
    virtual void __stdcall unknown_slot51() = 0;
    virtual HRESULT __stdcall unknown_slot52(int *count) = 0;
    virtual HRESULT __stdcall SetClientVersion(unsigned long version) = 0;
    virtual void __stdcall unknown_slot54() = 0;
    virtual void __stdcall unknown_slot55() = 0;
    virtual HRESULT __stdcall unknown_slot56(User *user) = 0;
    virtual HRESULT __stdcall unknown_slot57(User *user) = 0;
    virtual HRESULT __stdcall unknown_slot58(unsigned short const *message) = 0;
    virtual HRESULT __stdcall unknown_slot59(User *users,unsigned short const *message) = 0;
    virtual HRESULT __stdcall unknown_slot60(unsigned short const *message) = 0;
    virtual HRESULT __stdcall unknown_slot61(User *users,unsigned short const *message) = 0;
    virtual HRESULT __stdcall unknown_slot62(User *user,unsigned short const *message) = 0; // RA2 Unicode page call at original +0xF8
    virtual HRESULT __stdcall unknown_slot63(int update,int count) = 0;
};
}

// The firewall settings at 0x00A71B18 (formerly declared here as FirewallSettings).
#include "shared/firewall_settings.hpp"
#endif
