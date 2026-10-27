// HRESULT __stdcall HouseTypeClass::GetSizeMax(ULARGE_INTEGER *size) (0x004FA240)

HRESULT __stdcall HouseTypeClass::GetSizeMax(ULARGE_INTEGER *size)
{
    if (size == 0) {
        return E_POINTER;
    }
    size->HighPart = 0;
    size->LowPart = sizeof(HouseTypeClass) + 4;
    return S_OK;
}
