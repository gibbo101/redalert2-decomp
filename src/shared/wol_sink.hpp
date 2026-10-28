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

#include "shared/unknown_globals.hpp"
#include "shared/wdt_state.hpp"
#include "shared/com_persist.hpp"
#include "shared/com_api.hpp"
#include "shared/win32_api.hpp"
#include "shared/string_table.hpp"
#include "shared/wstring.hpp"
#include "shared/wide_string.hpp"

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
struct Update;
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

// A WOL user (only the members WOnline.cpp reads here).
struct User {
    unsigned int flags;                 // +0x00
    char unknown_04[0x14 - 4];
    unsigned int unknown_14;
    unsigned long unknown_18;
    int unknown_1c;
    User *next;                         // +0x20
    char name[10];                      // +0x24
    char unknown_2e[0x57 - 0x2e];
    char unknown_57[0x6c - 0x57];
};

struct Channel {
    int unknown_00;
    char unknown_04[0x28 - 4];
    int ping;
    int unknown_2c;
    Channel *next;
    char name[0x10c - 0x34];
};
// Only slot 42 is called here; unused interface signatures are hypotheses.
struct __declspec(novtable) IChat : public IUnknown {
    virtual void __stdcall unknown_slot03() = 0;
    virtual void __stdcall unknown_slot04() = 0;
    virtual void __stdcall unknown_slot05() = 0;
    virtual void __stdcall unknown_slot06() = 0;
    virtual void __stdcall unknown_slot07() = 0;
    virtual void __stdcall unknown_slot08() = 0;
    virtual void __stdcall unknown_slot09() = 0;
    virtual void __stdcall unknown_slot10() = 0;
    virtual void __stdcall unknown_slot11() = 0;
    virtual void __stdcall unknown_slot12() = 0;
    virtual void __stdcall unknown_slot13() = 0;
    virtual HRESULT __stdcall unknown_slot14(User *user, char const *text) = 0;
    virtual void __stdcall unknown_slot15() = 0;
    virtual void __stdcall unknown_slot16() = 0;
    virtual void __stdcall unknown_slot17() = 0;
    virtual void __stdcall unknown_slot18() = 0;
    virtual void __stdcall unknown_slot19() = 0;
    virtual void __stdcall unknown_slot20() = 0;
    virtual void __stdcall unknown_slot21() = 0;
    virtual void __stdcall unknown_slot22() = 0;
    virtual HRESULT __stdcall Game_Icon(long id, long format, void **bitmap, void **palette, int *width, int *height) = 0;
    virtual void __stdcall unknown_slot24() = 0;
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
    virtual void __stdcall unknown_slot35() = 0;
    virtual void __stdcall unknown_slot36() = 0;
    virtual void __stdcall unknown_slot37() = 0;
    virtual void __stdcall unknown_slot38() = 0;
    virtual void __stdcall unknown_slot39() = 0;
    virtual void __stdcall unknown_slot40() = 0;
    virtual void __stdcall unknown_slot41() = 0;
    virtual HRESULT __stdcall unknown_slot42(char const *text) = 0;
    virtual void __stdcall unknown_slot43() = 0;
    virtual HRESULT __stdcall unknown_slot44(unsigned int value) = 0;
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
extern "C" long __cdecl time(long *timer);
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

void __fastcall Unknown_00698D00(int arg);              // 0x00698D00
void *__fastcall Unknown_00735940(int id);              // 0x00735940 (a dialog by id)
void __fastcall Unknown_007357E0(void *dialog, int arg);    // 0x007357E0
HWND Unknown_00735B10();                                // 0x00735B10 (the current dialog window)
void Unknown_0075B590();                                // 0x0075B590
void Unknown_0075B2D0();                                // 0x0075B2D0
void __fastcall Unknown_0073FEE0(int arg1, bool arg2);  // 0x0073FEE0
void __fastcall Unknown_00741750(WOL::User *user);      // 0x00741750 (a user left the channel)
// Adds a formatted line to the chat display (hypothesis; 0x005C2C80).
void __cdecl Unknown_005C2C80(int color, wchar_t const *format, ...);
// Converts a narrow string into wide characters (0x006FA0C0; -1: to its end).
void __fastcall Unknown_006FA0C0(wchar_t *buffer, char const *text, int length);
extern int unknown_color_7a7360;        // 0x007A7360 (a chat colour)
extern int unknown_color_7a736c;        // 0x007A736C (private action colour)
extern int unknown_color_7a7370;        // 0x007A7370 (public action colour)
extern int unknown_color_7a7364;        // 0x007A7364 (public message colour)
extern int unknown_color_7a7374;        // 0x007A7374 (public message colour for users with flag bit 0)
void __fastcall Unknown_0075B910(char const *message, bool arg2);   // 0x0075B910 (in-game message)
extern int unknown_b2a7e8;              // 0x00B2A7E8
extern char unknown_name_a3d3a0[];      // 0x00A3D3A0 (the local nick name)
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
extern WOL::IChat *unknown_chat_a72cfc;
extern Wstring unknown_wstring_b26cb8;
extern int unknown_a3d3bc;
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
    char unknown_08[0x10 - 8];
    int unknown_10;
    int Unknown_Value_10() const { return unknown_10; }
    char unknown_14[8];
    int unknown_1c;
    int unknown_20;
    char unknown_24[0x38 - 0x24];   // size 0x38 (operator new in Load_Default 0x00738670)
};
struct WolRegistryOptions {
    WolRegistryOptions() : Options(0), HasOptions(false) {}
    bool Read_004ff200();
    bool unknown_004ff2c0() const;
    unsigned int Options;
    bool HasOptions;
};
int __fastcall Save_Nickname_00745320(char const *nick, char const *password, bool arg, int arg2);
extern Wstring unknown_password_b2a63c;
extern int unknown_newnick_result_b2ac08;
extern bool unknown_7fd374;
extern void Unknown_0073c120();
int __fastcall Popup_005c3230(wchar_t const *text, int unknown, void (*callback)(), int flags);

#include "shared/random.hpp"
extern "C" void __cdecl srand(unsigned int seed);
extern "C" int __cdecl rand();
extern "C" long __cdecl atol(char const *text);
extern "C" void *__cdecl memcpy(void *destination, void const *source, unsigned int length);
#pragma intrinsic(memcpy)
// Non-polymorphic server array observed at 0x00b2a700.
class WolServerArray {
public:
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
    bool Grow_When_Full(); // capacity operation expanded inside original Insert
    bool Shrink_00766dc0();
};
class WolIntArray {
public:
    int Count;
    int Capacity;
    int *Items;
    bool Get_00768260(int &value, int index);
    bool Remove_007681a0(int index);
};
class WolStringArray {
public:
    int Count;
    int Capacity;
    Wstring *Items;
    bool Grow_00768320();
    bool Get(Wstring &text, int index) {
        if (index >= 0 && index < Count) { text = Items[index]; return true; }
        return false;
    }
    bool Insert(Wstring const &text, int index); // original complete method 0x007679c0
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
// Key and chain prefix only; the payload has not been identified.
class WolChannelNameSet {
public:
    struct Node { Wstring Key; int unknown_04; Node *Next; };
    Node **Buckets;
    unsigned int Count, BucketCount, Bits;
    char unknown_10[8];
    unsigned int (__fastcall *Hash)(Wstring const &key);
    bool Contains(Wstring const &key) const {
        unsigned int hash = Hash(key);
        for (Node *node = Buckets[((1u << Bits) - 1) & hash]; node; node = node->Next) {
            if (node->Key == key) return true;
        }
        return false;
    }
};
class WolLadderCache {
public:
    struct Node { Wstring Key; WOL::Ladder Value; Node *Next; };
    Node **Buckets;
    unsigned int Count;
    unsigned int BucketCount;
    unsigned int Bits;
    unsigned int unknown_10;
    bool ResizeLocked;
    char unknown_15[3];
    unsigned int (__fastcall *Hash)(Wstring const &key);
    void *unknown_1c;
    double ShrinkLimit;
    double GrowLimit;
    unsigned int MinimumBuckets;
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
private:
    // Slot position only: ABI/return/parameters unresolved; never invoked.
    // This private placeholder makes no claim about the original signature.
    virtual void __stdcall unknown_slot06_abi_unresolved() = 0;
public:
    // Original004820DD passes only COM this and calls vtable+1C. The return
    // is ignored; void expresses only this caller, not original return behavior.
    virtual void __stdcall unknown_slot07_004820dd() = 0;
};
extern WolIntArray unknown_channel_requests_b29390;
extern WolChannelArray unknown_lobbies_b26c88;
extern WolChannelArray unknown_games_b29990;
extern WolStringArray unknown_game_names_b2a648;
extern WolStringArray unknown_pending_names_b29468;
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
class WolUserArray {
public:
    int Count, Capacity;
    WOL::User *Items;
    bool Insert_00765e90(WOL::User const &user, int index);
    bool Grow_00766e60();
    bool Get(WOL::User &user, int index) const; // 0x00766020
    bool Get(WOL::User *&user, int index) const {
        if (index >= 0 && index < Count) { user = Items + index; return true; }
        return false;
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
extern char unknown_query_b2b420[512];
extern int unknown_query_count_b2abf4;
extern int unknown_a72d08;
extern int unknown_a72c68;
extern int unknown_a40230;
extern IPXAddressClass unknown_address_a3fbc8;
extern PlayerProfile *unknown_profile_b28cc4;
void __fastcall Unknown_005cd030(HWND dialog, bool value);
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
extern wchar_t unknown_connection_error_b2a8ec[];
extern "C" wchar_t *__cdecl wcscpy(wchar_t *destination, wchar_t const *source);

// WOnline helper: ECX is an output address (saved at 0x0074fcbc);
// return paths use AL. The original free-function name remains unknown.
bool __fastcall Find_Local_Address_0074fcb0(IPXAddressClass *address);

#endif
