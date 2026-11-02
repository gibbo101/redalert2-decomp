// @ref ??0Matrix3D@@QAE@ABV0@@Z=0058fe10
// @ref ??AMapClass@@QAEAAVCellClass@@ABUCoordStruct@@@Z=00548000
// @ref ??D@YI?AVMatrix3D@@ABV0@0@Z=00591180
// @ref ?Current@FacingClass@@QBE?AUUnknownFacingDir@@XZ=004b8be0
// @ref ?Draw_Matrix@LocomotionClass@@UAGPAVMatrix3D@@PAV2@PAH@Z=0053d030
// @ref ?Fast_Cos@@YAMN@Z=004ba4d0
// @ref ?Fast_Sin@@YAMN@Z=004ba480
// @ref ?Make_Identity@Matrix3D@@QAEXXZ=00590060
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Rotate_X@Matrix3D@@QAEXM@Z=00590760
// @ref ?Rotate_Y@Matrix3D@@QAEXM@Z=00590880
// @ref ?Rotate_Z@Matrix3D@@QAEXM@Z=005909a0
// @ref ?Translate_X@Matrix3D@@QAEXM@Z=00590180
// @ref ?Translate_Y@Matrix3D@@QAEXM@Z=005901b0
// @ref ?Translate_Z@Matrix3D@@QAEXM@Z=005901e0
// @ref ?Unknown_00718D60@@YIPAVMatrix3D@@PAV1@H@Z=00718d60
// @ref ?unknown_hover_facing_step_79d090@@3NB=0079d090
// @ref ?unknown_hover_tilt_min_79d170@@3NB=0079d170
// @ref ?unknown_hover_zero_79a738@@3MB=0079a738
// @ref __ftol=0077f110
#include "shared/hover_locomotion.hpp"
#include "shared/cell.hpp"
#include "shared/techno_type.hpp"
#include "shared/crt_math.hpp"
extern double const unknown_hover_tilt_min_79d170;
extern double const unknown_hover_facing_step_79d090;
extern float const unknown_hover_zero_79a738;
Matrix3D *__stdcall HoverLocomotionClass::Draw_Matrix(Matrix3D *matrix,int *key)
{
    if (fabs(LinkedTo->unknown_280)>=unknown_hover_tilt_min_79d170 ||
        fabs(LinkedTo->unknown_284)>=unknown_hover_tilt_min_79d170) {
        if (key) *key=-1;
        Matrix3D translation;
        translation.Make_Identity();
        Matrix3D rotation;
        rotation.Make_Identity();
        float width=(float)LinkedTo->unknown_slot32()->unknown_330;
        float length=(float)LinkedTo->unknown_slot32()->unknown_338;
        float cos_pitch=Fast_Cos(LinkedTo->unknown_284);
        float sin_pitch=Fast_Sin(LinkedTo->unknown_284);
        float cos_roll=Fast_Cos(LinkedTo->unknown_280);
        float sin_roll=Fast_Sin(LinkedTo->unknown_280);
        int height=(int)(fabs(sin_roll)*width+fabs(sin_pitch)*length);
        int shift_x=(int)(length-(int)(cos_pitch*length));
        int shift_y=(int)(width-(int)(cos_roll*width));
        if (LinkedTo->unknown_284<unknown_hover_zero_79a738) shift_x=-shift_x;
        if (LinkedTo->unknown_280>unknown_hover_zero_79a738) shift_y=-shift_y;
        translation.Translate_Z((float)height);
        rotation.Translate_X((float)shift_x);
        rotation.Translate_Y((float)shift_y);
        rotation.Rotate_X(LinkedTo->unknown_280);
        rotation.Rotate_Y(LinkedTo->unknown_284);
        Matrix3D base;
        Matrix3D base_value(*LocomotionClass::Draw_Matrix(&base,key));
        *matrix=translation*base_value*rotation;
    } else {
        if (!Is_Powered()) {
            int ramp=Map[Object_Coord(LinkedTo)].unknown_11c;
            Matrix3D slope;
            Matrix3D result;
            result=*Unknown_00718D60(&slope,ramp);
            result.Rotate_Z((float)((Dir_To_32(LinkedTo->unknown_2e0.Current())-8)*unknown_hover_facing_step_79d090));
            if (key && *key!=-1) {
                *key=32*(ramp+(*key<<6));
                *key|=Dir_To_32(LinkedTo->unknown_2e0.Current());
            }
            *matrix=result;
        } else {
            Matrix3D base;
            *matrix=*LocomotionClass::Draw_Matrix(&base,key);
        }
    }
    return matrix;
}
