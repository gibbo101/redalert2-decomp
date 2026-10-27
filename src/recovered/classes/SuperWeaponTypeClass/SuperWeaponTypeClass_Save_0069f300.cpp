// HRESULT __stdcall SuperWeaponTypeClass::Save(IStream *stream, BOOL clear_dirty) (0x0069F300)

HRESULT __stdcall SuperWeaponTypeClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = AbstractClass::Save(stream, clear_dirty);
    if (SUCCEEDED(result)) {
        result = S_OK;
    }
    return result;
}
