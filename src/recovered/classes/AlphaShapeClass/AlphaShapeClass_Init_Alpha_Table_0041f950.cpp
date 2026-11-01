// void AlphaShapeClass::Init_Alpha_Table() (0x0041F950)
// Each entry is the product of its two index bytes over 127, clamped to a byte.
#include "shared/alpha_shape.hpp"
// @ref ?unknown_alpha_table_83c670@@3PAEA=0083c670
// @ref ?unknown_alpha_table_ready_84c684@@3_NA=0084c684

#define ALPHA_MIN(a, b) ((a) < (b) ? (a) : (b))
#define ALPHA_MAX(a, b) ((a) > (b) ? (a) : (b))

void AlphaShapeClass::Init_Alpha_Table()
{
    unknown_alpha_table_ready_84c684 = true;
    for (int i = 0; i < 256 * 256; i++) {
        int low = i % 256;
        int high = i / 256;
        int value = ALPHA_MAX(0, ALPHA_MIN(255, low * high / 127));
        unknown_alpha_table_83c670[i] = value;
    }
}
