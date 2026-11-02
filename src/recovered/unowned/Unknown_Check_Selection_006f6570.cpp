// void Unknown_006F6570() (0x006F6570)
// Checks the selection for the group command (hypothesis): with nothing
// selected, or with a selected object that answers no to slot 275, the
// matching message is shown (MSG:NothingSelected / MSG:AttackMoveUnsupported);
// otherwise the flag 0x00AC1330 is raised.
#include "shared/uicmnds.hpp"
#include "shared/string_table.hpp"
// @ref ?unknown_objects_a40c60@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00a40c60
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ?unknown_flag_ac1330@@3_NA=00ac1330
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?unknown_messages_a3dc70@@3UUnknownMessageList@@A=00a3dc70
// @ref ?Add_Message@UnknownMessageList@@QAEXHHPBGHHHH@Z=005b4da0
// @ref ??_C@_0BD@BJM@D?3?2Ra2?2UICmnds?4cpp?$AA@=007f8c10
// @ref ??_C@_0BE@GHHF@MSG?3NothingSelected?$AA@=007f8bfc
// @ref ??_C@_0BK@BJPP@MSG?3AttackMoveUnsupported?$AA@=007f8be0

void Unknown_006F6570()
{
    if (unknown_objects_a40c60.Count() == 0) {
        Show_Message(StringTable::Load_String("MSG:NothingSelected", 0, "D:\\Ra2\\UICmnds.cpp", 0x2E9), 0xF0);
    } else {
        int count = unknown_objects_a40c60.Count();
        for (int index = 0; index < count; index++) {
            ObjectClass *object = unknown_objects_a40c60[index];
            bool flag;
            if (object != 0) {
                flag = object->AbstractFlags.IsTechno;
            }
            if (object != 0 && flag) {
                if (!((TechnoClass *)object)->unknown_slot275()) {
                    Show_Message(StringTable::Load_String("MSG:AttackMoveUnsupported", 0, "D:\\Ra2\\UICmnds.cpp", 0x2EF), 0xF0);
                    return;
                }
            }
        }
    }
    unknown_flag_ac1330 = true;
}
