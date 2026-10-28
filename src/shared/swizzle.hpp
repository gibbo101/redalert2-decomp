// Swizzle.cpp (unit 0x0069F950-0x006A0261): the save-game pointer fix-up
// service. Loading code reports each saved object's old address with
// Here_I_Am and each loaded pointer field with Swizzle; Process_Tables sorts
// both tables by old address and writes every field's new address. Names
// after Westwood's SwizzleManagerClass/ISwizzle (YRpp), checked against the
// vtable 0x007AC330 and IID 0x007A2060.
#ifndef RA2_SHARED_SWIZZLE_HPP
#define RA2_SHARED_SWIZZLE_HPP

#include "shared/com_persist.hpp"
#include "shared/vector_class_decl.hpp"
#include "shared/vector_elements.hpp"

// {5FAFCA70-8B12-11D1-B708-00A024DDAFD1}
extern "C" GUID const IID_ISwizzle;    // 0x007A2060

struct __declspec(novtable) ISwizzle : public IUnknown {
    virtual HRESULT __stdcall Reset() = 0;
    virtual HRESULT __stdcall Swizzle(void **pointer) = 0;
    virtual HRESULT __stdcall Fetch_Swizzle_ID(void *pointer, long *id) = 0;
    virtual HRESULT __stdcall Here_I_Am(long id, void *pointer) = 0;
    virtual HRESULT __stdcall Save_Interface(IStream *stream, IUnknown *object) = 0;
    virtual HRESULT __stdcall Load_Interface(IStream *stream, GUID *riid, void **object) = 0;
    virtual HRESULT __stdcall Get_Save_Size(int *size) = 0;
};

class SwizzleManagerClass : public ISwizzle {
public:
    SwizzleManagerClass();                                                          // 0x0069FA60
    ~SwizzleManagerClass();                                                         // 0x0069FAB0

    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);      // 0x0069FD10
    virtual unsigned long __stdcall AddRef();                                      // 0x0069FD90
    virtual unsigned long __stdcall Release();                                     // 0x0069FDA0
    virtual HRESULT __stdcall Reset();                                              // 0x0069FB10
    virtual HRESULT __stdcall Swizzle(void **pointer);                              // 0x0069FB20
    virtual HRESULT __stdcall Fetch_Swizzle_ID(void *pointer, long *id);            // 0x0069FD70
    virtual HRESULT __stdcall Here_I_Am(long id, void *pointer);                    // 0x0069FBA0
    virtual HRESULT __stdcall Save_Interface(IStream *stream, IUnknown *object);    // 0x0069FDB0
    virtual HRESULT __stdcall Load_Interface(IStream *stream, GUID *riid, void **object);  // 0x0069FDC0
    virtual HRESULT __stdcall Get_Save_Size(int *size);                             // 0x0069FCF0

private:
    void Process_Tables();                                                          // 0x0069FC30

    DynamicVectorClass<SwizzlePointerClass> UnswizzledPointers;    // +0x04 fields to fix (old address, field)
    DynamicVectorClass<SwizzlePointerClass> SwizzledPointers;      // +0x1C objects (old address, new address)
};
extern SwizzleManagerClass SwizzleManager;     // 0x00ABD868

#endif
