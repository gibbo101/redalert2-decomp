// ATL 3.0's module record (_ATL_MODULE, atlbase.h) and object map entries, as wonline.cpp's
// copy of AtlModuleInit (0x0075D160) uses them. Field names are ATL's.
#ifndef RA2_SHARED_ATL_MODULE_HPP
#define RA2_SHARED_ATL_MODULE_HPP

#include "shared/com_api.hpp"
#include "shared/win32_api.hpp"

struct _ATL_OBJMAP_ENTRY {
    GUID const *pclsid;                                         // +0x00
    void *pfnUpdateRegistry;                                    // +0x04
    void *pfnGetClassObject;                                    // +0x08
    void *pfnCreateInstance;                                    // +0x0C
    IUnknown *pCF;                                              // +0x10
    unsigned long dwRegister;                                   // +0x14
    void *pfnGetObjectDescription;                              // +0x18
    void *pfnGetCategoryMap;                                    // +0x1C (ATL 3.0; the 2.1 entry is 0x1C bytes)
    void (__stdcall *pfnObjectMain)(bool bStarting);            // +0x20
};
// A function AtlModuleTerm calls (ATL's _ATL_TERMFUNC_ELEM).
struct _ATL_TERMFUNC_ELEM {
    void (__stdcall *pFunc)(unsigned long dw);                  // +0x00
    unsigned long dw;                                           // +0x04
    _ATL_TERMFUNC_ELEM *pNext;                                  // +0x08
};
struct _ATL_MODULE {
    unsigned int cbSize;                                        // +0x00
    HINSTANCE m_hInst;                                          // +0x04
    HINSTANCE m_hInstResource;                                  // +0x08
    HINSTANCE m_hInstTypeLib;                                   // +0x0C
    _ATL_OBJMAP_ENTRY *m_pObjMap;                               // +0x10
    long m_nLockCnt;                                            // +0x14
    HANDLE m_hHeap;                                             // +0x18
    CRITICAL_SECTION m_csTypeInfoHolder;                        // +0x1C
    CRITICAL_SECTION m_csWindowCreate;                          // +0x34
    CRITICAL_SECTION m_csObjMap;                                // +0x4C
    unsigned long dwAtlBuildVer;                                // +0x64 (ATL 3.0 from here; 2.1 records end at 0x64)
    void *m_pCreateWndList;                                     // +0x68
    bool m_bDestroyHeap;                                        // +0x6C
    GUID *pguidVer;                                             // +0x70
    unsigned long m_dwHeaps;                                    // +0x74
    HANDLE *m_phHeaps;                                          // +0x78
    int m_nHeap;                                                // +0x7C
    _ATL_TERMFUNC_ELEM *m_pTermFuncs;                           // +0x80
};
#define E_INVALIDARG ((HRESULT)0x80070057L)
// The next object map entry: 2.1 records hold 0x1C-byte entries.
inline _ATL_OBJMAP_ENTRY *_NextObjectMapEntry(_ATL_MODULE *pM, _ATL_OBJMAP_ENTRY *pEntry)
{
    if (pM->cbSize == 0x64) return (_ATL_OBJMAP_ENTRY *)((unsigned char *)pEntry + 0x1C);
    return pEntry + 1;
}
extern "C" HRESULT __stdcall AtlModuleInit(_ATL_MODULE *pM, _ATL_OBJMAP_ENTRY *p, HINSTANCE h);   // 0x0075D160
extern "C" HRESULT __stdcall AtlModuleTerm(_ATL_MODULE *pM);    // 0x00765990
#ifdef RA2_ATL_COM_OBJECT_CREATE
extern "C" HRESULT __stdcall AtlAdvise(IUnknown *container, IUnknown *sink, GUID const &iid, unsigned long *cookie); // 0x0075D0D0
// ATL's module object (atlbase.h). Init stores the ATL 3.0 version GUID and registers the module globally.
class CComModule;
extern CComModule *_pModule;        // 0x00B2ACC0
extern GUID GUID_ATLVer30;          // 0x007FD528
class CComModule : public _ATL_MODULE {
public:
    HRESULT Init(_ATL_OBJMAP_ENTRY *entries, HINSTANCE instance)
    {
        pguidVer = &GUID_ATLVer30;
        _pModule = this;
        cbSize = sizeof(_ATL_MODULE);
        dwAtlBuildVer = 0x300;
        return AtlModuleInit(this, entries, instance);
    }
};
extern CComModule _Module;          // 0x00B292F8
#endif

#endif
