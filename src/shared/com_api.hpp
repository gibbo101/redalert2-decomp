// Minimal COM declarations (as in the Win32 SDK) used by recovered source.
//
// CoCreateInstance and OleRun are ole32.dll imports (IAT 0x0079A5F0 and
// 0x0079A5F4, manifests/imports.json); _com_issue_error (0x00795940) is the
// VC6 COM support library's error raiser.
#ifndef RA2_SHARED_COM_API_HPP
#define RA2_SHARED_COM_API_HPP

typedef long HRESULT;

struct GUID {
    unsigned long Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char Data4[8];
};

#define SUCCEEDED(result) ((HRESULT)(result) >= 0)
#define FAILED(result) ((HRESULT)(result) < 0)
#define E_NOTIMPL ((HRESULT)0x80004001L)
#define E_NOINTERFACE ((HRESULT)0x80004002L)
#define E_POINTER ((HRESULT)0x80004003L)
#define CLSCTX_INPROC_SERVER 0x1
#define CLSCTX_INPROC_HANDLER 0x2
#define CLSCTX_LOCAL_SERVER 0x4
#define CLSCTX_ALL (CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER | CLSCTX_LOCAL_SERVER)

struct __declspec(novtable) IUnknown {
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object) = 0;
    virtual unsigned long __stdcall AddRef() = 0;
    virtual unsigned long __stdcall Release() = 0;
};

extern "C" GUID const IID_IUnknown;    // 0x007CE610

extern "C" __declspec(dllimport) HRESULT __stdcall CoCreateInstance(GUID const &clsid, IUnknown *outer,
                                                                    unsigned long context, GUID const &iid, void **object);
extern "C" __declspec(dllimport) HRESULT __stdcall OleRun(IUnknown *unknown);
// The application object the scripting interfaces return (0x0084C7DC; its address is the object:
// the exit path disconnects it; moved from shared/house.hpp).
extern IUnknown *unknown_application_84c7dc;
// The registrations Prog_End and the exit path revoke (ole32 and OLEAUT32 imports).
extern "C" __declspec(dllimport) HRESULT __stdcall CoRevokeClassObject(unsigned long registration);
extern "C" __declspec(dllimport) HRESULT __stdcall CoDisconnectObject(IUnknown *object, unsigned long reserved);
extern "C" __declspec(dllimport) void __stdcall OleUninitialize();
extern "C" __declspec(dllimport) HRESULT __stdcall RevokeActiveObject(unsigned long registration, void *reserved);

void __stdcall _com_issue_error(HRESULT result);

#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif
// ole32 and OLEAUT32 imports of the COM server registration (0x0068DC70, 0x0068E040); the
// type library is only loaded and released, so it is held as its IUnknown.
extern "C" __declspec(dllimport) int __stdcall StringFromGUID2(GUID const &guid, wchar_t *string, int length);
extern "C" __declspec(dllimport) HRESULT __stdcall LoadTypeLib(wchar_t const *file, IUnknown **library);

// The VC6 COM support smart pointer of IUnknown (comip.h's _com_ptr_t, IUnknownPtr):
// WinMain creates the game's own server object through it.
struct IUnknownPtr {
    IUnknown *Interface;    // +0x00

    void _Release();
    HRESULT CreateInstance(GUID const &clsid, IUnknown *outer, unsigned long context);    // 0x00691450
};

inline void IUnknownPtr::_Release()
{
    if (Interface != 0) {
        Interface->Release();
    }
}

#endif
