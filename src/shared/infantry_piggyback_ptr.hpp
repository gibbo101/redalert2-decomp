#ifndef RA2_SHARED_INFANTRY_PIGGYBACK_PTR_HPP
#define RA2_SHARED_INFANTRY_PIGGYBACK_PTR_HPP
// Interface-specific recovered COM pointer API and destructor (0x00509860).
// Compiler COM support: preserves the reconstructed full pointer API and one-pointer layout.
#include "shared/infantry.hpp"
#include "shared/locomotion.hpp"
extern "C" GUID const unknown_uuid_IPiggyback_7cfc30;
template <>
class UnknownComPtr<IPiggyback, &unknown_uuid_IPiggyback_7cfc30> {
public:
    typedef IPiggyback Interface;
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
    ~UnknownComPtr();

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
                result = unknown->QueryInterface(unknown_uuid_IPiggyback_7cfc30, (void **)&Pointer);
            }
            unknown->Release();
        } else {
            result = CoCreateInstance(clsid, outer, context, unknown_uuid_IPiggyback_7cfc30, (void **)&Pointer);
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
        HRESULT result = other->QueryInterface(unknown_uuid_IPiggyback_7cfc30, (void **)&pointer);
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
