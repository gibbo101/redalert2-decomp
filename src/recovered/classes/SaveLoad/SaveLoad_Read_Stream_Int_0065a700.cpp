// HRESULT SavegameInformation::Read_Stream_Int(IStorage *storage, int id, int *value) (0x0065A700; name hypothesis)
// Reads a summary value stored as a 4-byte stream.
#include "shared/savegame_info.hpp"
#include "shared/com_ptr.hpp"

HRESULT SavegameInformation::Read_Stream_Int(IStorage *storage, int id, int *value)
{
    *value = 0;
    UnknownComPtr<IStream, &unknown_uuid_IStream> stream;
    HRESULT result = storage->OpenStream(Savegame_Stream_Name(id), 0, 0x10, 0, &stream);
    if (FAILED(result)) {
        return result;
    }
    result = stream.Checked()->Read(value, sizeof(int), 0);
    if (FAILED(result)) {
        return result;
    }
    return result;
}
