// void __fastcall Queue_Record() (0x00629ED0): this frame's unexecuted events to the record file.
#include "shared/queue.hpp"
// @ref ?Frame@@3HA=00a40d2c
// @ref ?DoList@@3V?$QueueClass@VEventClass@@$0EAAA@@@A=00866270
// @ref ?Write@CCFileClass@@UAEJPBXJ@Z=00469030
// @ref ?unknown_record_file_a3f59c@@3VCCFileClass@@A=00a3f59c

void __fastcall Queue_Record()
{
    int i, j;
    if (::Frame == 0 && unknown_game_mode_a3d298 != 0) {
        return;
    }
    j = 0;
    for (i = 0; i < DoList.Count; i++) {
        if (::Frame == DoList[i].Frame && !DoList[i].IsExecuted) {
            j++;
        }
    }
    unknown_record_file_a3f59c.Write(&j, sizeof(j));
    for (i = 0; i < DoList.Count; i++) {
        if (::Frame == DoList[i].Frame && !DoList[i].IsExecuted) {
            unknown_record_file_a3f59c.Write(&DoList[i], sizeof(EventClass));
            j--;
        }
    }
}
