// HRESULT SavegameInformation::Write_Stream_Int(IStorage *storage, int id, int value) (0x0065ACE0; name hypothesis)
// Writes a summary value as its own stream and commits it.
#include "shared/savegame_info.hpp"
#include "shared/com_ptr.hpp"

HRESULT SavegameInformation::Write_Stream_Int(IStorage *storage, int id, int value)
{
    UnknownComPtr<IFullStream, &unknown_uuid_IFullStream> stream;
    HRESULT result = storage->CreateStream(Savegame_Stream_Name(id), 0x12, 0, 0, (IStream **)&stream);
    if (FAILED(result)) {
        return result;
    }
    result = stream.Checked()->Write(&value, sizeof(value), 0);
    if (FAILED(result)) {
        return result;
    }
    result = stream.Checked()->Commit(0);
    if (FAILED(result)) {
        return result;
    }
    return result;
}
