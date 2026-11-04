#include "shared/wol_sink.hpp"
#include "shared/wol_ladder_list_cell.hpp"
#include "shared/pcx_cache.hpp"
#include "shared/wol_list_text.hpp"
#include "shared/string_table.hpp"
WideString __fastcall unknown_number_text_7710c0(int number);
void __fastcall Update_Buddy_Buttons_007561c0(HWND dialog);
void __fastcall Update_Buddy_Profile_007562b0(HWND dialog);
extern "C" long __cdecl atol(char const *text);
extern "C" int __cdecl strncmp(char const *a,char const *b,unsigned int count);
extern "C" char *__cdecl strncpy(char *out,char const *in,unsigned int count);
extern wchar_t buddy_00839d4c[];
// @ref ?buddy_00839d4c@@3PAGA=00839d4c
extern char buddy_007fd62c[];
// @ref ?buddy_007fd62c@@3PADA=007fd62c
extern char buddy_007ffb1c[];
// @ref ?buddy_007ffb1c@@3PADA=007ffb1c
extern char buddy_007ffb08[];
// @ref ?buddy_007ffb08@@3PADA=007ffb08
extern char buddy_007ffae0[];
// @ref ?buddy_007ffae0@@3PADA=007ffae0
extern char buddy_007ffaf0[];
// @ref ?buddy_007ffaf0@@3PADA=007ffaf0
extern char buddy_007ffabc[];
// @ref ?buddy_007ffabc@@3PADA=007ffabc
extern char buddy_007ffaa4[];
// @ref ?buddy_007ffaa4@@3PADA=007ffaa4
extern char buddy_007fd358[];
// @ref ?buddy_007fd358@@3PADA=007fd358
extern wchar_t buddy_007d64f4[];
// @ref ?buddy_007d64f4@@3PAGA=007d64f4
extern wchar_t buddy_007fd8b8[];
// @ref ?buddy_007fd8b8@@3PAGA=007fd8b8
extern char buddy_007eb25c[];
// @ref ?buddy_007eb25c@@3PADA=007eb25c
extern char buddy_007fd890[];
// @ref ?buddy_007fd890@@3PADA=007fd890
extern char buddy_007eb228[];
// @ref ?buddy_007eb228@@3PADA=007eb228
extern char buddy_007fd8a4[];
// @ref ?buddy_007fd8a4@@3PADA=007fd8a4
extern char buddy_007ffad4[];
// @ref ?buddy_007ffad4@@3PADA=007ffad4
extern char buddy_007eb218[];
// @ref ?buddy_007eb218@@3PADA=007eb218
extern char buddy_007eafb4[];
// @ref ?buddy_007eafb4@@3PADA=007eafb4
extern char buddy_007e7444[];
// @ref ?buddy_007e7444@@3PADA=007e7444
extern char buddy_007eb234[];
// @ref ?buddy_007eb234@@3PADA=007eb234
extern char buddy_007fd87c[];
// @ref ?buddy_007fd87c@@3PADA=007fd87c
extern char buddy_007fd864[];
// @ref ?buddy_007fd864@@3PADA=007fd864
extern int buddy_column_007fd308;
// @ref ?buddy_column_007fd308@@3HA=007fd308
extern int buddy_column_007fd30c;
// @ref ?buddy_column_007fd30c@@3HA=007fd30c
extern int buddy_column_007fd310;
// @ref ?buddy_column_007fd310@@3HA=007fd310
extern int buddy_column_007fd314;
// @ref ?buddy_column_007fd314@@3HA=007fd314
extern int buddy_column_007fd318;
// @ref ?buddy_column_007fd318@@3HA=007fd318
extern int buddy_column_007fd31c;
// @ref ?buddy_column_007fd31c@@3HA=007fd31c

void __fastcall Unknown_00755180(HWND dialog)
{
    HWND list=GetDlgItem(dialog,0x689);
    SendMessageA(list,0x49d,0,1);
    for(int i=0;i<unknown_strings_b26920.Count;++i) {
        Wstring buddy;
        unknown_strings_b26920.Get(buddy,i);
        WideString display=Wstring_To_Wide(buddy);
        unsigned int state=0;
        unknown_names_b29848.Get_Value(buddy,state);
        int row=SendMessageA(list,0x4c5,0,(LPARAM)buddy.Peek_Buffer());
        if(row==-1) row=SendMessageA(list,0x4c8,0,(LPARAM)buddy.Peek_Buffer());
        WolLadderListCell name;
        name.Flags=1; name.Text.Set(display.Get()); name.Secondary.Set(buddy_00839d4c);
        WolLadderListCell status;
        status.Flags=1; status.Secondary.Set(buddy_00839d4c);
        WolLadderListCell mode;
        mode.Flags=0; mode.Text.Set(buddy_00839d4c); mode.Secondary.Set(buddy_00839d4c);
        WolLadderListCell password;
        password.Flags=0; password.Text.Set(buddy_00839d4c); password.Secondary.Set(buddy_00839d4c);
        WolLadderListCell gameType;
        gameType.Flags=0; gameType.Text.Set(buddy_00839d4c); gameType.Secondary.Set(buddy_00839d4c);
        WolLadderListCell ping;
        ping.Flags=0; ping.Text.Set(buddy_00839d4c); ping.Secondary.Set(buddy_00839d4c);
        switch(state) {
        case 1:
            status.Text.Set(StringTable::Load_String(buddy_007ffb1c,0,buddy_007fd62c,0x5f37));
            name.unknown_0c=status.unknown_0c=0x808080; break;
        case 2:
            status.Text.Set(StringTable::Load_String(buddy_007ffb08,0,buddy_007fd62c,0x5f3d));
            name.unknown_0c=status.unknown_0c=0x808080; break;
        case 3:
            status.Text.Set(StringTable::Load_String(buddy_007ffae0,0,buddy_007fd62c,0x5f43));
            name.unknown_0c=status.unknown_0c=0xf0f0; break;
        case 7: case 8:
            status.Text.Set(StringTable::Load_String(buddy_007ffaf0,0,buddy_007fd62c,0x5f4a));
            name.unknown_0c=status.unknown_0c=0x80ff00; break;
        case 4: {
            WOL::Channel channel;
            memset(&channel,0,sizeof(channel));
            if(!unknown_channels_b29478.Get_Value(buddy,channel)) {
                status.Text.Set(StringTable::Load_String(buddy_007ffae0,0,buddy_007fd62c,0x5f63));
                name.unknown_0c=status.unknown_0c=0xf0f0;
            } else {
                if(channel.unknown_00==0 && strncmp(channel.channel_name,buddy_007fd358,strlen(buddy_007fd358))==0) {
                    int lobby=atol(channel.channel_name+strlen(buddy_007fd358));
                    int page=lobby/8;
                    WideString location((wchar_t const*)unknown_lobby_names_b26c94[lobby%8]);
                    if(page) {
                        location+=buddy_007d64f4;
                        location+=unknown_number_text_7710c0(page+1);
                    }
                    status.Text.Set(location.Get());
                } else status.Text.Set(Unknown_006FA180(channel.channel_name));
                name.unknown_0c=status.unknown_0c=0xff4000;
            }
            break;
        }
        case 5: {
            WOL::Channel game;
            memset(&game,0,sizeof(game));
            bool found=unknown_channels_b29478.Get_Value(buddy,game);
            if(found) { Wstring game_name(game.channel_name); found=unknown_games_b29990.Find_Name(game_name,game); }
            if(found) {
            char options[132];
            strncpy(options,game.exInfo,128);
            int first=0,second=0,third=0,fourth=0,fifth=0;
            Wstring rest;
            Parse_Channel_Info_0073d070(options,&first,&second,&third,&fourth,&fifth,&rest);
            unsigned int current=game.currentUsers-fourth+third;
            int reserved=(fourth!=0 || fifth!=0);
            unsigned int maximum=game.maxUsers-reserved;
            wchar_t details[80];
            swprintf(details,buddy_007fd8b8,game.channel_name,current,maximum);
            status.Text.Set(details);
            name.unknown_0c=status.unknown_0c=0xffff00;
            mode.Flags=2;
            if(game.unknown_14!=0) {
                mode.unknown_10=(int)unknown_bitmap_writer_a76378.Get_Image_0068ca40(buddy_007eb25c,0);
                mode.Secondary.Set(StringTable::Load_String(buddy_007fd890,0,buddy_007fd62c,0x5f87));
            } else if(game.unknown_20&0x100) {
                mode.unknown_10=(int)unknown_bitmap_writer_a76378.Get_Image_0068ca40(buddy_007eb228,0);
                mode.Secondary.Set(StringTable::Load_String(buddy_007fd8a4,0,buddy_007fd62c,0x5f8a));
            } else {
                mode.unknown_10=(int)unknown_bitmap_writer_a76378.Get_Image_0068ca40(buddy_007ffad4,0);
                mode.Secondary.Set(buddy_00839d4c);
            }
            if(game.unknown_20&0x600) {
                if(fourth==0 && fifth!=0) {
                    gameType.Flags=2;
                    gameType.unknown_10=(int)unknown_bitmap_writer_a76378.Get_Image_0068ca40(buddy_007eb218,0);
                } else {
                    gameType.Flags=2;
                    gameType.unknown_10=(int)unknown_bitmap_writer_a76378.Get_Image_0068ca40(buddy_007eafb4,0);
                }
            } else if(fourth==0 && fifth!=0) {
                gameType.Flags=2;
                gameType.unknown_10=(int)unknown_bitmap_writer_a76378.Get_Image_0068ca40(buddy_007e7444,0);
            }
            if(game.flags&0x100) {
                password.Flags=2;
                password.unknown_10=(int)unknown_bitmap_writer_a76378.Get_Image_0068ca40(buddy_007eb234,0);
                password.Secondary.Set(StringTable::Load_String(buddy_007fd87c,0,buddy_007fd62c,0x5faa));
            }
            ping.Flags=3;
            ping.unknown_14=game.ping;
            swprintf(details,StringTable::Load_String(buddy_007fd864,0,buddy_007fd62c,0x5faf),game.ping);
            ping.Secondary.Set(details);
            } else {
                status.Text.Set(StringTable::Load_String(buddy_007ffae0,0,buddy_007fd62c,0x5fb2));
                name.unknown_0c=status.unknown_0c=0xf0f0;
            }
            break;
        }
        case 6:
            status.Text.Set(StringTable::Load_String(buddy_007ffabc,0,buddy_007fd62c,0x5fb9));
            name.unknown_0c=status.unknown_0c=0x3050ff; break;
        default:
            status.Text.Set(StringTable::Load_String(buddy_007ffaa4,0,buddy_007fd62c,0x5fbf));
            name.unknown_0c=status.unknown_0c=0x808080; break;
        }
        SendMessageA(list,0x4a8,((unsigned short)row<<16) | ((unsigned short)buddy_column_007fd308),(LPARAM)&name);
        SendMessageA(list,0x4a8,((unsigned short)row<<16) | ((unsigned short)buddy_column_007fd30c),(LPARAM)&mode);
        SendMessageA(list,0x4a8,((unsigned short)row<<16) | ((unsigned short)buddy_column_007fd310),(LPARAM)&password);
        SendMessageA(list,0x4a8,((unsigned short)row<<16) | ((unsigned short)buddy_column_007fd314),(LPARAM)&gameType);
        SendMessageA(list,0x4a8,((unsigned short)row<<16) | ((unsigned short)buddy_column_007fd318),(LPARAM)&status);
        SendMessageA(list,0x4a8,((unsigned short)row<<16) | ((unsigned short)buddy_column_007fd31c),(LPARAM)&ping);
    }
    int wanted=-1;
    if(unknown_wstring_b29cd4.Length()>0) wanted=SendMessageA(list,0x4c5,0,(LPARAM)unknown_wstring_b29cd4.Peek_Buffer());
    if(wanted!=SendMessageA(list,0x188,0,0)) SendMessageA(list,0x186,wanted,0);
    SendMessageA(list,0x49d,0,0);
    InvalidateRect(list,0,0);
    Update_Buddy_Buttons_007561c0(dialog);
    Update_Buddy_Profile_007562b0(dialog);
}
