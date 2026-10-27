// void MultiplayerSyncCommandClass::Execute(int key) const -- 0x0051D820
// Toggles the extra sync information (0x00AB62E8) and announces the new
// state in the message list (0x00A3DC70, Add_Message 0x005B4DA0).
#include "shared/command.hpp"
// @ref ?unknown_extra_sync_info_ab62e8@@3_NA=00ab62e8
// @ref ?Unknown_006FA180@@YIPAGPBD@Z=006fa180
// @ref ?Add_Message@UnknownMessageList_0051d820@@QAEPAXPBGH0HHH_N@Z=005b4da0
// @ref ?unknown_message_list_a3dc70@@3VUnknownMessageList_0051d820@@A=00a3dc70
// @ref ??_C@_0BD@DGNA@Extra?5sync?5info?5ON?$AA@=007dd5d0
// @ref ??_C@_0BE@KFNA@Extra?5sync?5info?5OFF?$AA@=007dd5bc

extern bool unknown_extra_sync_info_ab62e8;
// An ASCII string widened into a rotating static buffer (as in shared/ipx_manager.hpp).
wchar_t *__fastcall Unknown_006FA180(char const *text);

// The in-game message list (MessageListClass in Westwood's code; only the
// call used here).
class UnknownMessageList_0051d820 {
public:
    void *Add_Message(wchar_t const *name, int id, wchar_t const *text, int color, int style, int timeout,
                      bool single_player);
};
extern UnknownMessageList_0051d820 unknown_message_list_a3dc70;

void MultiplayerSyncCommandClass::Execute(int key) const
{
    unknown_extra_sync_info_ab62e8 = !unknown_extra_sync_info_ab62e8;
    if (unknown_extra_sync_info_ab62e8) {
        unknown_message_list_a3dc70.Add_Message(0, 0, Unknown_006FA180("Extra sync info ON"), 3, 0x4046, 150, false);
    } else {
        unknown_message_list_a3dc70.Add_Message(0, 0, Unknown_006FA180("Extra sync info OFF"), 3, 0x4046, 150, false);
    }
}
