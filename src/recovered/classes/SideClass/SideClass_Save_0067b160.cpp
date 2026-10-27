// HRESULT __stdcall SideClass::Save(IStream *stream, BOOL clear_dirty) (0x0067B160)
// The AbstractClass data, the house count and the houses.

HRESULT __stdcall SideClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = AbstractClass::Save(stream, clear_dirty);
    if (FAILED(result)) {
        return result;
    }
    int count = Houses.Count();
    stream->Write(&count, sizeof(count), 0);
    for (int index = 0; index < count; index++) {
        stream->Write(&Houses[index], sizeof(int), 0);
    }
    return S_OK;
}
