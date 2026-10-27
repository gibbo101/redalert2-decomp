// CStreamClass (vtables 0x0079E704 IStream, 0x0079E6EC ILinkStream; RTTI):
// an IStream that forwards to a held inner stream and buffers through it.
// Layout from the destructor 0x00494860 and the IStream slots
// 0x00494970..0x00494FD0; names past the RTTI ones are hypotheses.
#ifndef RA2_SHARED_CSTREAM_HPP
#define RA2_SHARED_CSTREAM_HPP

#include "shared/unknown_globals.hpp"
#include "shared/com_persist.hpp"
#include "shared/win32_api.hpp"

#ifndef E_POINTER
#define E_POINTER ((HRESULT)0x80004003L)
#endif
#ifndef E_FAIL
#define E_FAIL ((HRESULT)0x80004005L)
#endif


// Count of live COM objects (shared with LocomotionClass AddRef/Release).

// Westwood's link interface (slots 3 and 4 of the 0x0079E6EC vtable:
// 0x00494A00, 0x00494A90). Method names follow the public YR headers and
// are hypotheses.
struct __declspec(novtable) ILinkStream : public IUnknown {
    virtual HRESULT __stdcall Link_Stream(IUnknown *stream) = 0;
    virtual HRESULT __stdcall Unlink_Stream(IUnknown **stream) = 0;
};

// The held inner stream, with the public behaviour of the compiler's
// _com_ptr_t<IStream>: a checked operator-> (E_POINTER through
// _com_issue_error when empty), Release() that empties it, and a destructor
// that releases what is held.
extern "C" GUID const unknown_uuid_IStream_7d5988;

class UnknownStreamPtr {
public:
    UnknownStreamPtr() : Pointer(0) {}
    ~UnknownStreamPtr()
    {
        if (Pointer != 0) {
            Pointer->Release();
        }
    }
    IStream *operator->() const
    {
        if (Pointer == 0) {
            _com_issue_error(E_POINTER);
        }
        return Pointer;
    }
    operator IStream *() const { return Pointer; }
    unsigned char operator==(int null_value) const; // actual checked-null operation004951D0

    void Release()
    {
        if (Pointer == 0) {
            _com_issue_error(E_POINTER);
        }
        Pointer->Release();
        Pointer = 0;
    }

    void Release_Held()
    {
        if (Pointer) Pointer->Release();
    }
    void Attach(IStream *pointer)
    {
        if (Pointer) Pointer->Release();
        Pointer = pointer;
    }
    HRESULT Query(IUnknown *other)
    {
        IStream *pointer;
        HRESULT result = other->QueryInterface(unknown_uuid_IStream_7d5988, (void **)&pointer);
        if (FAILED(result)) {
            Release_Held();
            Pointer = 0;
        } else {
            Attach(pointer);
        }
        return result;
    }
    UnknownStreamPtr &operator=(IUnknown *other)
    {
        HRESULT result = Query(other);
        if (FAILED(result) && result != (HRESULT)0x80004002L) {
            _com_issue_error(result);
        }
        return *this;
    }

    IStream *Pointer;
};

class CStreamClass : public IStream, public ILinkStream {
public:
    CStreamClass();
    // IUnknown (0x00494970 QueryInterface, 0x00494910 AddRef, 0x00494930 Release)
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    // ISequentialStream (0x00494B40, 0x00494CB0)
    virtual HRESULT __stdcall Read(void *buffer, unsigned long size, unsigned long *read);
    virtual HRESULT __stdcall Write(void const *buffer, unsigned long size, unsigned long *written);
    // IStream (0x00494DE0 .. 0x00494FD0)
    virtual HRESULT __stdcall Seek(LARGE_INTEGER move, unsigned long origin, ULARGE_INTEGER *position);
    virtual HRESULT __stdcall SetSize(ULARGE_INTEGER size);
    virtual HRESULT __stdcall CopyTo(IStream *stream, ULARGE_INTEGER size, ULARGE_INTEGER *read,
                                     ULARGE_INTEGER *written);
    virtual HRESULT __stdcall Commit(unsigned long flags);
    virtual HRESULT __stdcall Revert();
    virtual HRESULT __stdcall LockRegion(ULARGE_INTEGER offset, ULARGE_INTEGER size, unsigned long type);
    virtual HRESULT __stdcall UnlockRegion(ULARGE_INTEGER offset, ULARGE_INTEGER size, unsigned long type);
    virtual HRESULT __stdcall Stat(STATSTG *stat, unsigned long flags);
    virtual HRESULT __stdcall Clone(IStream **stream);
    // slot 14 (scalar deleting destructor 0x004950F0); destructor 0x00494860
    virtual ~CStreamClass();
    // ILinkStream
    virtual HRESULT __stdcall Link_Stream(IUnknown *stream);
    virtual HRESULT __stdcall Unlink_Stream(IUnknown **stream);

    // Writes buffered bytes through to the inner stream (0x00495000).
    HRESULT unknown_flush_495000(void *buffer, int size);
    // Writes out pending buffered bytes (expanded inline).
    HRESULT unknown_flush_pending();

    UnknownStreamPtr Stream;    // +0x08 the forwarded inner stream
    long RefCount;              // +0x0C
    bool unknown_10;            // +0x10 (Seek/SetSize refused while set)
    bool unknown_11;            // +0x11 buffered data pending
    int unknown_14;             // +0x14 buffered byte count
    void *unknown_18;           // +0x18
    void *unknown_1c;           // +0x1C
    void *unknown_20;           // +0x20
    unsigned long unknown_24;   // +0x24 compressed block size
    unsigned long unknown_28;   // +0x28 uncompressed block size
};

#endif
