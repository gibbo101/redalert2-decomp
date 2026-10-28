// bool Clip_Line(Point2D &start, Point2D &end, Rect const &rect) (0x00775620)
// Cohen-Sutherland clipping of the line start-end to rect, in doubles: while
// an endpoint lies outside (Clip_Line_Outcode, expanded inline), move it to
// the edge it crosses (the last row or column inside for the excluded right
// and bottom edges). False when both endpoints lie beyond one edge; true with
// the endpoints rewritten otherwise.
#include "shared/rect.hpp"

bool __fastcall Clip_Line(Point2D &start, Point2D &end, Rect const &rect)
{
    double x = rect.X;
    double y = rect.Y;
    double x0 = start.X;
    double y0 = start.Y;
    double x1 = end.X;
    double y1 = end.Y;
    double inverse_slope = (x1 - x0) / (y1 - y0);
    double slope = (y1 - y0) / (x1 - x0);
    int code0 = Clip_Line_Outcode(rect, x0, y0);
    int code1 = Clip_Line_Outcode(rect, x1, y1);
    for (;;) {
        if (code0 == 0 && code1 == 0) {
            start.X = (int)x0;
            start.Y = (int)y0;
            end.X = (int)x1;
            end.Y = (int)y1;
            return true;
        }
        if (code0 & code1) {
            return false;
        }
        int code = code0 ? code0 : code1;
        if (code & 8) {
            x = x0 + (rect.Y - y0) * inverse_slope;
            y = rect.Y;
        } else if (code & 4) {
            x = x0 + (rect.Y + rect.Height - 1 - y0) * inverse_slope;
            y = rect.Y + rect.Height - 1;
        } else if (code & 2) {
            y = y0 + (rect.X + rect.Width - 1 - x0) * slope;
            x = rect.X + rect.Width - 1;
        } else if (code & 1) {
            y = y0 + (rect.X - x0) * slope;
            x = rect.X;
        }
        if (code == code0) {
            x0 = x;
            y0 = y;
            code0 = Clip_Line_Outcode(rect, x0, y0);
        } else {
            x1 = x;
            y1 = y;
            code1 = Clip_Line_Outcode(rect, x1, y1);
        }
    }
}
