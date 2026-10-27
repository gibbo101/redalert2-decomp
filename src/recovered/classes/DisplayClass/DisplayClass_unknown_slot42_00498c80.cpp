// void DisplayClass::unknown_slot42(Rect const &rect) (0x00498C80, slot 42: Set_View_Dimensions)
// Takes the new tactical view rectangle: keeps it (0x00839630), passes it
// to the tactical view and, with the mouse hidden, rebuilds the alpha and
// depth buffers for it; then the sidebar places its controls (slot 34),
// the view's tooltip (id 500) is replaced and the message list is moved to
// the view's top edge.
#include "shared/display.hpp"
#include "shared/tactical.hpp"
#include "shared/mouse.hpp"
#include "shared/blit.hpp"
#include "shared/tool_tip.hpp"
#include "shared/map_view.hpp"
// @ref ??_C@_0BC@MLFK@Deleting?5ABuffer?6?$AA@=007d5d74
// @ref ??_C@_0BC@NALE@Deleting?5ZBuffer?6?$AA@=007d5da4
// @ref ??_C@_0BL@EKMA@Set_View_Dimensions?$CIexit?$CJ?6?$AA@=007d5d3c
// @ref ??_C@_0BM@KIKC@Allocating?5ABuffer?5?$CI?$CFdx?$CFd?$CJ?6?$AA@=007d5d58
// @ref ??_C@_0BM@NINK@Allocating?5ZBuffer?5?$CI?$CFdx?$CFd?$CJ?6?$AA@=007d5d88
// @ref ??_C@_0CC@JMFC@Set_View_Dimensions?$CI?$CFd?0?$CFd?0?$CFd?0?$CFd?$CJ@=007d5db8
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?unknown_rect_85291c@@3VRect@@A=0085291c
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?Unknown_006A65A0@Tactical@@QAEXABVRect@@@Z=006a65a0
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?ABufferPtr@@3PAVABuffer@@A=00839c6c
// @ref ?ZBufferPtr@@3PAVZBuffer@@A=008315b4
// @ref ??0ABuffer@@QAE@VRect@@@Z=00775b80
// @ref ??1ABuffer@@QAE@XZ=00775cf0
// @ref ??0ZBuffer@@QAE@VRect@@@Z=00410a60
// @ref ??1ZBuffer@@QAE@XZ=00410bd0
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_slot34@SidebarClass@@UAEXXZ=006819a0
// @ref ?ToolTips@@3PAVCCToolTip@@A=008399b0
// @ref ?Remove@ToolTipManager@@QAEXI@Z=006eba10
// @ref ?Add@ToolTipManager@@QAE_NABVToolTip@@@Z=006eb860
// @ref ?unknown_object_a3dc70@@3VUnknownObjectA3DC70@@A=00a3dc70
// @ref ?Unknown_005B4C60@UnknownObjectA3DC70@@QAEXHHHHHHHHHHH@Z=005b4c60
// @ref ?Unknown_005B5C60@UnknownObjectA3DC70@@QAEXH@Z=005b5c60

void DisplayClass::unknown_slot42(Rect const &rect)
{
    Debug_Printf("Set_View_Dimensions(%d,%d,%d,%d)\n", rect.X, rect.Y, rect.Width, rect.Height);
    unknown_rect_839630 = rect;
    if (unknown_tactical_83996c != 0) {
        unknown_tactical_83996c->Unknown_006A65A0(unknown_rect_839630);
        WWMouse->Hide_Mouse();
        if (ABufferPtr != 0) {
            Debug_Printf("Deleting ZBuffer\n");
            delete ABufferPtr;
            ABufferPtr = 0;
        }
        ABufferPtr = new ABuffer(unknown_rect_839630);
        ABufferPtr->MaxValue = 0x8000;
        Debug_Printf("Allocating ZBuffer (%dx%d)\n", unknown_rect_839630.Width, unknown_rect_839630.Height);
        if (ZBufferPtr != 0) {
            Debug_Printf("Deleting ABuffer\n");
            delete ZBufferPtr;
            ZBufferPtr = 0;
        }
        ZBufferPtr = new ZBuffer(unknown_rect_839630);
        Debug_Printf("Allocating ABuffer (%dx%d)\n", unknown_rect_839630.Width, unknown_rect_839630.Height);
        WWMouse->Show_Mouse();
    }
    Map.unknown_slot34();
    unknown_rect_85291c.X = unknown_rect_839630.X;
    unknown_rect_85291c.Y = unknown_rect_839630.Y;
    unknown_rect_85291c.Width = unknown_rect_839630.Width;
    unknown_rect_85291c.Height = unknown_rect_839630.Height;
    if (ToolTips != 0) {
        ToolTip tip;
        tip.unknown_18 = false;
        tip.ID = 500;
        tip.Label = 0;
        tip.Region = unknown_rect_839630;
        ToolTips->Remove(500);
        ToolTips->Add(tip);
    }
    unknown_object_a3dc70.Unknown_005B4C60(unknown_rect_839630.X + 3, unknown_rect_839630.Y, 6, 0x62, 0xE, -1, -1, 0, 0x14, 0x62,
                                          unknown_rect_839630.Width - 6);
    unknown_object_a3dc70.Unknown_005B5C60(unknown_rect_839630.Width);
    Debug_Printf("Set_View_Dimensions(exit)\n");
}
