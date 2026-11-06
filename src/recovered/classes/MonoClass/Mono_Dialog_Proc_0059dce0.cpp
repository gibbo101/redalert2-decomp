#define SOUND_PLAY_DECLARE_HANDLE_INIT
#include "shared/mono_window.hpp"
#include "shared/audio.hpp"
#include "shared/voc_class.hpp"
#include "shared/vox_class.hpp"
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
extern DynamicVectorClass<VoxClass *> unknown_VoxClass_list_00ad0930;
// @ref ?unknown_VoxClass_list_00ad0930@@3V?$DynamicVectorClass@PAVVoxClass@@@@A=00ad0930
struct PAINTSTRUCT { HDC hdc; BOOL erase; RECT paint; BOOL restore; BOOL update; unsigned char reserved[32]; };
WIN32_IMPORT HDC WINAPI BeginPaint(HWND window, PAINTSTRUCT *paint);
WIN32_IMPORT BOOL WINAPI EndPaint(HWND window, PAINTSTRUCT const *paint);
void Audio_Stop_All();
extern "C" {
extern AudioEventHandle mono_test_handle_a70e70;
extern AudioEventHandle *mono_test_handle_a70ef4;
extern int mono_voice_index_a70ef0;
extern int mono_voice_priority_a70efc;
extern int mono_stream_count_a70ef8;
extern int mono_audio_toggle_a70eec;
extern AudioStreamPlayer *mono_test_streams_a70dec[5];
extern int mono_voice_count_ad0940;
}
void __fastcall Mono_View_Page(int page);
MonoClass *__fastcall Mono_Page_0059da50(int page) { return unknown_mono_pages_a70e40[page]; }
namespace seed_0059da40 {
extern "C" unsigned int DAT_00a70f0c;
unsigned int FUN_0059da40() { return (unsigned int)unknown_mono_viewed_a70f0c; }
}
BOOL __stdcall Mono_Dialog_Proc_0059dce0(HWND dialog, unsigned int message, unsigned int key, long lparam)
{
    if (message==15) {
        PAINTSTRUCT paint;
        InvalidateRect(dialog,0,1);
        BeginPaint(dialog,&paint);
        MonoClass *page=(MonoClass *)seed_0059da40::FUN_0059da40();
        if (page) page->View();
        EndPaint(dialog,&paint);
        return 1;
    }
    if (message==258) {
        if (!mono_test_handle_a70ef4) {
            mono_test_handle_a70ef4=&mono_test_handle_a70e70;
            mono_test_handle_a70ef4->Init();
        }
        switch (key) {
        case '1':case '2':case '3':case '4':mono_voice_priority_a70efc=key-'1';return 0;
        case 'Q':case 'q':
            if (mono_voice_index_a70ef0>16 || mono_voice_index_a70ef0>=unknown_VoxClass_list_00ad0930.Count()) mono_voice_index_a70ef0=0;
            Speech_Play(mono_voice_index_a70ef0,1,mono_voice_priority_a70efc);
            ++mono_voice_index_a70ef0;
            break;
        case 'W':case 'w':
            if (mono_voice_index_a70ef0>16 || mono_voice_index_a70ef0>=unknown_VoxClass_list_00ad0930.Count()) mono_voice_index_a70ef0=0;
            Speech_Play(mono_voice_index_a70ef0,0,mono_voice_priority_a70efc);
            ++mono_voice_index_a70ef0;
            return 0;
        case 'E':case 'e':
            if (mono_voice_index_a70ef0>16 || mono_voice_index_a70ef0>=unknown_VoxClass_list_00ad0930.Count()) mono_voice_index_a70ef0=0;
            Speech_Play(mono_voice_index_a70ef0,2,mono_voice_priority_a70efc);
            ++mono_voice_index_a70ef0;
            return 0;
        case 'O':case 'o':
            if (mono_voice_index_a70ef0>16 || mono_voice_index_a70ef0>=unknown_VoxClass_list_00ad0930.Count()) mono_voice_index_a70ef0=0;
            Speech_Play(mono_voice_index_a70ef0,-1,-1);
            ++mono_voice_index_a70ef0;
            return 0;
        case 'L':case 'l':
            if (Audio_Event_Handle_Event(mono_test_handle_a70ef4)) Audio_Event_Handle_Finish(mono_test_handle_a70ef4);
            else Voc_Play(VocClass::From_Name("TestEnvelopeFShift"),1.0f,0x2000,mono_test_handle_a70ef4);
            return 0;
        case 'T':case 't':Voc_Play(VocClass::From_Name("TestEffect"),1.0f,0x2000,0);return 0;
        case '[':
            if (mono_stream_count_a70ef8<5) {
                AudioStreamPlayer *stream=Audio_Stream_Create(Audio_Get_Device(),5000);
                mono_test_streams_a70dec[mono_stream_count_a70ef8]=stream;
                if (stream) {
                    if (Audio_Stream_Open(stream,"intro.wav",1)) ++mono_stream_count_a70ef8;
                    else Audio_Stream_Destroy(mono_test_streams_a70dec[mono_stream_count_a70ef8]);
                }
            }
            return 0;
        case ']':
            if (mono_stream_count_a70ef8>0) {
                Audio_Stream_Stop(mono_test_streams_a70dec[--mono_stream_count_a70ef8]);
                Audio_Stream_Destroy(mono_test_streams_a70dec[mono_stream_count_a70ef8]);
            }
            return 0;
        case 'N':case 'n':mono_audio_toggle_a70eec=!mono_audio_toggle_a70eec;return 0;
        case 'S':case 's':Audio_Stop_All();return 0;
        case 'A':case 'a':
            Mono_View_Page(5);return 0;
        case 'I':case 'i':
            Mono_View_Page(7);return 0;
        case 'M':case 'm':
            Mono_View_Page(6);return 0;
        case ',':case '<': {
            int page=((MonoClass *)seed_0059da40::FUN_0059da40())->Get_Handle()+1;
            if (page==8)page=0;
            unknown_mono_viewed_a70f0c=Mono_Page_0059da50(page);
            ((MonoClass *)seed_0059da40::FUN_0059da40())->Clear();
            ((MonoClass *)seed_0059da40::FUN_0059da40())->Refresh(0,0,80,25);return 0;
        }
        case '.':case '>': {
            int page=((MonoClass *)seed_0059da40::FUN_0059da40())->Get_Handle()-1;
            if (page<0)page=7;
            unknown_mono_viewed_a70f0c=Mono_Page_0059da50(page);
            ((MonoClass *)seed_0059da40::FUN_0059da40())->Clear();
            ((MonoClass *)seed_0059da40::FUN_0059da40())->Refresh(0,0,80,25);return 0;
        }
        }
    }
    if (message==273) {
        Mono_Window_Hide();
        return 1;
    }
    return 0;
}

// @ref _mono_test_handle_a70e70=00a70e70
// @ref _mono_test_handle_a70ef4=00a70ef4
// @ref _mono_voice_index_a70ef0=00a70ef0
// @ref _mono_voice_priority_a70efc=00a70efc
// @ref _mono_stream_count_a70ef8=00a70ef8
// @ref _mono_audio_toggle_a70eec=00a70eec
// @ref _mono_test_streams_a70dec=00a70dec
// @ref _mono_voice_count_ad0940=00ad0940
// @ref ??_C@_09NOGH@intro?4wav?$AA@=007e2ac4
// @ref ??_C@_0BD@KMLH@TestEnvelopeFShift?$AA@=007e2adc
// @ref ??_C@_0L@HJPA@TestEffect?$AA@=007e2ad0
