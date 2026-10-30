// The Westwood Online event sinks of WOnline.cpp ("D:\Ra2\wonline.cpp"):
// CNetUtilEventSink (vtable 0x007AF840) and CChatEventSink (0x007AF868)
// implement the WOL API's INetUtilEvent and IChatEvent; the ATL
// CComObject<...> wrappers (0x007AF73C, 0x007AF77C) supply IUnknown.
//
// Layout (constructors 0x0075D1F0, 0x0075DFE0): +0x00 the interface vtable,
// +0x04 the ATL reference count, +0x08 the ATL critical section
// (CComObjectRootEx<CComMultiThreadModel>; MSVC places the polymorphic base
// first). ATL lifetime and interface-map operations below are recovered
// as ordinary source and checked against the original template instances.
//
// Interface method names and parameters follow the WOL API (wolapi.idl)
// where the vtable order, the ret sizes and the debug strings agree;
// hypotheses otherwise.
#ifndef RA2_WOL_SINK_HPP
#define RA2_WOL_SINK_HPP
// The unit inlines VectorClass::operator[] and DynamicVectorClass::Count (0x0073F550).
#ifndef VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#endif
#ifndef VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#endif

#include "shared/unknown_globals.hpp"
#include "shared/wdt_state.hpp"
#include "shared/com_persist.hpp"
#include "shared/com_api.hpp"
#include "shared/win32_api.hpp"
#include "shared/string_table.hpp"
#include "shared/wstring.hpp"
#include "shared/wide_string.hpp"
#include "shared/system_timer.hpp"
#include "shared/cd_timer.hpp"

#include "shared/debug_printf.hpp"
#include "shared/pcx_cache.hpp"

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
struct Ladder {
    unsigned int game_type;
    int unknown_04;
    int unknown_08;
    int unknown_0c;
    int unknown_10;
    int unknown_14;
    int unknown_18;
    int unknown_1c;
    int unknown_20;
    char unknown_24[0x3c - 0x24];
    Ladder *next;
    char name[0x6c - 0x40];
};

// WOL::User is in shared/unknown_globals.hpp.

struct Channel {
    int unknown_00;
    union {
        char unknown_04[0x14 - 4];
        struct { unsigned int minUsers,maxUsers,currentUsers,official; };
    };
    int unknown_14;                     // +0x14
    char unknown_18[0x20 - 0x18];
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
    virtual void __stdcall unknown_slot04() = 0;
    virtual void __stdcall unknown_slot05() = 0;
    virtual void __stdcall unknown_slot06() = 0;
    virtual void __stdcall unknown_slot07() = 0;
    virtual HRESULT __stdcall unknown_slot08(Channel *channel) = 0;
    virtual HRESULT __stdcall unknown_slot09() = 0;
    virtual void __stdcall unknown_slot10() = 0;
    virtual void __stdcall unknown_slot11() = 0;
    virtual void __stdcall unknown_slot12() = 0;
    virtual void __stdcall unknown_slot13() = 0;
    virtual HRESULT __stdcall unknown_slot14(User *user, char const *text) = 0;
    virtual HRESULT __stdcall unknown_slot15(char const *text) = 0;
    virtual void __stdcall unknown_slot16() = 0;
    virtual void __stdcall unknown_slot17() = 0;
    virtual void __stdcall unknown_slot18() = 0;
    virtual void __stdcall unknown_slot19() = 0;
    virtual void __stdcall unknown_slot20() = 0;
    virtual HRESULT __stdcall unknown_slot21(User *user) = 0;
    virtual void __stdcall unknown_slot22() = 0;
    virtual HRESULT __stdcall Game_Icon(long id, long format, void **bitmap, void **palette, int *width, int *height) = 0;
    virtual HRESULT __stdcall unknown_slot24(User *user) = 0;   // OnBuddyList: a zeroed User with the name
    virtual void __stdcall unknown_slot25() = 0;
    virtual void __stdcall unknown_slot26() = 0;
    virtual void __stdcall unknown_slot27() = 0;
    virtual void __stdcall unknown_slot28() = 0;
    virtual void __stdcall unknown_slot29() = 0;
    virtual void __stdcall unknown_slot30() = 0;
    virtual void __stdcall unknown_slot31() = 0;
    virtual void __stdcall unknown_slot32() = 0;
    virtual HRESULT __stdcall Game_Types(char const **types) = 0;
    virtual void __stdcall unknown_slot34() = 0;
    virtual HRESULT __stdcall unknown_slot35(unsigned long sku) = 0;
    virtual HRESULT __stdcall unknown_slot36(int index,char const **nick,char const **password) = 0;
    virtual HRESULT __stdcall unknown_slot37(int index,char const *nick,char const *password,int mangle) = 0;
    virtual void __stdcall unknown_slot38() = 0;
    virtual HRESULT __stdcall unknown_slot39(char const *text) = 0;
    virtual void __stdcall unknown_slot40() = 0;
    virtual void __stdcall unknown_slot41() = 0;
    virtual HRESULT __stdcall unknown_slot42(char const *text) = 0;
    virtual void __stdcall unknown_slot43() = 0;
    virtual HRESULT __stdcall unknown_slot44(unsigned int value) = 0;
    virtual void __stdcall unknown_slot45() = 0;
    virtual void __stdcall unknown_slot46() = 0;
    virtual void __stdcall unknown_slot47() = 0;
    virtual void __stdcall unknown_slot48() = 0;
    virtual void __stdcall unknown_slot49() = 0;
    virtual HRESULT __stdcall unknown_slot50(int index,int locale) = 0;
    virtual void __stdcall unknown_slot51() = 0;
    virtual HRESULT __stdcall unknown_slot52(int *count) = 0;
    virtual void __stdcall unknown_slot53() = 0;
    virtual void __stdcall unknown_slot54() = 0;
    virtual void __stdcall unknown_slot55() = 0;
    virtual HRESULT __stdcall unknown_slot56(User *user) = 0;
    virtual HRESULT __stdcall unknown_slot57(User *user) = 0;
    virtual HRESULT __stdcall unknown_slot58(unsigned short const *message) = 0;
    virtual HRESULT __stdcall unknown_slot59(User *users,unsigned short const *message) = 0;
    virtual HRESULT __stdcall unknown_slot60(unsigned short const *message) = 0;
    virtual HRESULT __stdcall unknown_slot61(User *users,unsigned short const *message) = 0;
    virtual void __stdcall unknown_slot62() = 0;
    virtual HRESULT __stdcall unknown_slot63(int update,int count) = 0;
};

// The WOL download object (only the first method is called here).
struct __declspec(novtable) IDownload : public IUnknown {
    virtual HRESULT __stdcall DownloadFile(char const *server, char const *login, char const *password,
                                           char const *file, char const *local, char const *regkey) = 0;
    virtual HRESULT __stdcall Abort() = 0;
};

struct __declspec(novtable) INetUtilEvent : public IUnknown {
    virtual HRESULT __stdcall OnPing(HRESULT result, int time, unsigned long ip, int handle) = 0;
    virtual HRESULT __stdcall OnLadderList(HRESULT result, Ladder *list, int count, long timestamp, int keyrung) = 0;
    virtual HRESULT __stdcall OnGameresSent(HRESULT result) = 0;
    virtual HRESULT __stdcall OnNewNick(HRESULT result, char const *message, char const *nick, char const *pass) = 0;
    virtual HRESULT __stdcall OnAgeCheck(HRESULT result, int years, int consent) = 0;
    virtual HRESULT __stdcall OnWDTState(HRESULT result, unsigned char *state, int length) = 0;
};

struct __declspec(novtable) IDownloadEvent : public IUnknown {
    virtual HRESULT __stdcall OnEnd() = 0;
    virtual HRESULT __stdcall OnError(int error) = 0;
    virtual HRESULT __stdcall OnProgressUpdate(int bytes_read, int total_size, int time_taken, int time_left) = 0;
    virtual HRESULT __stdcall OnQueryResume() = 0;
};

struct __declspec(novtable) IChatEvent : public IUnknown {
    virtual HRESULT __stdcall OnServerList(HRESULT result, Server *servers) = 0;
    virtual HRESULT __stdcall OnUpdateList(HRESULT result, Update *updates) = 0;
    virtual HRESULT __stdcall OnServerError(HRESULT result, char const *message) = 0;
    virtual HRESULT __stdcall OnConnection(HRESULT result, char const *motd) = 0;
    virtual HRESULT __stdcall OnMessageOfTheDay(HRESULT result, char const *motd) = 0;
    virtual HRESULT __stdcall OnChannelList(HRESULT result, Channel *channels) = 0;
    virtual HRESULT __stdcall OnChannelCreate(HRESULT result, Channel *channel) = 0;
    virtual HRESULT __stdcall OnChannelJoin(HRESULT result, Channel *channel, User *user) = 0;
    virtual HRESULT __stdcall OnChannelLeave(HRESULT result, Channel *channel, User *user) = 0;
    virtual HRESULT __stdcall OnChannelTopic(HRESULT result, Channel *channel, char const *topic) = 0;
    virtual HRESULT __stdcall OnPrivateAction(HRESULT result, User *user, char const *action) = 0;
    virtual HRESULT __stdcall OnPublicAction(HRESULT result, Channel *channel, User *user, char const *action) = 0;
    virtual HRESULT __stdcall OnUserList(HRESULT result, Channel *channel, User *users) = 0;
    virtual HRESULT __stdcall OnPublicMessage(HRESULT result, Channel *channel, User *user, char const *message) = 0;
    virtual HRESULT __stdcall OnPrivateMessage(HRESULT result, User *user, char const *message) = 0;
    virtual HRESULT __stdcall OnSystemMessage(HRESULT result, char const *message) = 0;
    virtual HRESULT __stdcall OnNetStatus(HRESULT result) = 0;
    virtual HRESULT __stdcall OnLogout(HRESULT result, User *user) = 0;
    virtual HRESULT __stdcall OnPrivateGameOptions(HRESULT result, User *user, char const *options) = 0;
    virtual HRESULT __stdcall OnPublicGameOptions(HRESULT result, Channel *channel, User *user, char const *options) = 0;
    virtual HRESULT __stdcall OnGameStart(HRESULT result, Channel *channel, User *users, int game_id) = 0;
    virtual HRESULT __stdcall OnUserKick(HRESULT result, Channel *channel, User *kicked, User *kicker) = 0;
    virtual HRESULT __stdcall OnUserIP(HRESULT result, User *user) = 0;
    virtual HRESULT __stdcall OnFind(HRESULT result, Channel *channel) = 0;
    virtual HRESULT __stdcall OnPageSend(HRESULT result) = 0;
    virtual HRESULT __stdcall OnPaged(HRESULT result, User *user, char const *message) = 0;
    virtual HRESULT __stdcall OnServerBannedYou(HRESULT result, long banned_till) = 0;
    virtual HRESULT __stdcall OnUserFlags(HRESULT result, char const *name, unsigned int flags, unsigned int mask) = 0;
    virtual HRESULT __stdcall OnChannelBan(HRESULT result, char const *name, int banned) = 0;
    virtual HRESULT __stdcall OnSquadInfo(HRESULT result, unsigned long id, Squad *squad) = 0;
    virtual HRESULT __stdcall OnUserLocale(HRESULT result, User *users) = 0;
    virtual HRESULT __stdcall OnUserTeam(HRESULT result, User *users) = 0;
    virtual HRESULT __stdcall OnSetLocale(HRESULT result, int locale) = 0;
    virtual HRESULT __stdcall OnSetTeam(HRESULT result, int team) = 0;
    virtual HRESULT __stdcall OnBuddyList(HRESULT result, User *buddies) = 0;
    virtual HRESULT __stdcall OnBuddyAdd(HRESULT result, User *buddy) = 0;
    virtual HRESULT __stdcall OnBuddyDelete(HRESULT result, User *buddy) = 0;
    virtual HRESULT __stdcall OnPublicUnicodeMessage(HRESULT result, Channel *channel, User *user, unsigned short const *message) = 0;
    virtual HRESULT __stdcall OnPrivateUnicodeMessage(HRESULT result, User *user, unsigned short const *message) = 0;
    virtual HRESULT __stdcall OnPrivateUnicodeAction(HRESULT result, User *user, unsigned short const *action) = 0;
    virtual HRESULT __stdcall OnPublicUnicodeAction(HRESULT result, Channel *channel, User *user, unsigned short const *action) = 0;
    virtual HRESULT __stdcall OnPagedUnicode(HRESULT result, User *user, unsigned short const *message) = 0;
};
}

// The layout and lifetime of ATL's CComObjectRootEx<CComMultiThreadModel>
// (0x1C bytes: reference count and critical section).
extern long unknown_module_locks_b2930c;

struct AtlRootLayout {
    AtlRootLayout() : m_dwRef(0) { InitializeCriticalSection(&m_critsec); }
    ~AtlRootLayout() { DeleteCriticalSection(&m_critsec); }
    long m_dwRef;                       // +0x04 in the sink
    CRITICAL_SECTION m_critsec;               // +0x08 CRITICAL_SECTION
};

class CNetUtilEventSink : public AtlRootLayout, public WOL::INetUtilEvent {
public:
    CNetUtilEventSink();
    virtual HRESULT __stdcall OnPing(HRESULT result, int time, unsigned long ip, int handle);            // 0x0075DF30
    virtual HRESULT __stdcall OnLadderList(HRESULT result, WOL::Ladder *list, int count, long timestamp, int keyrung);  // 0x0075D330
    virtual HRESULT __stdcall OnGameresSent(HRESULT result);                                             // 0x0075D300
    virtual HRESULT __stdcall OnNewNick(HRESULT result, char const *message, char const *nick, char const *pass);  // 0x0075DBD0
    virtual HRESULT __stdcall OnAgeCheck(HRESULT result, int years, int consent);                        // 0x0075DEB0
    virtual HRESULT __stdcall OnWDTState(HRESULT result, unsigned char *state, int length);              // 0x0075D210
};

class CChatEventSink : public AtlRootLayout, public WOL::IChatEvent {
public:
    CChatEventSink();
    virtual HRESULT __stdcall OnServerList(HRESULT result, WOL::Server *servers);              // 0x0075E000
    virtual HRESULT __stdcall OnUpdateList(HRESULT result, WOL::Update *updates);              // 0x0075EA50
    virtual HRESULT __stdcall OnServerError(HRESULT result, char const *message);              // 0x0075EED0
    virtual HRESULT __stdcall OnConnection(HRESULT result, char const *motd);                  // 0x0075EF30
    virtual HRESULT __stdcall OnMessageOfTheDay(HRESULT result, char const *motd);             // 0x0075F290
    virtual HRESULT __stdcall OnChannelList(HRESULT result, WOL::Channel *channels);           // 0x00763C80
    virtual HRESULT __stdcall OnChannelCreate(HRESULT result, WOL::Channel *channel);          // 0x0075F330
    virtual HRESULT __stdcall OnChannelJoin(HRESULT result, WOL::Channel *channel, WOL::User *user);   // 0x0075F530
    virtual HRESULT __stdcall OnChannelLeave(HRESULT result, WOL::Channel *channel, WOL::User *user);  // 0x00760BD0
    virtual HRESULT __stdcall OnChannelTopic(HRESULT result, WOL::Channel *channel, char const *topic);  // 0x007646A0
    virtual HRESULT __stdcall OnPrivateAction(HRESULT result, WOL::User *user, char const *action);    // 0x00764360
    virtual HRESULT __stdcall OnPublicAction(HRESULT result, WOL::Channel *channel, WOL::User *user, char const *action);  // 0x00764500
    virtual HRESULT __stdcall OnUserList(HRESULT result, WOL::Channel *channel, WOL::User *users);     // 0x00760C00
    virtual HRESULT __stdcall OnPublicMessage(HRESULT result, WOL::Channel *channel, WOL::User *user, char const *message);  // 0x00762590
    virtual HRESULT __stdcall OnPrivateMessage(HRESULT result, WOL::User *user, char const *message);            // 0x00762790
    virtual HRESULT __stdcall OnSystemMessage(HRESULT result, char const *message);                            // 0x00763AB0
    virtual HRESULT __stdcall OnNetStatus(HRESULT result);                                                     // 0x00763AE0
    virtual HRESULT __stdcall OnLogout(HRESULT result, WOL::User *user);                                       // 0x0075EEB0
    virtual HRESULT __stdcall OnPrivateGameOptions(HRESULT result, WOL::User *user, char const *options);      // 0x00761C50
    virtual HRESULT __stdcall OnPublicGameOptions(HRESULT result, WOL::Channel *channel, WOL::User *user, char const *options);  // 0x00761890
    virtual HRESULT __stdcall OnGameStart(HRESULT result, WOL::Channel *channel, WOL::User *users, int game_id);  // 0x00761570
    virtual HRESULT __stdcall OnUserKick(HRESULT result, WOL::Channel *channel, WOL::User *kicked, WOL::User *kicker);  // 0x00764B00
    virtual HRESULT __stdcall OnUserIP(HRESULT result, WOL::User *user);                                       // 0x007646B0
    virtual HRESULT __stdcall OnFind(HRESULT result, WOL::Channel *channel);                                   // 0x00762F70
    virtual HRESULT __stdcall OnPageSend(HRESULT result);                                                      // 0x00762E00
    virtual HRESULT __stdcall OnPaged(HRESULT result, WOL::User *user, char const *message);                   // 0x007629B0
    virtual HRESULT __stdcall OnServerBannedYou(HRESULT result, long banned_till);                             // 0x007646C0
    virtual HRESULT __stdcall OnUserFlags(HRESULT result, char const *name, unsigned int flags, unsigned int mask);  // 0x007647B0
    virtual HRESULT __stdcall OnChannelBan(HRESULT result, char const *name, int banned);                      // 0x00764730
    virtual HRESULT __stdcall OnSquadInfo(HRESULT result, unsigned long id, WOL::Squad *squad);                // 0x0075ED00
    virtual HRESULT __stdcall OnUserLocale(HRESULT result, WOL::User *users);                                  // 0x00764D70
    virtual HRESULT __stdcall OnUserTeam(HRESULT result, WOL::User *users);                                    // 0x007651D0
    virtual HRESULT __stdcall OnSetLocale(HRESULT result, int locale);                                         // 0x00764F80
    virtual HRESULT __stdcall OnSetTeam(HRESULT result, int team);                                             // 0x00765430
    virtual HRESULT __stdcall OnBuddyList(HRESULT result, WOL::User *buddies);                                 // 0x007656B0
    virtual HRESULT __stdcall OnBuddyAdd(HRESULT result, WOL::User *buddy);                                    // 0x00765930
    virtual HRESULT __stdcall OnBuddyDelete(HRESULT result, WOL::User *buddy);                                 // 0x00765940
    virtual HRESULT __stdcall OnPublicUnicodeMessage(HRESULT result, WOL::Channel *channel, WOL::User *user, unsigned short const *message);  // 0x007626B0
    virtual HRESULT __stdcall OnPrivateUnicodeMessage(HRESULT result, WOL::User *user, unsigned short const *message);  // 0x007628D0
    virtual HRESULT __stdcall OnPrivateUnicodeAction(HRESULT result, WOL::User *user, unsigned short const *action);    // 0x00764440
    virtual HRESULT __stdcall OnPublicUnicodeAction(HRESULT result, WOL::Channel *channel, WOL::User *user, unsigned short const *action);  // 0x007645E0
    virtual HRESULT __stdcall OnPagedUnicode(HRESULT result, WOL::User *user, unsigned short const *message);  // 0x00762C20
};

// The patch download sink (vtable of CComObject<CDownloadEventSink>
// 0x007AF9A4). Its methods follow the template instances at the end of
// WOnline.cpp, so they were inline in a class declared in the .cpp
// (hypothesis); here they are defined out of line.
class CDownloadEventSink : public AtlRootLayout, public WOL::IDownloadEvent {
public:
    virtual HRESULT __stdcall OnEnd();                                               // 0x007668D0
    virtual HRESULT __stdcall OnError(int error);                                    // 0x007668F0
    virtual HRESULT __stdcall OnProgressUpdate(int bytes_read, int total_size, int time_taken, int time_left);  // 0x00766910
    virtual HRESULT __stdcall OnQueryResume();                                       // 0x00766AA0
};
extern long unknown_b2acc8;             // 0x00B2ACC8 (time of the last progress text)
#include "shared/crt_time.hpp"
WIN32_IMPORT LRESULT WINAPI SendDlgItemMessageA(HWND dialog, int id, UINT message, WPARAM wparam, LPARAM lparam);

// WOnline.cpp globals (names unknown; addresses evidenced).
extern int unknown_a3d2a4;              // 0x00A3D2A4 (1 or 2: an online session state)
extern int unknown_b2ac0c;              // 0x00B2AC0C (the age-check result)
extern int unknown_b2ac6c;              // 0x00B2AC6C (years)
extern int unknown_b2ac70;              // 0x00B2AC70 (consent)
extern unsigned int unknown_b2abe0;     // 0x00B2ABE0 (pending-request bits; 0x100 age check)
extern bool unknown_b2abd9;             // 0x00B2ABD9
extern int unknown_b2a630;              // 0x00B2A630
extern int unknown_b2aaf8;              // 0x00B2AAF8 (successful pings)
extern int unknown_b26568;              // 0x00B26568 (pings received)
extern int unknown_b29828;              // 0x00B29828 (pings expected)
extern int unknown_b26898;              // 0x00B26898
extern int unknown_b299c0;              // 0x00B299C0

void __fastcall Unknown_00698D00(bool arg);             // 0x00698D00 (stores cl: a byte)
void *__fastcall Unknown_00735940(int id);              // 0x00735940 (a dialog by id)
void Unknown_0075B590();                                // 0x0075B590
void Unknown_0075B2D0();                                // 0x0075B2D0
void __fastcall Unknown_0073FEE0(int arg1, bool arg2);  // 0x0073FEE0
void __fastcall Unknown_00741750(WOL::User *user);      // 0x00741750 (a user left the channel)
// Converts a narrow string into wide characters (0x006FA0C0; -1: to its end).
void __fastcall Unknown_006FA0C0(wchar_t *buffer, char const *text, int length);
// unknown_color_7a7360: shared/unknown_globals.hpp.
extern int unknown_color_7a736c;        // 0x007A736C (private action colour)
extern int unknown_color_7a7370;        // 0x007A7370 (public action colour)
extern int unknown_color_7a7364;        // 0x007A7364 (public message colour)
extern int unknown_color_7a7374;        // 0x007A7374 (public message colour for users with flag bit 0)
extern int unknown_color_7a7378;        // 0x007A7378 (page colour)
// The nick of the last user who paged us (0x00B2AC48; /reply target hypothesis).
extern char unknown_last_pager_b2ac48[];
extern int unknown_color_7a7368;        // 0x007A7368 (private message colour)
void __fastcall Unknown_0075B910(char const *message, bool arg2);   // 0x0075B910 (in-game message)
extern int unknown_b2a7e8;              // 0x00B2A7E8
extern "C" int __cdecl _stricmp(char const *left, char const *right);


extern "C" char *__cdecl _strdup(char const *string);
extern "C" char *__cdecl strtok(char *string, char const *delimiters);
extern "C" void __cdecl free(void *block);

namespace ATL {
struct InterfaceMapEntry {
    GUID const *iid;
    unsigned long offset;
    HRESULT (__stdcall *query)(void *, GUID const &, void **, unsigned long);
};
inline int IsIUnknown(GUID const &iid)
{
    unsigned long const *parts = (unsigned long const *)&iid;
    return parts[0] == 0 && parts[1] == 0 && parts[2] == 0xc0 && parts[3] == 0x46000000;
}
inline int EqualInterface(GUID const &left, GUID const &right)
{
    unsigned long const *a = (unsigned long const *)&left;
    unsigned long const *b = (unsigned long const *)&right;
    return a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a[3] == b[3];
}
inline HRESULT InternalQueryInterface(void *object, InterfaceMapEntry const *entry, GUID const &iid, void **result)
{
    if (!result) return E_POINTER;
    *result = 0;
    if (IsIUnknown(iid)) {
        IUnknown *unknown = (IUnknown *)((char *)object + entry->offset);
        unknown->AddRef();
        *result = unknown;
        return S_OK;
    }
    while (entry->query) {
        int blind = entry->iid == 0;
        if (blind || EqualInterface(*entry->iid, iid)) {
            if (entry->query == (HRESULT (__stdcall *)(void *, GUID const &, void **, unsigned long))1) {
                IUnknown *unknown = (IUnknown *)((char *)object + entry->offset);
                unknown->AddRef();
                *result = unknown;
                return S_OK;
            }
            HRESULT status = entry->query(object, iid, result, entry->offset);
            if (status == S_OK || (!blind && FAILED(status))) return status;
        }
        ++entry;
    }
    return E_NOINTERFACE;
}

template<class Base> class CComObject : public Base {
public:
    CComObject(void *outer = 0);
    virtual HRESULT __stdcall QueryInterface(GUID const &, void **);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    ~CComObject() {
        m_dwRef = 1;
        InterlockedDecrement(&unknown_module_locks_b2930c);
    }
};
}

inline bool Is_Online_Session()
{
    return unknown_a3d2a4 == 2 || unknown_a3d2a4 == 1;
}

extern HANDLE unknown_b2650c;
extern HANDLE unknown_b26524;
extern long unknown_b292dc;
WIN32_IMPORT BOOL WINAPI SetEvent(HANDLE event);
void __fastcall WDT_Store_Current_00769520(rc_ptr<WDTState> const &state);
void __fastcall WDT_Store_Previous_007695a0(rc_ptr<WDTState> const &state);

struct WolPlayerData {
    char name[0x14];
    int unknown_14;
    int unknown_18;
    int unknown_1c;
    int unknown_20;
    char unknown_24[0x94 - 0x24];
};
extern WolPlayerData unknown_player_b29cf0[16];
extern WOL::Channel unknown_channel_b299c0;
extern Wstring unknown_wstring_b26cb8;
extern int unknown_b2ac58;
extern int unknown_b2abe8;
void __fastcall Format_User_Options_0073cff0(char *text);
wchar_t *__fastcall Unknown_006FA180(char const *text);

class PlayerProfile : public ReferenceCounted {
public:
    PlayerProfile(Wstring const &server, int locale, bool verified, int unknown_18, int country, int color,
                  int rank, int points, int wins, int losses, int disconnects);   // 0x00738C40
    static rc_ptr<PlayerProfile> __fastcall Load_Default();                          // 0x00738670
    static rc_ptr<PlayerProfile> __fastcall Load_00738880(Wstring const &name);
    void Populate_Dialog_00739b70(HWND dialog, Wstring const &name, bool update);
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
    // Sets the locale (+0x10; source 2: from the server) (0x00739950; name hypothesis).
    void Set_Locale_00739950(int locale, int source);
    // Writes the profile for a nickname into the registry (0x007395D0; name hypothesis).
    void Save_007395d0(Wstring const &name);
    // size 0x38 (operator new in Load_Default 0x00738670)
};
#include "shared/wol_registry_options.hpp"
int __fastcall Save_Nickname_00745320(char const *nick, char const *password, bool arg, int arg2);
extern Wstring unknown_password_b2a63c;
extern int unknown_newnick_result_b2ac08;
extern bool unknown_7fd374;
extern void Unknown_0073c120();
int __fastcall Popup_005c3230(wchar_t const *text, int unknown, void (*callback)(), int flags);
extern "C" char *__cdecl ctime(long const *timer);     // 0x007858AF

#include "shared/random.hpp"
extern "C" void __cdecl srand(unsigned int seed);
extern "C" int __cdecl rand();
extern "C" long __cdecl atol(char const *text);
extern "C" void *__cdecl memcpy(void *destination, void const *source, unsigned int length);
#pragma intrinsic(memcpy)
// Non-polymorphic server array observed at 0x00b2a700.
class WolServerArray {
public:
    WolServerArray() : Count(0), Capacity(0), Items(0) {}
    ~WolServerArray() { Count = 0; operator delete(Items); }
    int Count;
    int Capacity;
    WOL::Server *Items;
    bool Grow_00768110();
    void Resize(int capacity) {
        WOL::Server *items = (WOL::Server *)operator new(capacity * sizeof(WOL::Server));
        memset(items, 0, capacity * sizeof(WOL::Server));
        if (Items) memcpy(items, Items, Count * sizeof(WOL::Server));
        operator delete(Items);
        Items = items;
        Capacity = capacity;
    }
    void Insert(int index, WOL::Server const &server) {
        if (index > Count) index = Count;
        if (index >= Capacity) {
            if (Count >= Capacity) {
                int capacity = Count * 2;
                if (capacity < 10) capacity = 10;
                Resize(capacity);
            }
        }
        if (Count >= Capacity) Grow_00768110();
        if (index < Count) memmove(Items + index + 1, Items + index, (Count - index) * sizeof(WOL::Server));
        new (Items + index) WOL::Server(server);
        ++Count;
    }
    bool Get(WOL::Server *&server, int index) {
        if (index >= 0 && index < Count) { server = Items + index; return true; }
        return false;
    }
};
extern WolServerArray unknown_servers_b2a700;
extern WOL::Server unknown_game_server_b28cd0;
extern WOL::Server unknown_wdt_server_b29880;
extern int unknown_irc_index_b292d8;
extern int unknown_irc_index_b2a7f4;
extern unsigned int unknown_protocol_7fd370;
extern int unknown_mangler_count_b2ac34;
extern int unknown_mangler_index_b2ac38;
extern char unknown_ladder_address_b29018[];
extern int unknown_ladder_port_b2a8ac;
extern char unknown_game_address_b2a758[];
extern char unknown_game_address_b2ab00[];
extern int unknown_game_port_b28ffc;
extern int unknown_game_port_b28dd4;
extern char unknown_wdt_address_b269ac[];
extern int unknown_wdt_port_b299bc;
extern char unknown_mangler_addresses_b26cbc[64][128];
extern int unknown_mangler_ports_b291a4[64];
extern HANDLE unknown_server_error_event_b264f8;
extern HANDLE unknown_server_list_event_b264fc;
extern wchar_t unknown_server_error_b2a8ec[];
struct WolUnknownIdentifier { unsigned int unknown_00; void Initialize_005b9e80(); };
extern WolUnknownIdentifier unknown_identifier_a71b18;

class WolChannelArray {
public:
    WolChannelArray() : Count(0), Capacity(0), Items(0) {}
    ~WolChannelArray() { Count = 0; operator delete(Items); }
    int Count;
    int Capacity;
    WOL::Channel *Items;
    bool Insert_00766c20(WOL::Channel const &channel, int index);
    bool Get(WOL::Channel &channel, int index) const {
        if (index >= 0 && index < Count) { channel = Items[index]; return true; }
        return false;
    }
    bool Get(WOL::Channel *&channel, int index) const {
        if (index >= 0 && index < Count) { channel = Items + index; return true; }
        return false;
    }
    bool Find_Name(Wstring const &name,WOL::Channel &channel) const {
        memset(&channel,0,sizeof(channel));
        for(int i=0;i<Count;++i) {
            Get(channel,i);
            if(!_stricmp(channel.name,name.Peek_Buffer())) return true;
        }
        memset(&channel,0,sizeof(channel));
        return false;
    }
    bool Grow_When_Full(); // capacity operation expanded inside original Insert
    bool Shrink_00766dc0();
};
class WolIntArray {
public:
    WolIntArray() : Count(0), Capacity(0), Items(0) {}
    ~WolIntArray() { Count = 0; operator delete(Items); }
    int Count;
    int Capacity;
    int *Items;
    bool Get_00768260(int &value, int index);
    bool Grow() {
        if (Count < Capacity) return false;
        int capacity = Count * 2;
        if (capacity < 10) capacity = 10;
        int *items = (int *)operator new(capacity * sizeof(int));
        memset(items, 0, capacity * sizeof(int));
        if (Items) memcpy(items, Items, Count * sizeof(int));
        operator delete(Items);
        Items = items;
        Capacity = capacity;
        return true;
    }
    bool Shrink() {
        if (Count * 3 > Capacity) return false;
        int capacity = Capacity / 2;
        if (capacity < 10) capacity = 10;
        if (capacity >= Capacity) return false;
        int *items = (int *)operator new(capacity * sizeof(int));
        if (Items) memcpy(items, Items, Count * sizeof(int));
        operator delete(Items);
        Items = items;
        Capacity = capacity;
        return true;
    }
    bool Grow_00768290();
    bool Insert_00766f90(int const &value, int index);
    bool Remove_007681a0(int index);
};
class WolStringArray {
public:
    WolStringArray() : Count(0), Capacity(0), Items(0) {}
    ~WolStringArray() {
        for (int i = 0; i < Count; ++i) Items[i].~Wstring();
        Count = 0;
        operator delete(Items);
    }
    void Clear() {
        for(int i=0;i<Count;++i) Items[i].~Wstring();
        Count=0;
    }
    int Count;
    int Capacity;
    Wstring *Items;
    bool Grow_00768320();
    bool Grow() {
        if (Count < Capacity) return false;
        int capacity = Count * 2;
        if (capacity < 10) capacity = 10;
        Wstring *items = (Wstring *)operator new(capacity * sizeof(Wstring));
        memset(items, 0, capacity * sizeof(Wstring));
        if (Items) memcpy(items, Items, Count * sizeof(Wstring));
        operator delete(Items);
        Items = items;
        Capacity = capacity;
        return true;
    }
    bool Shrink_00767b20();
    bool Remove_007661f0(int index);
    bool Remove(int index) {
        if(Count==0) return false;
        if(index<0) index=0;
        if(index>=Count) index=Count-1;
        Items[index].~Wstring();
        memmove(Items+index,Items+index+1,(Count-index-1)*sizeof(Wstring));
        --Count;
        Shrink();
        return true;
    }

    bool Remove_Inline(int index) {
        if(Count==0) return false;
        if(index<0) index=0;
        if(index>=Count) index=Count-1;
        Items[index].~Wstring();
        memmove(Items+index,Items+index+1,(Count-index-1)*sizeof(Wstring));
        --Count;
        if(Count*3<=Capacity) Shrink_00767b20();
        return true;
    }
    bool Shrink() {
        if (Count * 3 > Capacity) return false;
        int capacity = Capacity / 2;
        if (capacity < 10) capacity = 10;
        if (capacity >= Capacity) return false;
        Wstring *items = (Wstring *)operator new(capacity * sizeof(Wstring));
        if (Items) memcpy(items, Items, Count * sizeof(Wstring));
        operator delete(Items);
        Items = items;
        Capacity = capacity;
        return true;
    }
    bool Get(Wstring &text, int index) {
        if (index >= 0 && index < Count) { text = Items[index]; return true; }
        return false;
    }
    bool Insert(Wstring const &text, int index); // original complete method 0x007679c0
    bool Get_007662c0(Wstring &text, int index); // out of line in wonline.cpp (accepted unowned 0x007662C0)
    void Add(Wstring const &text) {
        int index = Count;
        if (index > Count) index = Count;
        if (index >= Capacity) Grow_00768320();
        if (Count >= Capacity) Grow_00768320();
        if (index < Count) memmove(Items + index + 1, Items + index, (Count - index) * sizeof(Wstring));
        new (Items + index) Wstring(text);
        ++Count;
    }
    void Prepend(Wstring const &text) {
        int index = 0;
        if (index > Count) index = Count;
        if (index >= Capacity) Grow_00768320();
        if (Count >= Capacity) Grow_00768320();
        if (index < Count) memmove(Items + index + 1, Items + index, (Count - index) * sizeof(Wstring));
        new (Items + index) Wstring(text);
        ++Count;
    }

};
#include "shared/wol_dictionary.hpp"
// Name sets: the value is a 4-byte payload that has not been identified.
class WolChannelNameSet : public WolDictionary<Wstring, int> {
public:
    WolChannelNameSet() : WolDictionary<Wstring, int>(Hash_Name_005c2ba0) {}
    bool Get_Pointer_00767570(Wstring const &key, int **value) const;
    bool Remove_007675e0(Wstring const &key, int *old_value);
    void Shrink_00767850();
    void Grow_00767900();
    unsigned int Key_Hash_007679a0(Wstring const &key) const;
    bool Add_00766070(Wstring const &key, int const &value);
    bool Contains(Wstring const &key) const {
        unsigned int hash = Hash(key);
        for (Node *node = Buckets[((1u << Bits) - 1) & hash]; node; node = node->Next) {
            if (node->Key == key) return true;
        }
        return false;
    }
};
// A second name table (0x00B29848): another 4-byte payload, a separate instance.
class WolNameTable : public WolDictionary<Wstring, unsigned int> {
public:
    WolNameTable() : WolDictionary<Wstring, unsigned int>(Hash_Name_005c2ba0) {}
    bool Get_Pointer(Wstring const &key,unsigned int **value) const {
        if(Count==0) return false;
        Node *node=Buckets[Key_Hash_00767cd0(key)];
        if(!node) return false;
        while(node && !(node->Key==key)) node=node->Next;
        if(!node) return false;
        *value=&node->Value;
        return true;
    }
    bool Get_Pointer_00767bb0(Wstring const &key, unsigned int **value) const;
    void Shrink_00767c20();
    unsigned int Key_Hash_00767cd0(Wstring const &key) const;
    void Clear_007662f0();
    bool Remove_Name(Wstring const &key) {
        if(Count==0) return false;
        float load=(float)(Count-1);
        load/=(float)BucketCount;
        unsigned int hash=Hash(key);
        unsigned int bucket=((1u<<Bits)-1)&hash;
        Node *head=Buckets[bucket];
        Node *previous=head;
        if(!head) return false;
        if(head->Key==key) {
            Node *old=Buckets[bucket];
            Node *next=old->Next;
            delete old;
            Buckets[bucket]=next;
            --Count;
            if(load<=ShrinkLimit) Shrink_00767c20();
            return true;
        }
        Node *node=head->Next;
        bool removed=false;
        while(node) {
            if(node->Key==key) {
                previous->Next=node->Next;
                --Count;
                delete node;
                removed=true;
                break;
            }
            previous=node;
            node=node->Next;
        }
        if(load<=ShrinkLimit) Shrink_00767c20();
        return removed;
    }

};
// Channel records by name (0x00B29478).
class WolChannelDictionary : public WolDictionary<Wstring, WOL::Channel> {
public:
    WolChannelDictionary() : WolDictionary<Wstring, WOL::Channel>(Hash_Name_005c2ba0) {}
    bool Remove_Channel(Wstring const &key) {
        if(Count==0) return false;
        float load=(float)(Count-1);
        load/=(float)BucketCount;
        unsigned int hash=Hash(key);
        unsigned int bucket=((1u<<Bits)-1)&hash;
        Node *head=Buckets[bucket];
        Node *previous=head;
        if(!head) return false;
        if(head->Key==key) {
            Node *old=Buckets[bucket];
            Node *next=old->Next;
            delete old;
            Buckets[bucket]=next;
            --Count;
            if(load<=ShrinkLimit) Shrink_00768010();
            return true;
        }
        Node *node=head->Next;
        bool removed=false;
        while(node) {
            if(node->Key==key) {
                previous->Next=node->Next;
                --Count;
                delete node;
                removed=true;
                break;
            }
            previous=node;
            node=node->Next;
        }
        if(load<=ShrinkLimit) Shrink_00768010();
        return removed;
    }
    bool Add(Wstring const &key,WOL::Channel const &value) {
        Node *node=new Node;
        node->Key=key;
        node->Value=value;
        node->Next=0;
        unsigned int bucket=Key_Hash(key);
        Node *head=Buckets[bucket];
        Buckets[bucket]=node;
        if(head) node->Next=head;
        ++Count;
        float load=(float)Count;
        load/=(float)Get_Size();
        if(load>=GrowLimit) Grow_Table();
        return true;
    }
    bool Get_Pointer_00767cf0(Wstring const &key, WOL::Channel **value) const;
    bool Remove_00767d60(Wstring const &key, WOL::Channel *old_value);
    void Shrink_00768010();
    void Clear_00766400();
};
class WolLadderCache : public WolDictionary<Wstring, WOL::Ladder> {
public:
    WolLadderCache() : WolDictionary<Wstring, WOL::Ladder>(Hash_Name_005c2ba0) {}
    bool Get_Pointer_007670f0(Wstring const &key, WOL::Ladder **value) const;
    bool Get_Copy(WOL::Ladder &entry,Wstring const &key) const {
        WOL::Ladder *value=0;
        if(!Get_Pointer(key,&value)) return false;
        if(value) entry=*value;
        return true;
    }

    unsigned int Key_Hash_00767550(Wstring const &key) const;
    bool Remove_00767160(Wstring const &key, WOL::Ladder *old_value);
    void Shrink_00767400();
    void Grow_007674b0();
    void Clear()
    {
        unsigned int index = 0;
        while (index < BucketCount) {
            Node *node = Buckets[index];
            while (node) {
                Node *old = node;
                node = node->Next;
                delete old;
            }
            Buckets[index++] = 0;
        }
        Count = 0;
        while (BucketCount > MinimumBuckets && !ResizeLocked) Shrink_00767400();
    }
    void Insert(Wstring const &key, WOL::Ladder const &value)
    {
        WOL::Ladder old_value;
        Remove_00767160(key, &old_value);
        Node *node = new Node;
        node->Key = key;
        node->Value = value;
        node->Next = 0;
        unsigned int hash = Hash(key);
        unsigned int bucket = (1u << Bits) - 1;
        bucket &= hash;
        Node *head = Buckets[bucket];
        Buckets[bucket] = node;
        if (head) node->Next = head;
        ++Count;
        if ((float)Count / (float)BucketCount >= GrowLimit) Grow_007674b0();
    }
    bool Contains(Wstring const &key) const {
        unsigned int hash = Hash(key);
        for (Node *node = Buckets[((1u << Bits) - 1) & hash]; node; node = node->Next) {
            if (node->Key == key) return true;
        }
        return false;
    }
};
struct __declspec(novtable) WolLadderClient : public IUnknown {
    virtual void __stdcall unknown_slot03() = 0;
    virtual void __stdcall unknown_slot04() = 0;
    virtual HRESULT __stdcall Request(char const *server, int port, char const *names, unsigned int game, int unknown1, int unknown2, int unknown3) = 0;
    // Pings an address with a timeout in milliseconds; the request's handle in *handle
    // (the reconnect dialog 0x00627350 pings the game address 0x00B2A758 every second;
    // name hypothesis: WOLAPI's INetUtil::RequestPing).
    virtual HRESULT __stdcall Request_Ping(char const *address, int timeout, int *handle) = 0;
    // Original004820DD passes only COM this and calls vtable+1C. The return
    // is ignored; void expresses only this caller, not original return behavior.
    virtual void __stdcall unknown_slot07_004820dd() = 0;
    virtual HRESULT __stdcall Get_Average_Ping(unsigned long address,int *ping) = 0;
    virtual HRESULT __stdcall unknown_slot09() = 0;
    virtual void __stdcall unknown_slot10() = 0;
    virtual HRESULT __stdcall Request_WDT_State(char const *host,int port,unsigned char request) = 0;
};
extern WolIntArray unknown_channel_requests_b29390;
extern WolChannelArray unknown_lobbies_b26c88;
extern WolChannelArray unknown_games_b29990;
extern WolStringArray unknown_game_names_b2a648;
extern WolStringArray unknown_pending_names_b29468;
extern WolStringArray unknown_strings_b26a50;
extern WolStringArray unknown_strings_b26570;
extern WolStringArray unknown_strings_b299b0;
extern WolStringArray unknown_strings_b29380;
extern WolStringArray unknown_strings_b26960;
extern WolStringArray unknown_strings_b2a6c8;
extern WolStringArray unknown_strings_b26580;
extern WolStringArray unknown_strings_b29000;
extern WolStringArray unknown_strings_b26920;
extern WolStringArray unknown_strings_b29838;
extern WolStringArray unknown_strings_b2a7d8;
// The buddy name whose request is in flight (0x00B26944) and the time it was sent (0x00B2A7F8).
extern Wstring unknown_wstring_b26944;
extern unsigned long unknown_b2a7f8;
// The lobby names (0x00B26C94; "Lob_33_<n>" channels show names[n % 8], with " <n / 8 + 1>" past the first eight).
extern char *unknown_lobby_names_b26c94[8];
// The display name of the channel a user was kicked from (0x00B2B3C0; written, never read).
extern char unknown_kick_channel_b2b3c0[64];
extern int unknown_b2abec;              // 0x00B2ABEC (OnGameStart: the game channel's +0x20 low byte; OnUserKick counts kick popups)
// The general WOnline timer (0x00B292E8; OnPaged restarts it at 300, OnGameStart at 0).
extern CDTimerClass<SystemTimerClass> unknown_timer_b292e8;
// A copy of a user list entry (0x00B2A658; Unknown_0074DA60 returns it).
extern WOL::User unknown_user_b2a658;
extern bool unknown_b2ac45;             // 0x00B2AC45 (a game has started)
extern bool unknown_b2ac44;             // 0x00B2AC44
extern bool unknown_b2ac04;             // 0x00B2AC04
extern int unknown_b2ac40;              // 0x00B2AC40 (2 once a game starts)
extern int unknown_login_state_00b2abe4;   // 0x00B2ABE4
extern unsigned int unknown_protocol_7fd370;   // 0x007FD370
extern int unknown_b2668c;              // 0x00B2668C (0x2300 when a game starts)
extern int unknown_b299d4;              // 0x00B299D4 (unknown_b299c0 +0x14)
extern unsigned int unknown_b299e0;     // 0x00B299E0 (unknown_b299c0 +0x20)
extern Wstring unknown_wstring_b26cb8;
extern char unknown_b2a808[];           // 0x00B2A808 (the first user's name when the game starts)
extern long unknown_game_start_time_b2a638;   // 0x00B2A638
extern char unknown_session_a3fc54[];   // 0x00A3FC54 (session +0x29BC)
extern int unknown_session_a40054;      // 0x00A40054 (session +0x2DBC)
void __fastcall Unknown_0074d7d0(WOL::User *users);
extern WOL::IDownload *unknown_download_a72d04;   // 0x00A72D04
extern HANDLE unknown_b26518;           // 0x00B26518 (set after the patches are downloaded)
// The dialog procedure of the download progress dialog 0xD3 (0x00748CD0).
int WINAPI Download_Dialog_Proc_00748cd0(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
// Three words 0x0073CFD0 combines (exclusive or; meaning unknown).
extern unsigned int unknown_b2ac18, unknown_b2ac1c, unknown_b2ac20;
// Opens a web page (0x0073C580; the second argument is unknown).
void __fastcall unknown_open_url_73c580(char const *url, int arg2);
extern int unknown_b2ac5c;              // 0x00B2AC5C (a language code: the registration page LANGCODE)
// The dialog procedure of dialog 0xCF (0x007485D0).
int WINAPI Unknown_Dialog_Proc_007485d0(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
// Channel tests of a game mode 4 session (0x0073C340..0x0073C400; false in other modes): +0x14 set or
// flag bit 8 (of a channel, of the current game channel unknown_b299c0), flag bit 8, 11 or 12 of a channel.
// The current game channel (0x00B299C0; unknown_b299c0 is its first word, unknown_b299d4/e0 its +0x14/+0x20).
extern WOL::Channel unknown_game_channel_b299c0;
bool __fastcall Unknown_0073c340(WOL::Channel const *channel);
bool Unknown_0073c370();
bool Unknown_0073c3a0();
bool __fastcall Unknown_0073c3c0(WOL::Channel const *channel);
bool __fastcall Unknown_0073c3e0(WOL::Channel const *channel);
bool __fastcall Unknown_0073c400(WOL::Channel const *channel);
int __fastcall Unknown_0074e070(void *unknown);
// Whether a nick is acceptable (0x00756790; hypothesis).
bool __fastcall Unknown_00756790(Wstring const &name);
void Unknown_00757380();                                 // 0x00757380
extern WolStringArray unknown_strings_b29980;
extern WolChannelNameSet unknown_channel_names_b293a0;
extern WolLadderCache *unknown_ladder_cache_b2ac24;
extern WolLadderClient *unknown_ladder_client_a72d00;
extern HANDLE unknown_channel_event_b26504;
extern int unknown_user_list_count_b2a728;
void __fastcall Unknown_00755180(HWND dialog);
void Unknown_0073ee80();
void Unknown_0073f8f0();
WIN32_IMPORT BOOL WINAPI KillTimer(HWND window, unsigned int id);

#include "shared/unknown_player_entry.hpp"
// WOnline non-polymorphic array: Count +0, Capacity +4, Items +8.
// WolUserArray is a descriptive recovery name; original template spelling is unknown.
// The user list order (0x007416D0): more of flags bits 0 (x4) and 1 (x2) first, then _stricmp of the names.
int __fastcall Compare_Users_007416d0(WOL::User const &left, WOL::User const &right);
class WolUserArray {
public:
    WolUserArray() : Count(0), Capacity(0), Items(0) {}
    ~WolUserArray() { Count = 0; operator delete(Items); }
    int Count, Capacity;
    WOL::User *Items;
    bool Insert_00765e90(WOL::User const &user, int index);
    bool Grow_00766e60();
    bool Shrink_00766f00();
    bool Get(WOL::User &user, int index) const; // 0x00766020
    bool Get(WOL::User *&user, int index) const {
        if (index >= 0 && index < Count) { user = Items + index; return true; }
        return false;
    }
    // Inline forms (the out-of-line COMDATs above are the same bodies where a caller did not inline them).
    bool Get_Copy(WOL::User &user, int index) const {
        if (index >= 0 && index < Count) { user = Items[index]; return true; }
        return false;
    }
    bool Grow() {
        if (Count < Capacity) return false;
        int capacity = Count * 2;
        if (capacity < 10) capacity = 10;
        WOL::User *items = (WOL::User *)operator new(capacity * sizeof(WOL::User));
        memset(items, 0, capacity * sizeof(WOL::User));
        if (Items) memcpy(items, Items, Count * sizeof(WOL::User));
        operator delete(Items);
        Items = items;
        Capacity = capacity;
        return true;
    }
    bool Insert(WOL::User const &user, int index) {
        if (index > Count) index = Count;
        if (index >= Capacity) Grow();
        Grow();
        if (index < Count) memmove(Items + index + 1, Items + index, (Count - index) * sizeof(WOL::User));
        new (Items + index) WOL::User(user);
        ++Count;
        return true;
    }
    bool Remove(int index) {
        if (Count == 0) return false;
        if (index < 0) index = 0;
        if (index >= Count) index = Count - 1;
        memmove(Items + index, Items + index + 1, (Count - (index + 1)) * sizeof(WOL::User));
        --Count;
        if (Count * 3 <= Capacity) Shrink_00766f00();
        return true;
    }
    // Inserts a copy of user (unlinked) before the first entry it sorts before (0x007416D0 order).
    void Add_Sorted(WOL::User const &user) {
        int index = Count;
        WOL::User other;
        for (int i = 0; i < Count; ++i) {
            Get_Copy(other, i);
            if (Compare_Users_007416d0(user, other) < 0) { index = i; break; }
        }
        WOL::User entry = user;
        entry.next = 0;
        Insert(entry, index);
    }
    int Find_Name(Wstring const &name) const {
        WOL::User *user = 0;
        for (int i = 0; i < Count; ++i) {
            Get(user, i);
            if (!_stricmp(name.Peek_Buffer(), user->name)) return i;
        }
        return -1;
    }
};
extern WolUserArray unknown_users_b2a728;
extern WolChannelNameSet unknown_known_names_b294b8;
extern WolLadderCache unknown_ladder_b296f8;
extern WolLadderCache unknown_ladder_b26970;
extern WolLadderCache unknown_ladder_b2ab98;
extern WolNameTable unknown_names_b29848;
extern WolChannelDictionary unknown_channels_b29478;
extern char unknown_query_b2b420[512];
extern int unknown_query_count_b2abf4;
extern int unknown_squad_query_b2abf8;  // 0x00B2ABF8 (a squad lookup of the local player is pending)
extern unsigned long unknown_squad_id_b2abfc;   // 0x00B2ABFC (the local player's squad id)
extern char unknown_squad_name_b2a8b0[];        // 0x00B2A8B0 (the local player's squad name)
extern int unknown_a72d08;
extern int unknown_a40230;
extern IPXAddressClass unknown_address_a3fbc8;
extern PlayerProfile *unknown_profile_b28cc4;
void Unknown_005c9700();
bool Unknown_0075a920();
extern "C" wchar_t *__cdecl wcscpy(wchar_t *destination, wchar_t const *source);
extern "C" unsigned long __stdcall ntohl(unsigned long value);

// The PCX image cache (UnknownBitmapWriter, 0x00A76378): shared/pcx_cache.hpp.
extern WOL::Channel unknown_pending_channel_b26a60;
extern int unknown_connection_result_b2ac10;
extern bool unknown_b2abd8;
extern bool unknown_b2abda;
extern bool unknown_7fd2fc;
extern int unknown_icons_b2acc4;
extern int unknown_icon_format_7fd304;
extern Wstring unknown_motd_b26954;
extern HANDLE unknown_b26500;
extern HANDLE unknown_b264f8;
// The text of a dialog item (0x00757CC0; name hypothesis).
Wstring __fastcall Unknown_00757cc0(HWND item);
// Sends text to a dialog control with message 0x4B4 (WM_USER + 0xB4; the page dialogs' reply line, hypothesis).
inline void Set_Edit_Text(HWND edit, Wstring const &text)
{
    SendMessageA(edit, 0x4b4, 0, (LPARAM)text.Peek_Buffer());
}
// The procedure of the page reply dialog 0x11E (0x00757D80).
int WINAPI Page_Dialog_Proc_00757d80(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
extern HANDLE unknown_b26530;           // 0x00B26530 (set when the local user's locale or team arrives)
extern HANDLE unknown_b2651c;           // 0x00B2651C (set when a net status arrives while disconnecting)
extern HRESULT unknown_net_status_b2ac00;   // 0x00B2AC00 (that net status)
extern wchar_t unknown_connection_error_b2a8ec[];
extern "C" wchar_t *__cdecl wcscpy(wchar_t *destination, wchar_t const *source);

// WOnline helper: ECX is an output address (saved at 0x0074fcbc);
// return paths use AL. The original free-function name remains unknown.
bool __fastcall Find_Local_Address_0074fcb0(IPXAddressClass *address);

// Reads list-box item `index` into a wide string (0x00600F10).
LRESULT __fastcall unknown_get_list_item_wide_text(HWND window, WPARAM index, WideString &text);
// A file-static Wstring (0x00B29CD4; initializer 0x0073B8A0).
extern Wstring unknown_wstring_b29cd4;
// The index of the session player with this name (1: the local player; 0x0073D3F0).
int __fastcall Unknown_0073d3f0(Wstring const &name);
// Connects to a WOL server (0x007424C0; hypothesis).
bool __fastcall Unknown_007424c0(WOL::Server *server);

// RTTI0x007AF934; actual constructor/destructor establish one owned Wstring at+C.
#include "shared/wonline_dialog_control.hpp"
class WonlineStringDialogControl : public SimpleWonlineDialogControl {
public:
    WonlineStringDialogControl() {}
    virtual ~WonlineStringDialogControl() {}
    Wstring Text;
};
#endif
