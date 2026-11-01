// The save/load unit's top-level game file operations (SaveLoad.cpp; TibSun saveload.cpp Save_Game and
// Load_Game): the structured-storage and link-stream declarations they use.
#ifndef RA2_SHARED_SAVELOAD_GAME_HPP
#define RA2_SHARED_SAVELOAD_GAME_HPP

#include "shared/savegame_info.hpp"
#include "shared/cstream.hpp"

// IStorage with the slots after OpenStream (objidl.h order).
struct __declspec(novtable) IFullStorage : public IStorage {
    virtual HRESULT __stdcall CreateStorage(wchar_t const *name, unsigned long mode, unsigned long reserved1,
                                            unsigned long reserved2, IStorage **storage) = 0;    // slot 5
    virtual HRESULT __stdcall OpenStorage(wchar_t const *name, IStorage *priority, unsigned long mode,
                                          wchar_t **exclude, unsigned long reserved, IStorage **storage) = 0;   // slot 6
    virtual HRESULT __stdcall CopyTo(unsigned long count, GUID const *exclude, wchar_t **names,
                                     IStorage *destination) = 0;                                  // slot 7
    virtual HRESULT __stdcall MoveElementTo(wchar_t const *name, IStorage *destination, wchar_t const *new_name,
                                            unsigned long flags) = 0;                             // slot 8
    virtual HRESULT __stdcall Commit(unsigned long flags) = 0;                                    // slot 9
};

// Creates a compound file (OLE32).
extern "C" __declspec(dllimport) HRESULT __stdcall StgCreateDocfile(wchar_t const *name, unsigned long mode,
                                                                    unsigned long reserved, IStorage **storage);
// The current time as a FILETIME (OLE32).
extern "C" __declspec(dllimport) HRESULT __stdcall CoFileTimeNow(FILETIME *time);

// The compressing link stream's class (CStreamClass, 0x007A1AB0; TibSun CLSID_CompressStream).
extern "C" GUID const CLSID_CStreamClass;
// __uuidof(ILinkStream) and __uuidof(IStream) as the smart pointers query them (separate copies from the
// game's IID_ILinkStream 0x007A1AA0; the ILinkStream copy 0x007F1B50 is in this unit's own .rdata).
extern "C" GUID const unknown_uuid_ILinkStream_7f1b50;
extern "C" GUID const unknown_uuid_IStream_7d5988;

// The save game's version stamp (0x007F1B18).
extern int unknown_savegame_version_7f1b18;

#endif
