// A minimal smart pointer for COM interfaces with the public behaviour of
// the compiler's COM support template (_com_ptr_t): it holds one interface
// pointer, queries for its interface when built or assigned from another
// interface pointer, releases what it holds, and reports failures other
// than E_NOINTERFACE through _com_issue_error (0x00795940). Reconstructed
// from those semantics only; it carries just the members whose inline
// expansions the game's locomotors and units use. Out-of-line instances
// (for example Release_Held 0x004A4D10 and Assign_Query 0x00454BF0) are
// library-derived template instances.
#ifndef RA2_SHARED_COM_PTR_HPP
#define RA2_SHARED_COM_PTR_HPP

#include "shared/com_persist.hpp"

#ifndef E_NOINTERFACE
#define E_NOINTERFACE ((HRESULT)0x80004002L)
#endif
#ifndef E_POINTER
#define E_POINTER ((HRESULT)0x80004003L)
#endif

void __stdcall _com_issue_error(HRESULT result);    // 0x00795940

// The interface IDs the compiler's __uuidof references (separate copies from
// the game's IID_ objects).
extern "C" GUID const unknown_uuid_IUnknown_7ce610;        // 0x007CE610
extern "C" GUID const unknown_uuid_IPersist_7cf208;        // 0x007CF208
extern "C" GUID const unknown_uuid_IPersistStream_7d5f38;  // 0x007D5F38
extern "C" GUID const unknown_uuid_ILocomotion_7ce600;     // 0x007CE600

struct UnknownLocomotionPtr;
struct ILocomotion;

template <class Interface, GUID const *iid>
class UnknownComPtr {
public:
    UnknownComPtr() : Pointer(0) {}
    // Built from another interface pointer: a query for this interface.
    template <class Other>
    UnknownComPtr(Other const &other) : Pointer(0)
    {
        if (other) {
            HRESULT result = Query(other);
            if (FAILED(result) && result != E_NOINTERFACE) {
                _com_issue_error(result);
            }
        }
    }
    // Built by creating an instance of a class (CreateInstance is out of
    // line: 0x0041B650 for ILocomotion).
    UnknownComPtr(GUID const &clsid, IUnknown *outer = 0, DWORD context = 7) : Pointer(0)
    {
        HRESULT result = CreateInstance(clsid, outer, context);
        if (FAILED(result) && result != E_NOINTERFACE) {
            _com_issue_error(result);
        }
    }
    // A copy takes its own reference.
    UnknownComPtr(UnknownComPtr const &other) : Pointer(other.Pointer)
    {
        if (Pointer != 0) {
            Pointer->AddRef();
        }
    }
    ~UnknownComPtr()
    {
        if (Pointer != 0) {
            Pointer->Release();
        }
    }

    operator Interface *() const { return Pointer; }
    Interface *operator->() const { return Pointer; }
    // The checked access (E_POINTER when empty).
    Interface *Checked() const
    {
        if (Pointer == 0) {
            _com_issue_error(E_POINTER);
        }
        return Pointer;
    }
    // Assignment of a held pointer: a new reference.
    UnknownComPtr &operator=(Interface *pointer)
    {
        if (Pointer != pointer) {
            Interface *old = Pointer;
            Pointer = pointer;
            if (Pointer != 0) {
                Pointer->AddRef();
            }
            if (old != 0) {
                old->Release();
            }
        }
        return *this;
    }
    UnknownComPtr &operator=(UnknownComPtr const &other) { return operator=(other.Pointer); }
    // _com_ptr_t::CreateInstance (out of line 0x0041B650 for ILocomotion;
    // the aircraft constructor expands it with CLSCTX_ALL).
    HRESULT CreateInstance(GUID const &clsid, IUnknown *outer, DWORD context)
    {
        HRESULT result;
        if (Pointer != 0) {
            Pointer->Release();
        }
        if (context & (CLSCTX_LOCAL_SERVER | 0x10)) {
            IUnknown *unknown;
            result = CoCreateInstance(clsid, outer, context, unknown_uuid_IUnknown_7ce610, (void **)&unknown);
            if (FAILED(result)) {
                return result;
            }
            result = OleRun(unknown);
            if (SUCCEEDED(result)) {
                result = unknown->QueryInterface(*iid, (void **)&Pointer);
            }
            unknown->Release();
        } else {
            result = CoCreateInstance(clsid, outer, context, *iid, (void **)&Pointer);
        }
        return result;
    }

    // Releases what is held inline (the locomotors' Save constructs through
    // Query and expands this; Release_Held stays out of line).
    void Attach(Interface *pointer)
    {
        if (Pointer != 0) {
            Pointer->Release();
        }
        Pointer = pointer;
    }
    // A query from a held locomotor (out of line in the original: 0x00454BF0
    // for IPersist).
    HRESULT Query(UnknownLocomotionPtr const &other);
    // Stand-in for the original's single generic _com_ptr_t converting
    // query (constructing an IPersist/IPiggyback pointer from another
    // _com_ptr_t), whose out-of-line instances are 0x00454BF0 (IPersist) and
    // 0x00454C70 (IPiggyback). FootClass::Locomotor is that template's
    // ILocomotion instance; the two ILocomotion stand-ins here are one type in
    // the original. The original's inlining of this query varies with the
    // caller's inline budget: e.g. 0x004C4C30 expands it inline while slots
    // 260/138/261 call the out-of-line copies. This explicit overload only
    // reproduces the out-of-line form.
    HRESULT Query(UnknownComPtr<ILocomotion, &unknown_uuid_ILocomotion_7ce600> const &other);
    // Out of line in the original (0x004A4D10 for IPersistStream,
    // 0x004A4D00 for IPersist in Drive.cpp, 0x004CDF80 for ILocomotion in
    // Foot.cpp).
    void Release_Held();
    // Gives up the held pointer without releasing it.
    Interface *Detach()
    {
        Interface *old = Pointer;
        Pointer = 0;
        return old;
    }
    // The address of the pointer, for an out parameter (releases what is held).
    Interface **operator&()
    {
        Release_Held();
        Pointer = 0;
        return &Pointer;
    }
    template <class Other>
    HRESULT Query(Other other)
    {
        Interface *pointer;
        HRESULT result = other->QueryInterface(*iid, (void **)&pointer);
        if (FAILED(result)) {
            Release_Held();
            Pointer = 0;
        } else {
            Attach(pointer);
        }
        return result;
    }

    Interface *Pointer;
};


#endif
