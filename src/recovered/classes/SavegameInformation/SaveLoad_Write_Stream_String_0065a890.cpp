// HRESULT SavegameInformation::Write_Stream_String(IStorage *storage, int id, char const *text) (0x0065A890; name hypothesis)
// Writes a summary value as its own stream and commits it.
#include "shared/savegame_info.hpp"
#include "shared/com_ptr.hpp"

HRESULT SavegameInformation::Write_Stream_String(IStorage *storage, int id, char const *text)
{
    wchar_t wide[128];
    MultiByteToWideChar(0, 0, text, -1, wide, 0x80);
    UnknownComPtr<IFullStream, &unknown_uuid_IFullStream> stream;
    HRESULT result = storage->CreateStream(Savegame_Stream_Name(id), 0x12, 0, 0, (IStream **)&stream);
    if (FAILED(result)) {
        return result;
    }
    result = stream.Checked()->Write(wide, (wcslen(wide) + 1) * sizeof(wchar_t), 0);
    if (FAILED(result)) {
        return result;
    }
    result = stream.Checked()->Commit(0);
    if (FAILED(result)) {
        return result;
    }
    return result;
}
