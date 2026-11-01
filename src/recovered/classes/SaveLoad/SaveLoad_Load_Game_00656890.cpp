// bool __fastcall Unknown_00656890(char const *filename) (0x00656890; TibSun saveload.cpp Load_Game)
// Reads the saved game's summary (Get_Savefile_Info 0x00657FA0, expanded here) for its game mode,
// opens the file's CONTENTS stream through a decompressing link stream and reads everything back
// (Get_All 0x00656B80), then rebuilds the derived state of the map and the sidebar. The two
// DebugString lines (release-build empty inlines, shared/saveload_lists.hpp) mirror TibSun's
// Save_Game ones; their sites give the original's inline budget (hypothesis: the text is unknown).
#include "shared/saveload_game.hpp"
#include "shared/com_ptr.hpp"
#include "shared/debug_printf.hpp"
#include "shared/swizzle.hpp"
#include "shared/progress_screen.hpp"
#include "shared/map_view.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/tiberium.hpp"
#include "shared/load_dlg.hpp"
#include "shared/saveload_lists.hpp"
// @ref ??_C@_0BE@MECH@?6LOADING?5GAME?5?$FL?$CFs?$FN?6?$AA@=007f1bd8
// @ref ??_C@_0BP@NMCE@LOADING?5GAME?5?$FL?$CFs?$FN?5?9?5Complete?6?6?$AA@=007f1bb8
// @ref ??_C@_1BC@MEJL@?$AAC?$AAO?$AAN?$AAT?$AAE?$AAN?$AAT?$AAS?$AA?$AA@=007f1b60
// @ref _CLSID_CStreamClass=007a1ab0
// @ref _unknown_uuid_IUnknown_7ce610=007ce610
// @ref _unknown_uuid_ILinkStream_7f1b50=007f1b50

bool __fastcall Get_All(IStream *stream, bool save_net);
void __fastcall Post_Load_Game_0065d2c0();             // 0x0065D2C0

bool __fastcall Unknown_00656890(char const *filename)
{
    wchar_t name[64];
    Debug_Printf("\nLOADING GAME [%s]\n", filename);
    SavegameInformation info;
    if (!Get_Savefile_Info(filename, info)) {
        return false;
    }
    unknown_game_mode_a3d298 = info.Get_Game_Type();
    SwizzleManager.Reset();

    UnknownComPtr<IStorage, &unknown_uuid_IStorage> storage;
    MultiByteToWideChar(0, 0, filename, -1, name, 64);
    if (FAILED(StgOpenStorage(name, 0, 0x20, 0, 0, &storage))) {
        return false;
    }

    UnknownComPtr<IStream, &unknown_uuid_IStream> content;
    if (FAILED(storage.Checked()->OpenStream(L"CONTENTS", 0, 0x10, 0, &content))) {
        return false;
    }

    UnknownComPtr<ILinkStream, &unknown_uuid_ILinkStream_7f1b50> link;
    link.CreateInstance(CLSID_CStreamClass, 0, 7);
    link.Checked()->Link_Stream(content);
    UnknownComPtr<IStream, &unknown_uuid_IStream_7d5988> stream(link);

    ProgressScreen.Init(100.0, 0, 0);
    DebugString("Calling Get_All()\n");
    Get_All(stream, false);
    DebugString("Unlinking content stream from decompressor\n");
    link.Checked()->Unlink_Stream(0);
    SwizzleManager.Reset();

    Post_Load_Game_0065d2c0();
    Map.Init_IO();
    Map.unknown_slot54(1);
    Map.unknown_slot34();
    TiberiumClass::Init_Growth();
    TiberiumClass::Init_Spread();
    Map.Unknown_00634030();
    unknown_flag_a40d04 = true;
    unknown_flag_a40380 = true;
    Unknown_Free_Art_Set_006F30F0();
    Debug_Printf("LOADING GAME [%s] - Complete\n\n", filename);
    return true;
}
