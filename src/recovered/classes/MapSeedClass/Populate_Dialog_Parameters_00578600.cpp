#include "shared/unknown_geometry.hpp"
#include "shared/unknown_static_rect.hpp"
#include "shared/map_seed.hpp"
#include "shared/anim_type.hpp"
extern char const *unknown_time_labels_7e0b10[4];
// @ref ?unknown_time_labels_7e0b10@@=007e0b10
extern char const *unknown_size_labels_7e0b20[4];
// @ref ?unknown_size_labels_7e0b20@@=007e0b20
extern char const *unknown_map_type_labels_7e0ae4[5];
// @ref ?unknown_map_type_labels_7e0ae4@@=007e0ae4
extern char const *unknown_resource_labels_7e0af8[4];
// @ref ?unknown_resource_labels_7e0af8@@=007e0af8
extern char unknown_seed_text_a709c8[];
// @ref ?unknown_seed_text_a709c8@@=00a709c8
// @ref ?Theaters@@=0079ab68
// @ref ?Clamp_Parameters_00578d80@MapSeedClass@@=00578d80
void MapSeedClass::Populate_Dialog_Parameters_00578600(HWND dialog)
{
    Clamp_Parameters_00578d80();
    {
        HWND control=GetDlgItem(dialog,0x3ea);
        while(SendMessageA(control,0x146,0,0)>0) SendMessageA(control,0x144,0,0);
        for(int i=0;i<4;++i) {
            LRESULT item=SendMessageA(control,0x4c2,0,(LPARAM)StringTable::Load_String(unknown_time_labels_7e0b10[i],0,"D:\\Ra2\\MapGen.cpp",0x1277));
            SendMessageA(control,0x151,item,i);
        }
        LRESULT selected=SendMessageA(control,0x4be,0,(LPARAM)StringTable::Load_String(unknown_time_labels_7e0b10[Time],0,"D:\\Ra2\\MapGen.cpp",0x127b));
        SendMessageA(control,0x14e,selected,0);
    }
    {
        HWND control=GetDlgItem(dialog,0x406);
        while(SendMessageA(control,0x146,0,0)>0) SendMessageA(control,0x144,0,0);
        for(int i=0;i<4;++i) {
            LRESULT item=SendMessageA(control,0x4c2,0,(LPARAM)StringTable::Load_String(unknown_size_labels_7e0b20[i],0,"D:\\Ra2\\MapGen.cpp",0x1286));
            SendMessageA(control,0x151,item,i);
        }
        LRESULT selected=SendMessageA(control,0x4be,0,(LPARAM)StringTable::Load_String(unknown_size_labels_7e0b20[Width],0,"D:\\Ra2\\MapGen.cpp",0x128a));
        SendMessageA(control,0x14e,selected,0);
    }
    {
        HWND control=GetDlgItem(dialog,0x405);
        while(SendMessageA(control,0x146,0,0)>0) SendMessageA(control,0x144,0,0);
        for(int i=1;i<5;++i) {
            LRESULT item=SendMessageA(control,0x4c2,0,(LPARAM)StringTable::Load_String(unknown_map_type_labels_7e0ae4[i],0,"D:\\Ra2\\MapGen.cpp",0x1296));
            SendMessageA(control,0x151,item,i);
        }
        LRESULT selected=SendMessageA(control,0x4be,0,(LPARAM)StringTable::Load_String(unknown_map_type_labels_7e0ae4[MapType],0,"D:\\Ra2\\MapGen.cpp",0x129a));
        SendMessageA(control,0x14e,selected,0);
    }
    {
        HWND control=GetDlgItem(dialog,0x407);
        while(SendMessageA(control,0x146,0,0)>0) SendMessageA(control,0x144,0,0);
        for(int i=0;i<2;++i) {
            LRESULT item=SendMessageA(control,0x4c2,0,(LPARAM)StringTable::Load_String(Theaters[i].UIName,0,"D:\\Ra2\\MapGen.cpp",0x12a6));
            SendMessageA(control,0x151,item,i);
        }
        LRESULT selected=SendMessageA(control,0x4be,0,(LPARAM)StringTable::Load_String(Theaters[Theater].UIName,0,"D:\\Ra2\\MapGen.cpp",0x12aa));
        SendMessageA(control,0x14e,selected,0);
    }
    {
        HWND control=GetDlgItem(dialog,0x408);
        while(SendMessageA(control,0x146,0,0)>0) SendMessageA(control,0x144,0,0);
        for(int i=0;i<4;++i) {
            LRESULT item=SendMessageA(control,0x4c2,0,(LPARAM)StringTable::Load_String(unknown_resource_labels_7e0af8[i],0,"D:\\Ra2\\MapGen.cpp",0x12b5));
            SendMessageA(control,0x151,item,i);
        }
        LRESULT selected=SendMessageA(control,0x4be,0,(LPARAM)StringTable::Load_String(unknown_resource_labels_7e0af8[Resources],0,"D:\\Ra2\\MapGen.cpp",0x12b9));
        SendMessageA(control,0x14e,selected,0);
    }
    HWND seed=GetDlgItem(dialog,0x3fb);
    sprintf(unknown_seed_text_a709c8,"%d",Seed);
    SendMessageA(seed,0x4b4,0,(LPARAM)unknown_seed_text_a709c8);
    HWND players=GetDlgItem(dialog,0x3eb);
    SendMessageA(players,0x406,1,0x80002);
    SendMessageA(players,0x405,1,NumPlayers);
}
