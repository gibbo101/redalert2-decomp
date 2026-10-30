// HRESULT __stdcall AtlModuleInit(_ATL_MODULE *pM, _ATL_OBJMAP_ENTRY *p, HINSTANCE h) (0x0075D160)
// ATL: initializes the module record and calls each object map entry's ObjectMain(true).
#include "shared/atl_module.hpp"
#include "shared/com_persist.hpp"

extern "C" HRESULT __stdcall AtlModuleInit(_ATL_MODULE *pM, _ATL_OBJMAP_ENTRY *p, HINSTANCE h)
{
    if (pM == 0) return E_INVALIDARG;
    pM->m_pObjMap = p;
    pM->m_hInst = pM->m_hInstTypeLib = pM->m_hInstResource = h;
    pM->m_nLockCnt = 0;
    pM->m_hHeap = 0;
    InitializeCriticalSection(&pM->m_csTypeInfoHolder);
    InitializeCriticalSection(&pM->m_csWindowCreate);
    InitializeCriticalSection(&pM->m_csObjMap);
    pM->m_pCreateWndList = 0;
    pM->m_bDestroyHeap = true;
    pM->m_dwHeaps = 0;
    pM->m_nHeap = 0;
    pM->m_phHeaps = 0;
    pM->m_pTermFuncs = 0;
    if (pM->m_pObjMap != 0) {
        _ATL_OBJMAP_ENTRY *pEntry = pM->m_pObjMap;
        while (pEntry->pclsid != 0) {
            pEntry->pfnObjectMain(true);
            pEntry = _NextObjectMapEntry(pM, pEntry);
        }
    }
    return S_OK;
}
