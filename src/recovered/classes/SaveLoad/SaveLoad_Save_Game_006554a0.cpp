// bool __fastcall Unknown_006554A0(char const *filename, wchar_t const *description, int unknown) (0x006554A0;
// TibSun saveload.cpp Save_Game)
// Creates the save file, writes its summary (SavegameInformation 0x00659530), then writes everything
// (Put_All 0x006558B0) to its CONTENTS stream through a compressing link stream and commits the file.
// The DebugString lines (release-build empty inlines, shared/saveload_lists.hpp) are TibSun's up to the
// content stream; with them the inline budget is the original's (hypothesis: RA2 drops the later
// ones and prints the link failure through Debug_Printf).
#include "shared/saveload_game.hpp"
#include "shared/com_ptr.hpp"
#include "shared/debug_printf.hpp"
#include "shared/house.hpp"
#include "shared/abstract_type.hpp"
#include "shared/id_source.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/load_dlg.hpp"
#include "shared/saveload_lists.hpp"
// @ref ??_C@_0BI@MEME@?6SAVING?5GAME?5?$FL?$CFs?5?9?5?$CFs?$FN?6?$AA@=007f1b7c
// @ref ??_C@_0BO@GMCG@SAVING?5GAME?5?$FL?$CFs?$FN?5?9?5Complete?6?6?$AA@=007f1b1c
// @ref ??_C@_0BA@JBMB@?7?$CK?$CK?$CK?$CK?$CK?5FAILED?$CB?6?$AA@=007f1b3c
// @ref ??_C@_07BGIN@SUN?4EXE?$AA@=007f1b74
// @ref ??_C@_1BC@MEJL@?$AAC?$AAO?$AAN?$AAT?$AAE?$AAN?$AAT?$AAS?$AA?$AA@=007f1b60
// @ref _CLSID_CStreamClass=007a1ab0
// @ref _unknown_uuid_IUnknown_7ce610=007ce610
// @ref _unknown_uuid_ILinkStream_7f1b50=007f1b50

bool __fastcall Put_All(IStream *stream, int save_net);

bool __fastcall Unknown_006554A0(char const *filename, wchar_t const *description, int unknown)
{
    wchar_t name[64];
    Debug_Printf("\nSAVING GAME [%s - %s]\n", filename, description);
    DebugString("Creating DocFile\n");
    UnknownComPtr<IStorage, &unknown_uuid_IStorage> storage;
    MultiByteToWideChar(0, 0, filename, -1, name, 64);
    if (FAILED(StgCreateDocfile(name, 0x1012, 0, &storage))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }

    SavegameInformation info;
    info.Set_unknown_00(unknown_savegame_version_7f1b18);
    info.Set_Description(description);
    info.Set_unknown_04(1);
    info.Set_Player_Name(unknown_player_a35db4->Type->UIName);
    info.Set_unknown_188(unknown_id_source_a3d290->unknown_224c);
    info.Set_unknown_18c(unknown_id_source_a3d290->TechLevel);
    info.Set_unknown_2d4("SUN.EXE");
    info.Set_Game_Type(unknown_game_mode_a3d298);
    FILETIME time;
    CoFileTimeNow(&time);
    info.Set_Play_Time(time);
    info.Set_Start_Time(time);
    info.Set_Save_Time(time);
    DebugString("Saving version information\n");
    info.Save(storage);

    DebugString("Creating content stream\n");
    UnknownComPtr<IStream, &unknown_uuid_IStream> content;
    if (FAILED(storage.Checked()->CreateStream(L"CONTENTS", 0x1012, 0, 0, &content))) {
        DebugString("\t***** FAILED!\n");
        return false;
    }

    UnknownComPtr<ILinkStream, &unknown_uuid_ILinkStream_7f1b50> link;
    link.CreateInstance(CLSID_CStreamClass, 0, 7);
    if (FAILED(link.Checked()->Link_Stream(content))) {
        Debug_Printf("\t***** FAILED!\n");
        return false;
    }
    UnknownComPtr<IStream, &unknown_uuid_IStream_7d5988> stream(link);

    bool result = Put_All(stream, 0);

    if (FAILED(link.Checked()->Unlink_Stream(0))) {
        return false;
    }
    content.Release();
    if (FAILED(((IFullStorage *)storage.Checked())->Commit(0))) {
        return false;
    }
    Debug_Printf("SAVING GAME [%s] - Complete\n\n", filename, description);
    return result;
}
