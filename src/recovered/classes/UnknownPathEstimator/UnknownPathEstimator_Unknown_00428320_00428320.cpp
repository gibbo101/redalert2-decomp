// UnknownPathEstimator::Unknown_00428320() (0x00428320): the facing between
// two adjacent cells.
#include "shared/path_estimator.hpp"
#include "shared/crt_memory.hpp"

int __fastcall UnknownPathEstimator::Unknown_00428320(Cell const &from, Cell const &to)
{
    int dy = to.Y - from.Y;
    if (abs(dy) <= 1 && abs(to.X - from.X) <= 1) {
        return unknown_path_facing_table_7cf100[dy + 1][to.X - from.X + 1];
    }
    return 8;
}
