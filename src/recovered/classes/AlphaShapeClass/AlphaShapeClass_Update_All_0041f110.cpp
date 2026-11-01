// void AlphaShapeClass::Update_All() (0x0041F110)
// Builds the alpha table once and deletes the shapes whose owner went away.
#include "shared/alpha_shape.hpp"
// @ref ?unknown_AlphaShapeClass_list_0083c648@@3V?$DynamicVectorClass@PAVAlphaShapeClass@@@@A=0083c648
// @ref ?unknown_alpha_table_83c670@@3PAEA=0083c670
// @ref ?unknown_alpha_table_ready_84c684@@3_NA=0084c684

void AlphaShapeClass::Update_All()
{
    if (!unknown_alpha_table_ready_84c684) {
        Init_Alpha_Table();
    }
    for (int i = unknown_AlphaShapeClass_list_0083c648.Count() - 1; i >= 0; i--) {
        if (unknown_AlphaShapeClass_list_0083c648[i]->unknown_3c) {
            delete unknown_AlphaShapeClass_list_0083c648[i];
        }
    }
}
