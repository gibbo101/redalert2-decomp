#include "shared/dial8.hpp"
#include "shared/mouse.hpp"
// @ref ?unknown_scheme_index_4cefc0@@YAHXZ=004cefc0
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?unknown_surface_83995c@@3PAVSurface@@A=0083995c
// @ref ?unknown_drawer_8323c4@@3PAVConvertClass@@A=008323c4
// @ref ?ColorSchemes@@3V?$DynamicVectorClass@PAVColorScheme@@@@A=00ab6ef8
// @ref ?Draw_Box@@YIXABVRect@@H_N@Z=004973d0
int Dial8Class::Draw_Me(int forced)
{
    int scheme = unknown_scheme_index_4cefc0();
    if (ControlClass::Draw_Me(forced)) {
        WWMouse->Hide_Mouse();
        Draw_Box(Rect(X, Y, Width, Height), 0, true);
        for (int i = 0; i < 8; ++i) {
            Draw_Box(Rect(OuterPoints[i].X - 1, OuterPoints[i].Y - 1, 3, 3), 1, false);
        }
        int color = unknown_drawer_8323c4->Convert(ColorSchemes[scheme]->unknown_color_0x31c);
        unknown_surface_83995c->Draw_Line(Point2D(Center.X + 1, Center.Y + 1), Point2D(InnerPoints[Selected].X + 1, InnerPoints[Selected].Y + 1), color);
        color = unknown_drawer_8323c4->Convert(ColorSchemes[scheme]->unknown_color_0x328);
        unknown_surface_83995c->Draw_Line(Point2D(Center.X, Center.Y), Point2D(InnerPoints[Selected].X, InnerPoints[Selected].Y), color);
        WWMouse->Show_Mouse();
        return 1;
    }
    return 0;
}
