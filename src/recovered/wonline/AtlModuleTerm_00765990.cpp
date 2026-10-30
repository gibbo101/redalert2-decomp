// HRESULT __stdcall AtlModuleTerm(_ATL_MODULE *pM) (0x00765990)
// ATL: releases the class factories, calls each ObjectMain(false), runs the term functions and destroys the heaps.
#include "shared/atl_module.hpp"
#include "shared/com_persist.hpp"

extern "C" HRESULT __stdcall AtlModuleTerm(_ATL_MODULE *pM)
{
    if (pM == 0) return E_INVALIDARG;
    if (pM->m_pObjMap != 0) {
        _ATL_OBJMAP_ENTRY *pEntry = pM->m_pObjMap;
        while (pEntry->pclsid != 0) {
            if (pEntry->pCF != 0) pEntry->pCF->Release();
            pEntry->pCF = 0;
            pEntry->pfnObjectMain(false);
            pEntry = _NextObjectMapEntry(pM, pEntry);
        }
    }
    DeleteCriticalSection(&pM->m_csTypeInfoHolder);
    DeleteCriticalSection(&pM->m_csWindowCreate);
    DeleteCriticalSection(&pM->m_csObjMap);
    _ATL_TERMFUNC_ELEM *pElem = pM->m_pTermFuncs;
    _ATL_TERMFUNC_ELEM *pNext = 0;
    while (pElem != 0) {
        pElem->pFunc(pElem->dw);
        pNext = pElem->pNext;
        delete pElem;
        pElem = pNext;
    }
    if (pM->m_hHeap != 0 && pM->m_bDestroyHeap) {
        if (pM->m_phHeaps != 0) {
            for (unsigned long i = 0; i <= pM->m_dwHeaps; i++) HeapDestroy(pM->m_phHeaps[i]);
        }
        HeapDestroy(pM->m_hHeap);
    }
    return S_OK;
}
