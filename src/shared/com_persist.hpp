// COM persistence interfaces (as in the Win32 SDK objidl.h) used by the
// game-object hierarchy: IPersist, IPersistStream and the IStream methods
// the objects call (Read slot 3, Write slot 4).
//
// The SDK declares interfaces __declspec(novtable): the original constructors
// store no vtable pointer for them (AbstractClass 0x0040FF10).
#ifndef RA2_SHARED_COM_PERSIST_HPP
#define RA2_SHARED_COM_PERSIST_HPP

#include "shared/com_api.hpp"
#include "shared/crt_memory.hpp"
#include "shared/win32_api.hpp"

typedef int BOOL;
#define S_OK ((HRESULT)0L)
#define S_FALSE ((HRESULT)1L)

union ULARGE_INTEGER {
    struct {
        unsigned long LowPart;
        unsigned long HighPart;
    };
    unsigned __int64 QuadPart;
};

inline int operator==(GUID const &a, GUID const &b)
{
    return !memcmp(&a, &b, sizeof(GUID));
}

struct __declspec(novtable) ISequentialStream : public IUnknown {
    virtual HRESULT __stdcall Read(void *buffer, unsigned long size, unsigned long *read) = 0;
    virtual HRESULT __stdcall Write(void const *buffer, unsigned long size, unsigned long *written) = 0;
};

// LARGE_INTEGER: shared/win32_api.hpp.

struct STATSTG;

struct __declspec(novtable) IStream : public ISequentialStream {
    virtual HRESULT __stdcall Seek(LARGE_INTEGER move, unsigned long origin, ULARGE_INTEGER *position) = 0;
    virtual HRESULT __stdcall SetSize(ULARGE_INTEGER size) = 0;
    virtual HRESULT __stdcall CopyTo(IStream *stream, ULARGE_INTEGER size, ULARGE_INTEGER *read,
                                     ULARGE_INTEGER *written) = 0;
    virtual HRESULT __stdcall Commit(unsigned long flags) = 0;
    virtual HRESULT __stdcall Revert() = 0;
    virtual HRESULT __stdcall LockRegion(ULARGE_INTEGER offset, ULARGE_INTEGER size, unsigned long type) = 0;
    virtual HRESULT __stdcall UnlockRegion(ULARGE_INTEGER offset, ULARGE_INTEGER size, unsigned long type) = 0;
    virtual HRESULT __stdcall Stat(STATSTG *stat, unsigned long flags) = 0;
    virtual HRESULT __stdcall Clone(IStream **stream) = 0;
};

struct __declspec(novtable) IPersist : public IUnknown {
    virtual HRESULT __stdcall GetClassID(GUID *clsid) = 0;
};

struct __declspec(novtable) IPersistStream : public IPersist {
    virtual HRESULT __stdcall IsDirty() = 0;
    virtual HRESULT __stdcall Load(IStream *stream) = 0;
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty) = 0;
    virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER *size) = 0;
};

// Interface IDs as the game's QueryInterface implementations compare them
// (0x007AFCE0, 0x007AFCD0, 0x007AFCC0: a second IID_IUnknown copy next to
// the UUID.LIB IPersist/IPersistStream IDs; _IID_IUnknown proper is
// 0x007CE610).
extern "C" GUID const IID_IUnknown_7afce0;     // 0x007AFCE0 {00000000-0000-0000-C000-000000000046}
extern "C" GUID const IID_IPersistStream;      // 0x007AFCD0 {00000109-0000-0000-C000-000000000046}
extern "C" GUID const IID_IPersist;            // 0x007AFCC0 {0000010C-0000-0000-C000-000000000046}

#endif
