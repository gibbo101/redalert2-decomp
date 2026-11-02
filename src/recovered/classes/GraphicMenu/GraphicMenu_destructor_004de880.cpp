// GraphicMenu::~GraphicMenu() (0x004DE880): deletes the items, clears the background and back buffers and
// copies the cleared buffer to the screen.
#include "shared/graphic_menu_class.hpp"
#include "shared/vector_cursor.hpp"
// @ref ??_7?$VectorCursor@PAVGraphicMenuItem@@V?$DynamicVectorClass@PAVGraphicMenuItem@@@@@@6B@=007a2b84
// @ref ??_E?$VectorCursor@PAVGraphicMenuItem@@V?$DynamicVectorClass@PAVGraphicMenuItem@@@@@@UAEPAXI@Z=004defa0
// @ref ??_G?$VectorCursor@PAVGraphicMenuItem@@V?$DynamicVectorClass@PAVGraphicMenuItem@@@@@@UAEPAXI@Z=004defa0
// @ref ?Valid@?$VectorCursor@PAVGraphicMenuItem@@V?$DynamicVectorClass@PAVGraphicMenuItem@@@@@@UBE_NXZ=004def90
// @ref ?Next@?$VectorCursor@PAVGraphicMenuItem@@V?$DynamicVectorClass@PAVGraphicMenuItem@@@@@@UAEAAV1@XZ=004df220
// @ref ?Prev@?$VectorCursor@PAVGraphicMenuItem@@V?$DynamicVectorClass@PAVGraphicMenuItem@@@@@@UAEAAV1@XZ=004df230
#include "shared/dsurface.hpp"
#include "shared/unknown_globals.hpp"
// @ref ??1MSEngine@@UAE@XZ=005b2c70
// @ref ??1Wstring@@QAE@XZ=0076d9e0
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??_7GraphicMenu@@6B@=007a2b3c
// @ref ??_GGraphicMenu@@UAEPAXI@Z=004def10
// @ref ??_7?$VectorClass@PAVGraphicMenuItem@@@@6B@=007a2b64
// @ref ?unknown_surface_839950@@3PAVSurface@@A=00839950
// @ref ?unknown_surface_839954@@3PAVSurface@@A=00839954
// @ref ?unknown_surface_839958@@3PAVSurface@@A=00839958
typedef VectorCursor<GraphicMenuItem *, DynamicVectorClass<GraphicMenuItem *> > GraphicMenuCursor;

GraphicMenu::~GraphicMenu()
{
    GraphicMenuCursor cursor(Items);
    GraphicMenuCursor *at = &cursor;
    while (at->Valid()) {
        delete at->Current();
        at->Next();
    }
    unknown_surface_839958->Fill(0);
    unknown_surface_839954->Fill(0);
    unknown_surface_839950->Copy_From(*unknown_surface_839954, false, true);
}
