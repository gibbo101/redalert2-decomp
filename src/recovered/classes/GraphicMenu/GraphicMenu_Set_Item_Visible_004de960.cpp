// void GraphicMenu::Set_Item_Visible(int id, bool visible) (0x004DE960): shows or hides every item with the id.
#include "shared/graphic_menu_class.hpp"
#include "shared/vector_cursor.hpp"
typedef VectorCursor<GraphicMenuItem *, DynamicVectorClass<GraphicMenuItem *> > GraphicMenuCursor;

void GraphicMenu::Set_Item_Visible(int id, bool visible)
{
    for (GraphicMenuCursor cursor(Items); cursor; cursor++) {
        if ((*cursor)->ID == id) {
            GraphicMenuItem *item = *cursor;
            item->Set_Visible(visible);
        }
    }
}
