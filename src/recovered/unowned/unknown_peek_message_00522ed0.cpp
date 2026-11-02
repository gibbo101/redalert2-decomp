// BOOL __fastcall unknown_peek_message_522ed0(MSG *, HWND, UINT, UINT, UINT) -- 0x00522ED0
// The game's PeekMessage with Westwood's input recorder: while recording (mode 1) logs each cursor move
// and every message for a listed window (others are dropped and the next message is taken); while playing
// back (mode 2) dispatches only real WM_PAINTs, ends playback on Escape or at the end of the stream file
// (Audio_File_Close_Stream, expanded twice), and returns the recorded cursor positions and messages whose
// recorded message count has been reached (FALSE until then). Names are hypotheses.
#include "shared/audio_file.hpp"
#include "shared/mouse.hpp"
#include "shared/movie.hpp"
#include "shared/cd_timer.hpp"
WIN32_IMPORT BOOL WINAPI PeekMessageA(MSG *message, HWND window, UINT first, UINT last, UINT remove);
WIN32_IMPORT BOOL WINAPI GetCursorPos(POINT *point);
// @ref __imp__PeekMessageA@20=0079a464
// @ref __imp__GetCursorPos@4=0079a3a8
// @ref __imp__DispatchMessageA@4=0079a4b4
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?Frame@@3HA=00a40d2c
// @ref ?unknown_message_count_a52298@@3HA=00a52298
// @ref ?Audio_Queue_Copy@@YIHPAUAudioQueue@@PAXH@Z=00408e00
// @ref ?unknown_audio_file_lock_a52268@@3UCRITICAL_SECTION@@A=00a52268

BOOL __fastcall unknown_peek_message_522ed0(MSG *message, HWND window, UINT first, UINT last, UINT remove)
{
    BOOL result;

    if (DAT_00a522ac == 1 && WWMouse != 0) {
        POINT point;
        GetCursorPos(&point);
        DAT_00a5229c = point.x;
        DAT_00a522a0 = point.y;
        WWMouse->Convert_Coordinate(DAT_00a5229c, DAT_00a522a0);
        if (DAT_00a5229c != DAT_00a522a4 || DAT_00a522a0 != DAT_00a522a8) {
            AudioFileCursorRecord record;
            record.Header.Type = 1;
            record.Header.Count = unknown_message_count_a52298;
            record.Header.Frame = Frame;
            EnterCriticalSection(&unknown_audio_file_lock_a52268);
            WWMouse->Set_Mouse_XY(DAT_00a5229c, DAT_00a522a0);
            record.X = DAT_00a5229c;
            record.Y = DAT_00a522a0;
            DAT_00a522a4 = DAT_00a5229c;
            DAT_00a522a8 = DAT_00a522a0;
            LeaveCriticalSection(&unknown_audio_file_lock_a52268);
            Audio_Queue_Copy(DAT_00a522c8, &record, sizeof(record));
        }
    }

    for (;;) {
        if (DAT_00a522ac == 2) {
            while (PeekMessageA(message, 0, 0, 0, 1)) {
                if (message->message == 0x100 && message->wParam == 0x1B) {
                    Audio_File_Close_Stream();
                    goto again;
                }
                if (message->message == 0x0F) {
                    DispatchMessageA(message);
                }
            }
            for (;;) {
                if (DAT_00a522e0 == 0) {
                    int available = Audio_Queue_Available(DAT_00a522cc);
                    if (available == 0) {
                        if (DAT_00a522d4 != 0) {
                            Audio_File_Close_Stream();
                            goto again;
                        }
                        continue;
                    }
                    if ((unsigned int)available < sizeof(AudioFileRecordHeader)) {
                        continue;
                    }
                    Audio_Queue_Copy(DAT_00a522cc, &DAT_00a521d0, sizeof(AudioFileRecordHeader));
                    DAT_00a522e0 = 1;
                }
                if (DAT_00a521d0.Count > (unsigned int)unknown_message_count_a52298) {
                    return 0;
                }
                DAT_00a522e0 = 0;
                if (DAT_00a521d0.Type == 1) {
                    POINT point;
                    Audio_Queue_Copy(DAT_00a522cc, &point, sizeof(point));
                    EnterCriticalSection(&unknown_audio_file_lock_a52268);
                    DAT_00a5229c = point.x;
                    DAT_00a522a0 = point.y;
                    if (WWMouse != 0) {
                        WWMouse->Set_Mouse_XY(point.x, point.y);
                    }
                    LeaveCriticalSection(&unknown_audio_file_lock_a52268);
                    continue;
                }
                Audio_Queue_Copy(DAT_00a522cc, message, sizeof(MSG));
                int index = (int)message->hwnd;
                HWND hwnd;
                if (DAT_00a522b0 != 0 && index >= 0 && index < DAT_00a521dc) {
                    hwnd = (HWND)((int *)DAT_00a522b4)[index];
                } else {
                    hwnd = 0;
                }
                message->hwnd = hwnd;
                if (message->hwnd != 0) {
                    result = 1;
                    goto recorded;
                }
            }
        }
        result = PeekMessageA(message, window, first, last, remove);
recorded:
        if (DAT_00a522ac != 1 || !result) {
            return result;
        }
        {
            int index = Audio_File_Find((int)message->hwnd);
            if (index >= 0) {
                AudioFileMessageRecord record;
                record.Header.Count = unknown_message_count_a52298;
                record.Header.Type = 0;
                record.Header.Frame = Frame;
                record.Message = *message;
                record.Message.hwnd = (HWND)index;
                Audio_Queue_Copy(DAT_00a522c8, &record, sizeof(record));
                return result;
            }
        }
        if (!remove) {
            PeekMessageA(message, window, first, last, 1);
        }
again:
        ;
    }
}
