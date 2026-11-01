// GraphicMenuItem *GraphicMenu::Item_At(Point2D const &point) (0x004DEDC0): the first item containing the point, or 0.
#include "shared/graphic_menu_class.hpp"
#include "shared/vector_cursor.hpp"
// @ref ??_7?$VectorCursor@PAVGraphicMenuItem@@V?$DynamicVectorClass@PAVGraphicMenuItem@@@@@@6B@=007a2b84
// @ref ??_E?$VectorCursor@PAVGraphicMenuItem@@V?$DynamicVectorClass@PAVGraphicMenuItem@@@@@@UAEPAXI@Z=004defa0
// @ref ??_G?$VectorCursor@PAVGraphicMenuItem@@V?$DynamicVectorClass@PAVGraphicMenuItem@@@@@@UAEPAXI@Z=004defa0
// @ref ?Valid@?$VectorCursor@PAVGraphicMenuItem@@V?$DynamicVectorClass@PAVGraphicMenuItem@@@@@@UBE_NXZ=004def90
// @ref ?Next@?$VectorCursor@PAVGraphicMenuItem@@V?$DynamicVectorClass@PAVGraphicMenuItem@@@@@@UAEAAV1@XZ=004df220
// @ref ?Prev@?$VectorCursor@PAVGraphicMenuItem@@V?$DynamicVectorClass@PAVGraphicMenuItem@@@@@@UAEAAV1@XZ=004df230
typedef VectorCursor<GraphicMenuItem *, DynamicVectorClass<GraphicMenuItem *> > GraphicMenuCursor;

GraphicMenuItem *GraphicMenu::Item_At(Point2D const &point)
{
    GraphicMenuCursor cursor(Items);
    GraphicMenuCursor *at = &cursor;
    while (at->Valid() && !at->Current()->Contains(point)) {
        at->Next();
    }
    return at->Valid() ? at->Current() : 0;
}
