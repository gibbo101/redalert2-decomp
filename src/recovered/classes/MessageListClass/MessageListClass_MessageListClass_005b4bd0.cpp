// MessageListClass::MessageListClass() -- 0x005B4BD0
// Clears the list, the geometry and the selection range; the seven trailing words become 0x10001.
// The DynamicVectorClass members this unit's lists expand, defined before any other header includes the
// vector header (the unit's first source; shared/vector_class.hpp).
// MsgList.cpp members declared for this unit only (shared/message_list.hpp).
#define RA2_MESSAGE_LIST_UNIT
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_OBJECT
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/vector_class.hpp"
#include "shared/message_list.hpp"

MessageListClass::MessageListClass()
{
    First = 0;
    X = 0;
    Y = 0;
    MaxMessages = 0;
    MaxChars = 0;
    Height = 0;
    unknown_18 = false;
    IsEdit = false;
    AdjustEdit = false;
    EditX = 0;
    EditY = 0;
    EditLabel = 0;
    EditCurPos = 0;
    EditInitPos = 0;
    EditCursor = 0;
    Selection_First = 0;
    Selection_Last = 0;
    TextWidth = 0;
    EditBuf[0] = 0;
    OverflowBuf[0] = 0;
    for (int i = 0; i < 7; i++) {
        unknown_1480[i] = 0x10001;
    }
}
