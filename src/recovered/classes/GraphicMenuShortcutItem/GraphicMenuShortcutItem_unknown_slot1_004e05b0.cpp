// bool GraphicMenuShortcutItem::unknown_slot1(int key) (0x004E05B0)
// True when the item is visible and one of its shortcut keys is `key`.
// The cursor is used through a pointer, so its virtual slots stay calls.
#include "shared/graphic_menu.hpp"
#include "shared/vector_cursor.hpp"
// @ref ??_7?$VectorCursor@IV?$DynamicVectorClass@I@@@@6B@=007a2c08
// @ref ??_E?$VectorCursor@IV?$DynamicVectorClass@I@@@@UAEPAXI@Z=004e06a0
// @ref ??_G?$VectorCursor@IV?$DynamicVectorClass@I@@@@UAEPAXI@Z=004e06a0
// @ref ?Valid@?$VectorCursor@IV?$DynamicVectorClass@I@@@@UBE_NXZ=004e0690
// @ref ?Next@?$VectorCursor@IV?$DynamicVectorClass@I@@@@UAEAAV1@XZ=004e06c0
// @ref ?Prev@?$VectorCursor@IV?$DynamicVectorClass@I@@@@UAEAAV1@XZ=004e06d0
// @ref ??3@YAXPAX@Z=00781d3b
typedef VectorCursor<unsigned int, DynamicVectorClass<unsigned int> > KeyCursor;

bool GraphicMenuShortcutItem::unknown_slot1(int key)
{
    if (!Visible) {
        return false;
    }
    KeyCursor cursor(Keys);
    KeyCursor *at = &cursor;
    while (at->Valid() && at->Current() != key) {
        at->Next();
    }
    return at->Valid();
}
