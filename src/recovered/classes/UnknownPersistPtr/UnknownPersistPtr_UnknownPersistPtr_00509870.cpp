// Converts the held locomotor to IPersist (0x00509870).
// Original callers 0x005021DB and 0x00508B0B pass the address of FootClass::Locomotor.
#include "shared/infantry.hpp"
// @ref _unknown_uuid_IPersist_7cf208=007cf208
// @ref ?_com_issue_error@@YGXJ@Z=00795940
UnknownPersistPtr::UnknownPersistPtr(UnknownComPtr<ILocomotion, &unknown_uuid_ILocomotion_7ce600> const &other)
    : Pointer(0)
{
    if (other != 0) {
        IPersist *pointer;
        HRESULT result = other.Pointer->QueryInterface(unknown_uuid_IPersist_7cf208, (void **)&pointer);
        if (FAILED(result)) {
            if (Pointer != 0) {
                Pointer->Release();
            }
            Pointer = 0;
        } else {
            IPersist *acquired = pointer;
            if (Pointer != 0) {
                Pointer->Release();
            }
            Pointer = acquired;
        }
        if (FAILED(result) && result != E_NOINTERFACE) {
            _com_issue_error(result);
        }
    }
}
