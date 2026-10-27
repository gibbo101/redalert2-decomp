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

void __stdcall _com_issue_error(HRESULT result);

#endif
