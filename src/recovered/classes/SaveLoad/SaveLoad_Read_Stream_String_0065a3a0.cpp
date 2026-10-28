// HRESULT SavegameInformation::Read_Stream_String(IStorage *storage, int id, char *buffer) (0x0065A3A0; name hypothesis)
// Reads a summary value stored as a wide-string stream (127 characters).
#include "shared/savegame_info.hpp"
#include "shared/com_ptr.hpp"

HRESULT SavegameInformation::Read_Stream_String(IStorage *storage, int id, char *buffer)
{
    UnknownComPtr<IStream, &unknown_uuid_IStream> stream;
    wchar_t text[128];
    buffer[0] = 0;
    HRESULT result = storage->OpenStream(Savegame_Stream_Name(id), 0, 0x10, 0, &stream);
    if (FAILED(result)) {
        return result;
    }
    wchar_t *character = text;
    for (;;) {
        result = stream.Checked()->Read(character, sizeof(wchar_t), 0);
        if (FAILED(result)) {
            return result;
        }
        if (*character == 0) {
            break;
        }
        character++;
    }
    WideCharToMultiByte(0, 0, text, -1, buffer, 0x7F, 0, 0);
    return result;
}
