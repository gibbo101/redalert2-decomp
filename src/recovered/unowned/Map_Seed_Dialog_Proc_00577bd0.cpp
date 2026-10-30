// Map-seed dialog callback; message and control names follow the original dispatch.
#include "shared/win32_api.hpp"
#include "shared/unknown_map_generator.hpp"
#include "shared/map_preview.hpp"
#include "shared/mouse.hpp"
#include "shared/keyboard.hpp"
#include "shared/progress_screen.hpp"
#include "shared/id_source.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/string_table.hpp"
#include "shared/crt_memory.hpp"
#include "shared/owner_draw_dialog_control.hpp"

// Existing OwnerDraw default dialog procedure, declared here to avoid unrelated mouse statics.
int __fastcall unknown_dialog_proc_5ffb00(HWND,UINT,WPARAM,LPARAM);
extern int unknown_selection_7e0adc;
extern bool unknown_preview_flag_7e0ae0;
extern bool unknown_generate_flag_a70068;
extern char const unknown_description_label_7e14dc[];
extern char const unknown_mapgen_file_7e14f8[];
extern char const unknown_random_map_name_7e1608[];
extern char const unknown_random_map_file_7e15fc[];
// @ref ?unknown_selection_7e0adc@@3HA=007e0adc
// @ref ?unknown_preview_flag_7e0ae0@@3_NA=007e0ae0
// @ref ?unknown_generate_flag_a70068@@3_NA=00a70068
// @ref ?unknown_description_label_7e14dc@@3QBDB=007e14dc
// @ref ?unknown_mapgen_file_7e14f8@@3QBDB=007e14f8
// @ref ?unknown_random_map_name_7e1608@@3QBDB=007e1608
// @ref ?unknown_random_map_file_7e15fc@@3QBDB=007e15fc
// @ref ?unknown_dialog_proc_5ffb00@@=005ffb00
// @ref ?unknown_5e4720@OwnerDraw@@=005e4720

// The real map-seed load-or-prompt body is visible in this original unit.
inline bool MapSeedClass::Load_Or_Prompt_005791a0(char const *filename)
{
    if(filename)return Load(filename);
    return Load_Dialog_0053b190()!=0 ? true : false;
}

int __stdcall Map_Seed_Dialog_Proc_00577bd0(HWND window,UINT message,WPARAM wparam,LPARAM lparam)
{
    int result=unknown_dialog_proc_5ffb00(window,message,wparam,lparam);
    if(result)return result;
    LONG *state=(LONG *)GetWindowLongA(window,8);
    switch(message) {
    case 0xf:
        if(unknown_preview_a6fee4) {
            HWND handle=GetDlgItem(window,0x468);
            if(!OwnerDraw::unknown_5e4720(handle))unknown_preview_a6fee4->Draw_0061D460(window);
        }
        if(ProgressScreen.Has_Window())ProgressScreen.Draw_It(Point2D(-1,-1));
        ValidateRect(window,0);
        return 0;
    case 0x114:
        if(lparam && GetDlgCtrlID((HWND)lparam)==0x3eb) {
            HWND handle=GetDlgItem(window,0x6c5);
            if(handle)EnableWindow(handle,0);
            handle=GetDlgItem(window,0x6c3);
            if(handle)EnableWindow(handle,0);
            unknown_map_generator_a6fd68.SeedOptions.Read_Dialog_Parameters_00578420(window);
            InvalidateRect(window,0,0);
            return 0;
        }
        break;
    case 0x111:
        switch((int)(wparam & 0xffff)) {
        case 0x5c0:
            *state=2;
            return 1;
        case 0x3ea: case 0x405: case 0x406: case 0x407: case 0x408:
            if((unsigned short)(wparam>>16)==1) {
                HWND handle=GetDlgItem(window,0x6c5);
                if(handle)EnableWindow(handle,0);
                handle=GetDlgItem(window,0x6c3);
                if(handle)EnableWindow(handle,0);
                unknown_map_generator_a6fd68.SeedOptions.Read_Dialog_Parameters_00578420(window);
                InvalidateRect(window,0,0);
                return 0;
            }
            break;
        case 0x620:
            WWMouse->Hide_Mouse();
            if(unknown_preview_flag_7e0ae0)unknown_generate_flag_a70068=true;
            else {
                unknown_generate_flag_a70068=false;
                unknown_preview_flag_7e0ae0=true;
            }
            unknown_map_generator_a6fd68.SeedOptions.Read_Dialog_Parameters_00578420(window);
            EnableWindow(GetDlgItem(window,0x405),0);
            EnableWindow(GetDlgItem(window,0x3ea),0);
            EnableWindow(GetDlgItem(window,0x407),0);
            EnableWindow(GetDlgItem(window,0x406),0);
            EnableWindow(GetDlgItem(window,0x408),0);
            EnableWindow(GetDlgItem(window,0x3eb),0);
            EnableWindow(GetDlgItem(window,0x621),0);
            EnableWindow(GetDlgItem(window,0x620),0);
            EnableWindow(GetDlgItem(window,0x6c2),0);
            EnableWindow(GetDlgItem(window,0x6c3),0);
            EnableWindow(GetDlgItem(window,0x6c4),0);
            EnableWindow(GetDlgItem(window,0x6c5),0);
            EnableWindow(GetDlgItem(window,0x5c0),0);
            wcscpy(unknown_map_generator_a6fd68.SeedOptions.DescriptionBuffer,
                StringTable::Load_String(unknown_description_label_7e14dc,0,unknown_mapgen_file_7e14f8,0xed1));
            unknown_map_generator_a6fd68.Unknown_0057A0D0(1,(int)window);
            unknown_preview_a6fee4->Unknown_0061D660();
            EnableWindow(GetDlgItem(window,0x405),1);
            EnableWindow(GetDlgItem(window,0x3ea),1);
            EnableWindow(GetDlgItem(window,0x407),1);
            EnableWindow(GetDlgItem(window,0x406),1);
            EnableWindow(GetDlgItem(window,0x408),1);
            EnableWindow(GetDlgItem(window,0x3eb),1);
            EnableWindow(GetDlgItem(window,0x621),1);
            EnableWindow(GetDlgItem(window,0x620),1);
            EnableWindow(GetDlgItem(window,0x6c2),1);
            EnableWindow(GetDlgItem(window,0x6c3),1);
            EnableWindow(GetDlgItem(window,0x6c4),1);
            EnableWindow(GetDlgItem(window,0x6c5),1);
            EnableWindow(GetDlgItem(window,0x5c0),1);
            if(unknown_map_generator_a6fd68.unknown_178)delete (MapSeedClass *)unknown_map_generator_a6fd68.unknown_178;
            unknown_map_generator_a6fd68.unknown_178=(int)new MapSeedClass;
            memcpy((void *)unknown_map_generator_a6fd68.unknown_178,&unknown_map_generator_a6fd68.SeedOptions,sizeof(MapSeedClass));
            WWMouse->Show_Mouse();
            WWKeyboard->Clear();
            PostMessageA(window,0xf,0,0);
            return 0;
        case 0x621: {
            unknown_map_generator_a6fd68.SeedOptions.Read_Dialog_Parameters_00578420(window);
            unknown_map_generator_a6fd68.SeedOptions.Populate_Dialog_Parameters_00578600(window);
            unknown_map_generator_a6fd68.SeedOptions.Theater=((unsigned int)unknown_random_839218(0,100)>=50);
            unknown_map_generator_a6fd68.SeedOptions.MapType=unknown_random_839218(1,4);
            unknown_map_generator_a6fd68.SeedOptions.Time=unknown_random_839218(0,3);
            unknown_map_generator_a6fd68.SeedOptions.Resources=unknown_random_839218(0,3);
            unknown_map_generator_a6fd68.SeedOptions.Width=unknown_random_839218(0,3);
            unknown_map_generator_a6fd68.SeedOptions.Height=unknown_map_generator_a6fd68.SeedOptions.Width;
            unknown_map_generator_a6fd68.SeedOptions.Randomize_Parameters_005789f0(unknown_map_generator_a6fd68.SeedOptions.MapType);
            wcscpy(unknown_map_generator_a6fd68.SeedOptions.DescriptionBuffer,
                StringTable::Load_String(unknown_description_label_7e14dc,0,unknown_mapgen_file_7e14f8,0xed1));
            unknown_map_generator_a6fd68.SeedOptions.Seed=unknown_random_839218(0,65535);
            unknown_map_generator_a6fd68.SeedOptions.Clamp_Parameters_00578d80();
            unknown_map_generator_a6fd68.SeedOptions.Populate_Dialog_Parameters_00578600(window);
            delete unknown_preview_a6fee4;
            unknown_preview_a6fee4=0;
            HWND handle=GetDlgItem(window,0x6c5);
            if(handle)EnableWindow(handle,0);
            handle=GetDlgItem(window,0x6c3);
            if(handle)EnableWindow(handle,0);
            InvalidateRect(window,0,0);
            return 0;
        }
        case 0x6c3: {
            unknown_map_generator_a6fd68.SeedOptions.Read_Dialog_Parameters_00578420(window);
            unknown_map_generator_a6fd68.SeedOptions.Save_Dialog_0053b1b0(unknown_map_generator_a6fd68.SeedOptions.DescriptionBuffer);
            bool enable=unknown_map_generator_a6fd68.SeedOptions.Has_Saved_Games_0053c5c0();
            HWND handle=GetDlgItem(window,0x6c2);
            if(handle)EnableWindow(handle,enable);
            handle=GetDlgItem(window,0x6c4);
            if(handle==0)return 0;
            EnableWindow(handle,enable);
            return 0;
        }
        case 0x6c2: {
            unknown_map_generator_a6fd68.SeedOptions.Read_Dialog_Parameters_00578420(window);
            bool loaded=unknown_map_generator_a6fd68.SeedOptions.Load_Or_Prompt_005791a0(0);
            if(loaded) {
                unknown_preview_flag_7e0ae0=false;
                PostMessageA(window,0x111,0x620,(LPARAM)GetDlgItem(window,0x620));
            }
            while(WWMouse->Get_Mouse_State()!=0)WWMouse->Show_Mouse();
            unknown_map_generator_a6fd68.SeedOptions.Populate_Dialog_Parameters_00578600(window);
            return 0;
        }
        case 0x6c4: {
            unknown_map_generator_a6fd68.SeedOptions.Read_Dialog_Parameters_00578420(window);
            unknown_map_generator_a6fd68.SeedOptions.Delete_Dialog_0053b1e0();
            bool enable=unknown_map_generator_a6fd68.SeedOptions.Has_Saved_Games_0053c5c0();
            HWND handle=GetDlgItem(window,0x6c2);
            if(handle)EnableWindow(handle,enable);
            handle=GetDlgItem(window,0x6c4);
            if(handle==0)return 0;
            EnableWindow(handle,enable);
            return 0;
        }
        case 0x6c5:
            unknown_map_generator_a6fd68.SeedOptions.Read_Dialog_Parameters_00578420(window);
            if(unknown_flag_a40d13) {
                unknown_map_generator_a6fd68.Unknown_0057A0D0(0,(int)window);
                unknown_id_source_a3d290->Set_Scenario_Name_0065e730(unknown_random_map_name_7e1608);
                Write_Scenario_INI_0065f980(unknown_random_map_file_7e15fc,true);
            } else if(!unknown_preview_a6fee4 || !unknown_preview_a6fee4->Is_Present()) {
                unknown_map_generator_a6fd68.Unknown_0057A0D0(1,(int)window);
                if(unknown_flag_a40d13) {
                    unknown_id_source_a3d290->Set_Scenario_Name_0065e730(unknown_random_map_name_7e1608);
                    Write_Scenario_INI_0065f980(unknown_random_map_file_7e15fc,true);
                }
            }
            *state=1;
            return 1;
        }
        break;
    case 0x497: {
        unknown_selection_7e0adc=-1;
        HWND preview_handle=GetDlgItem(window,0x620);
        if(unknown_flag_a40d13)EnableWindow(preview_handle,0);
        else EnableWindow(preview_handle,1);
        if(unknown_map_generator_a6fd68.SeedOptions.Seed==-1) {
            unknown_map_generator_a6fd68.SeedOptions.Seed=unknown_id_source_a3d290->Random()(0,65535);
            unknown_generate_flag_a70068=true;
        }
        unknown_preview_flag_7e0ae0=true;
        unknown_map_generator_a6fd68.SeedOptions.Populate_Dialog_Parameters_00578600(window);
        bool enable=unknown_map_generator_a6fd68.SeedOptions.Has_Saved_Games_0053c5c0();
        HWND handle=GetDlgItem(window,0x6c2);
        if(handle)EnableWindow(handle,enable);
        handle=GetDlgItem(window,0x6c4);
        if(handle)EnableWindow(handle,enable);
        handle=GetDlgItem(window,0x6c5);
        if(handle)EnableWindow(handle,0);
        handle=GetDlgItem(window,0x6c3);
        if(handle)EnableWindow(handle,0);
        return 0;
    }
    }
    return 0;
}
