// HRESULT SavegameInformation::Read_Stream_Wide(IStorage *storage, int id, wchar_t *buffer) (0x0065A490; name hypothesis)
// Reads a summary value stored as a wide-string stream.
#include "shared/savegame_info.hpp"
#include "shared/com_ptr.hpp"

HRESULT SavegameInformation::Read_Stream_Wide(IStorage *storage, int id, wchar_t *buffer)
{
    buffer[0] = 0;
    UnknownComPtr<IStream, &unknown_uuid_IStream> stream;
    HRESULT result = storage->OpenStream(Savegame_Stream_Name(id), 0, 0x10, 0, &stream);
    if (FAILED(result)) {
        return result;
    }
    for (;;) {
        result = stream.Checked()->Read(buffer, sizeof(wchar_t), 0);
        if (FAILED(result)) {
            return result;
        }
        if (*buffer == 0) {
            break;
        }
        buffer++;
    }
    return result;
}
