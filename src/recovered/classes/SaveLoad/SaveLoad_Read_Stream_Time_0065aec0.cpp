// HRESULT SavegameInformation::Read_Stream_Time(IStorage *storage, int id, FILETIME *time) (0x0065AEC0; name hypothesis)
// Reads a summary value stored as an 8-byte FILETIME stream.
#include "shared/savegame_info.hpp"
#include "shared/com_ptr.hpp"

HRESULT SavegameInformation::Read_Stream_Time(IStorage *storage, int id, FILETIME *time)
{
    *(__int64 *)time = 0;
    UnknownComPtr<IStream, &unknown_uuid_IStream> stream;
    HRESULT result = storage->OpenStream(Savegame_Stream_Name(id), 0, 0x10, 0, &stream);
    if (FAILED(result)) {
        return result;
    }
    result = stream.Checked()->Read(time, sizeof(FILETIME), 0);
    if (FAILED(result)) {
        return result;
    }
    return result;
}
