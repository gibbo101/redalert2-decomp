// MonoPoint::MonoPoint(int column, int row) (0x0059E160)
// The pixel position of a character cell: the cell size from the font
// metrics, with a margin of ten pixels.
#include "shared/mono_class.hpp"
// @ref ?unknown_mono_width_a70eb8@@3HA=00a70eb8
// @ref ?unknown_mono_height_a70ea0@@3HA=00a70ea0
// @ref ?unknown_mono_leading_a70eb0@@3HA=00a70eb0

MonoPoint::MonoPoint(int column, int row)
{
    Point2D p(unknown_mono_width_a70eb8 * column + 10,
              (unknown_mono_height_a70ea0 + unknown_mono_leading_a70eb0) * row + 10);
    X = p.X;
    Y = p.Y;
}
