// HRESULT __stdcall HouseTypeClass::Save(IStream *stream, BOOL clear_dirty) (0x004FA150)
// The AbstractClass data, then each veteran list as a count and its entries.

HRESULT __stdcall HouseTypeClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = AbstractClass::Save(stream, clear_dirty);
    if (FAILED(result)) {
        return result;
    }
    int count = VeteranInfantry.Count();
    stream->Write(&count, sizeof(count), 0);
    for (int index = 0; index < count; index++) {
        stream->Write(&VeteranInfantry[index], sizeof(InfantryTypeClass *), 0);
    }
    count = VeteranUnits.Count();
    stream->Write(&count, sizeof(count), 0);
    for (index = 0; index < count; index++) {
        stream->Write(&VeteranUnits[index], sizeof(UnitTypeClass *), 0);
    }
    count = VeteranAircraft.Count();
    stream->Write(&count, sizeof(count), 0);
    for (index = 0; index < count; index++) {
        stream->Write(&VeteranAircraft[index], sizeof(AircraftTypeClass *), 0);
    }
    return S_OK;
}
