// Gathers the objects of the bins within radius cells of the cell's bin into Working: the
// cell's own bin, the bins walked back to it from the four points radius cells away, the
// diagonal bins up to the shorter of each pair of arm lengths and, when both arms are longer
// than one bin, the two bins beside the first diagonal.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#include "shared/vector_class.hpp"
#include "shared/foot.hpp"
#include "shared/map_view.hpp"
#include "shared/rect.hpp"
#include "shared/cell_class.hpp"
#define Tracker_Min(a,b) (((a)<(b)) ? (a) : (b))
// The out-of-line Append_Bin (0x00412720) and As_Cell (0x00413770) copies are accepted in the
// neighbouring populations; this unit's Append_Bin definition is the one Unknown_004128A0 inlines.
// @ref ?Append_Bin_00412720@UnknownTracker839EA0@@QAEXH@Z=00412720
// @ref ?As_Cell@CoordStruct@@QBE?AVCell@@XZ=00413770
void UnknownTracker839EA0::Append_Bin_00412720(int index)
{
    int count=Bins[index].Count();
    for (int i=0;i<count;++i) Working.Add(Bins[index].Fetch(i));
}

inline Cell Object_Cell(CellClass *cell) { return cell->Center_Coord().As_Cell(); }

void UnknownTracker839EA0::Unknown_004128A0(CellClass *cell, int radius)
{
    Cell center = Object_Cell(cell);
    int index = Region_Index_00412820(center);
    Append_Bin_00412720(index);

    int up = 0;
    int down = 0;
    int right = 0;
    int left = 0;

    Cell edge = center;
    edge.X += radius;
    int bin = Region_Index_00412820(edge);
    while (bin != index) {
        right++;
        Append_Bin_00412720(bin);
        bin = Shift_Bin_004127a0(bin, Point2D(-1, 0));
    }

    edge = center;
    edge.Y -= radius;
    bin = Region_Index_00412820(edge);
    while (bin != index) {
        up++;
        Append_Bin_00412720(bin);
        bin = Shift_Bin_004127a0(bin, Point2D(0, 1));
    }

    edge = center;
    edge.Y += radius;
    bin = Region_Index_00412820(edge);
    while (bin != index) {
        down++;
        Append_Bin_00412720(bin);
        bin = Shift_Bin_004127a0(bin, Point2D(0, -1));
    }

    edge = center;
    edge.X -= radius;
    bin = Region_Index_00412820(edge);
    while (bin != index) {
        left++;
        Append_Bin_00412720(bin);
        bin = Shift_Bin_004127a0(bin, Point2D(1, 0));
    }

    if (up && left) {
        for (int i = Tracker_Min(up, left), bin = index; i > 0; i--) {
            bin = Shift_Bin_004127a0(bin, Point2D(-1, -1));
            Append_Bin_00412720(bin);
        }
        if (up >= 2 && left >= 2) {
            Append_Bin_00412720(Shift_Bin_004127a0(index, Point2D(-2, -1)));
            Append_Bin_00412720(Shift_Bin_004127a0(index, Point2D(-1, -2)));
        }
    }

    if (down && left) {
        for (int i = Tracker_Min(down, left), bin = index; i > 0; i--) {
            bin = Shift_Bin_004127a0(bin, Point2D(-1, 1));
            Append_Bin_00412720(bin);
        }
        if (down >= 2 && left >= 2) {
            int side;
            side = Shift_Bin_004127a0(index, Point2D(-2, 1));
            Append_Bin_00412720(side);
            side = Shift_Bin_004127a0(index, Point2D(-1, 2));
            Append_Bin_00412720(side);
        }
    }

    if (up && right) {
        for (int i = Tracker_Min(up, right), bin = index; i > 0; i--) {
            bin = Shift_Bin_004127a0(bin, Point2D(1, -1));
            Append_Bin_00412720(bin);
        }
        if (up >= 2 && right >= 2) {
            int side;
            side = Shift_Bin_004127a0(index, Point2D(2, -1));
            Append_Bin_00412720(side);
            side = Shift_Bin_004127a0(index, Point2D(1, -2));
            Append_Bin_00412720(side);
        }
    }

    if (down && right) {
        for (int i = Tracker_Min(down, right), bin = index; i > 0; i--) {
            bin = Shift_Bin_004127a0(bin, Point2D(1, 1));
            Append_Bin_00412720(bin);
        }
        if (down >= 2 && right >= 2) {
            int side;
            side = Shift_Bin_004127a0(index, Point2D(2, 1));
            Append_Bin_00412720(side);
            side = Shift_Bin_004127a0(index, Point2D(1, 2));
            Append_Bin_00412720(side);
        }
    }
}
