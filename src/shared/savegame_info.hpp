// SavegameInformation: the summary stored with a saved game (a property
// set read by 0x00659A90 and written by 0x00659530; 0x3F4 bytes, layout from
// the constructor 0x00659240 and the accessors 0x006592B0-0x00659526).
// Class and member names are hypotheses (Yuri's Revenge reference names
// the class SavegameInformation).
#ifndef RA2_SHARED_SAVEGAME_INFO_HPP
#define RA2_SHARED_SAVEGAME_INFO_HPP

#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif

#include "shared/win32_api.hpp"

extern "C" char *__cdecl strncpy(char *destination, char const *source, unsigned count);
extern "C" wchar_t *__cdecl wcsncpy(wchar_t *destination, wchar_t const *source, unsigned count);

#include "shared/com_persist.hpp"

// The structured-storage interfaces as far as the save code calls them
// (slot order as in objidl.h).
struct __declspec(novtable) IStorage : public IUnknown {
    virtual HRESULT __stdcall CreateStream(wchar_t const *name, unsigned long mode, unsigned long reserved1,
                                           unsigned long reserved2, IStream **stream) = 0;     // slot 3
    virtual HRESULT __stdcall OpenStream(wchar_t const *name, void *reserved1, unsigned long mode,
                                         unsigned long reserved2, IStream **stream) = 0;       // slot 4
};
// IStream with the slots after Write (objidl.h order).
struct __declspec(novtable) IFullStream : public IStream {
    virtual HRESULT __stdcall Seek(__int64 move, unsigned long origin, unsigned __int64 *position) = 0;   // slot 5
    virtual HRESULT __stdcall SetSize(unsigned __int64 size) = 0;                                       // slot 6
    virtual HRESULT __stdcall CopyTo(IStream *stream, unsigned __int64 count, unsigned __int64 *read,
                                     unsigned __int64 *written) = 0;                                    // slot 7
    virtual HRESULT __stdcall Commit(unsigned long flags) = 0;                                         // slot 8
};
struct PROPSPEC {
    unsigned long ulKind;
    unsigned long propid;
};
struct PROPVARIANT {
    unsigned short vt;
    unsigned short wReserved1;
    unsigned short wReserved2;
    unsigned short wReserved3;
    union {
        long lVal;
        wchar_t *pwszVal;
        char *pszVal;
        FILETIME filetime;
    };
};
struct __declspec(novtable) IPropertyStorage : public IUnknown {
    virtual HRESULT __stdcall ReadMultiple(unsigned long count, PROPSPEC const *specs, PROPVARIANT *values) = 0;   // slot 3
    virtual HRESULT __stdcall WriteMultiple(unsigned long count, PROPSPEC const *specs, PROPVARIANT const *values,
                                            unsigned long first) = 0;                                          // slot 4
};
struct __declspec(novtable) IPropertySetStorage : public IUnknown {
    virtual HRESULT __stdcall Create(GUID const &fmtid, GUID const *clsid, unsigned long flags, unsigned long mode,
                                     IPropertyStorage **storage) = 0;      // slot 3
    virtual HRESULT __stdcall Open(GUID const &fmtid, unsigned long mode, IPropertyStorage **storage) = 0;    // slot 4
};

// The summary's stream names by property ID (0x007F1C10, 13 entries).
struct SavegameStreamName {
    int ID;
    wchar_t const *Name;
};
extern SavegameStreamName const unknown_savegame_streams_7f1c10[13];
// The stream name of a property ID (0 when unknown).
inline wchar_t const *__fastcall Savegame_Stream_Name(int id)
{
    for (int index = 0; index < 13; index++) {
        if (unknown_savegame_streams_7f1c10[index].ID == id) {
            return unknown_savegame_streams_7f1c10[index].Name;
        }
    }
    return 0;
}
extern "C" GUID const unknown_fmtid_7afd60;     // 0x007AFD60 (the summary property set)
extern "C" GUID const IID_IPropertySetStorage;      // 0x007AFD50 (SavegameInformation::Save queries the storage)
extern "C" GUID const unknown_uuid_IPropertySetStorage;   // (not referenced)
extern "C" GUID const unknown_uuid_IStorage;    // (not referenced: Get_Savefile_Info's pointer never queries)
extern "C" GUID const unknown_uuid_IStream;     // (not referenced: the pointers below never query)
extern "C" GUID const unknown_uuid_IPropertyStorage;

extern "C" unsigned __cdecl wcslen(wchar_t const *string);
extern "C" GUID const unknown_uuid_IFullStream;

class SavegameInformation {
public:
    SavegameInformation();                                      // 0x00659240
    long Load(IStorage *storage);                               // 0x00659A90 (HRESULT; the summary property set)
    long Save(IStorage *storage);                               // 0x00659530 (HRESULT; properties, then streams)

    // Summary values as streams of the storage or as properties of its
    // summary property set (ids: unknown_savegame_streams_7f1c10).
    HRESULT Read_Stream_String(IStorage *storage, int id, char *buffer);   // 0x0065A3A0
    HRESULT Read_Stream_Wide(IStorage *storage, int id, wchar_t *buffer);   // 0x0065A490
    HRESULT Read_Property_String(IPropertySetStorage *storage, int id, char *buffer);   // 0x0065A540
    HRESULT Read_Property_Wide(IPropertySetStorage *storage, int id, wchar_t *buffer);   // 0x0065A620
    HRESULT Read_Stream_Int(IStorage *storage, int id, int *value);   // 0x0065A700
    HRESULT Read_Property_Int(IPropertySetStorage *storage, int id, int *value);   // 0x0065A7C0
    HRESULT Read_Stream_Time(IStorage *storage, int id, FILETIME *time);   // 0x0065AEC0
    HRESULT Read_Property_Time(IPropertySetStorage *storage, int id, FILETIME *time);   // 0x0065AF80
    HRESULT Write_Stream_String(IStorage *storage, int id, char const *text);   // 0x0065A890
    HRESULT Write_Stream_Wide(IStorage *storage, int id, wchar_t const *text);   // 0x0065A9D0
    HRESULT Write_Property_String(IPropertySetStorage *storage, int id, char const *text);   // 0x0065AAD0
    HRESULT Write_Property_Wide(IPropertySetStorage *storage, int id, wchar_t const *text);   // 0x0065ABF0
    HRESULT Write_Stream_Int(IStorage *storage, int id, int value);   // 0x0065ACE0
    HRESULT Write_Property_Int(IPropertySetStorage *storage, int id, int value);   // 0x0065ADD0
    HRESULT Write_Stream_Time(IStorage *storage, int id, FILETIME const *time);   // 0x0065B060 (hypothesis: by pointer)
    HRESULT Write_Property_Time(IPropertySetStorage *storage, int id, FILETIME const *time);   // 0x0065B150

    void Set_unknown_04(int value);        // 0x006592B0
    int Get_unknown_04() const;             // 0x006592C0
    void Set_unknown_00(int value);        // 0x006592D0
    int Get_unknown_00() const;             // 0x006592E0
    void Set_Description(wchar_t const *text);                  // 0x006592F0
    wchar_t const *Get_Description() const;                     // 0x00659310
    void Set_Player_Name(wchar_t const *text);                  // 0x00659320
    wchar_t const *Get_Player_Name() const;                     // 0x00659350
    void Set_unknown_188(int value);                            // 0x00659360
    int Get_unknown_188() const;                                // 0x00659370
    void Set_unknown_18c(int value);                            // 0x00659380
    int Get_unknown_18c() const;                                // 0x00659390
    void Set_unknown_190(char const *text);                     // 0x006593A0
    char const *Get_unknown_190() const;                        // 0x006593D0
    void Set_unknown_294(char const *text);                     // 0x006593E0
    char const *Get_unknown_294() const;                        // 0x00659400
    void Set_unknown_2d4(char const *text);                     // 0x00659410
    char const *Get_unknown_2d4() const;                        // 0x00659440
    void Set_Start_Time(FILETIME const &time);                  // 0x00659450
    void Get_Start_Time(FILETIME &time) const;                  // 0x00659470
    void Set_Save_Time(FILETIME const &time);                   // 0x00659490
    void Get_Save_Time(FILETIME &time) const;                   // 0x006594B0
    void Set_Play_Time(FILETIME const &time);                   // 0x006594D0
    void Get_Play_Time(FILETIME &time) const;                   // 0x006594F0
    void Set_Game_Type(int type);                               // 0x00659510
    int Get_Game_Type() const;                                  // 0x00659520 (the game mode at 0x00A3D298)

    int unknown_00;                         // +0x000
    int unknown_04;                         // +0x004
    wchar_t Description[0x80];              // +0x008
    wchar_t PlayerName[0x40];               // +0x108
    int unknown_188;                        // +0x188 (-1)
    int unknown_18c;                        // +0x18C
    char unknown_190[0x104];                // +0x190
    char unknown_294[0x40];                 // +0x294
    char unknown_2d4[0x104];                // +0x2D4
    FILETIME StartTime;                     // +0x3D8 (hypothesis)
    FILETIME SaveTime;                      // +0x3E0 (hypothesis)
    FILETIME PlayTime;                      // +0x3E8 (hypothesis)
    int GameType;                           // +0x3F0
};

// Opens a compound file (OLE32; Get_Savefile_Info 0x00657FA0).
extern "C" __declspec(dllimport) HRESULT __stdcall StgOpenStorage(wchar_t const *name, IStorage *priority, unsigned long mode,
                                                                  wchar_t **exclude, unsigned long reserved, IStorage **storage);

// The SaveLoad.cpp unit's free functions (names hypotheses).
HRESULT __fastcall Skip_Objects(IStream *stream);                                  // 0x00654C40
class SavegameInformation;
bool __fastcall Get_Savefile_Info(char const *filename, SavegameInformation &info); // 0x00657FA0

#endif
