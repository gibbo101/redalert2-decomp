// bool __fastcall Get_Savefile_Info(char const *filename, SavegameInformation &info) (0x00657FA0; name hypothesis)
// Opens a saved game's storage and reads its summary.
#include "shared/com_persist.hpp"
#include "shared/savegame_info.hpp"
#include "shared/com_ptr.hpp"
// @ref ?Load@SavegameInformation@@QAEJPAUIStorage@@@Z=00659a90

bool __fastcall Get_Savefile_Info(char const *filename, SavegameInformation &info)
{
    wchar_t wide[64];
    UnknownComPtr<IStorage, &unknown_uuid_IStorage> storage;
    MultiByteToWideChar(0, 0, filename, -1, wide, 64);
    if (FAILED(StgOpenStorage(wide, 0, 0x12, 0, 0, &storage))) {
        return false;
    }
    if (FAILED(info.Load(storage))) {
        return false;
    }
    return true;
}
