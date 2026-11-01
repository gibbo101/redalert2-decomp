// AlphaShapeClass::AlphaShapeClass(ObjectClass *object, int x, int y) (0x0041EBE0)
// The owner type's alpha image placed at x, y; joins both lists.
#include "shared/alpha_shape.hpp"
#include "shared/object.hpp"
#include "shared/object_type.hpp"
#include "shared/object_lists.hpp"
#include "shared/shape_file.hpp"
// @ref ??0AbstractClass@@QAE@XZ=0040ff10
// @ref ??_7AlphaShapeClass@@6BIPersistStream@@@=0079bfd4
// @ref ??_7AlphaShapeClass@@6BIRTTITypeInfo@@@=0079bfb8
// @ref ??_7AlphaShapeClass@@6BINoticeSink@@@=0079bfb0
// @ref ??_7AlphaShapeClass@@6BINoticeSource@@@=0079bfa8
// @ref ?unknown_AlphaShapeClass_list_0083c648@@3V?$DynamicVectorClass@PAVAlphaShapeClass@@@@A=0083c648
// @ref ?unknown_AbstractClass_list_00ac0d60@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0d60
// @ref ?unknown_alpha_table_83c670@@3PAEA=0083c670
// @ref ?unknown_alpha_table_ready_84c684@@3_NA=0084c684

AlphaShapeClass::AlphaShapeClass(ObjectClass *object, int x, int y) :
    Owner(object),
    Image(0),
    unknown_3c(false)
{
    ShapeFileStruct *image = (ShapeFileStruct *)object->Class_Of()->unknown_ac;
    Image = image;
    Bounds = Rect(x, y, image->Get_Width(), image->Get_Height());
    unknown_AlphaShapeClass_list_0083c648.Add(this);
    unknown_AbstractClass_list_00ac0d60.Add(this);
    if (!unknown_alpha_table_ready_84c684) {
        Init_Alpha_Table();
    }
}
