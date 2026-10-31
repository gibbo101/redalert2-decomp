// @ref ?unknown_registry_a73640@OwnerDraw@@3VUnknownControlIndex@1@A=00a73640
// @ref ?unknown_art_ac1074@@3PAXA=00ac1074
// @ref ?unknown_shape_ac1104@@3PAUShapeFileStruct@@A=00ac1104
// @ref ?unknown_shape_ac110c@@3PAUShapeFileStruct@@A=00ac110c
// @ref ?unknown_shape_ac1128@@3PAUShapeFileStruct@@A=00ac1128
// @ref ?unknown_shape_ac1010@@3PAUShapeFileStruct@@A=00ac1010
#include "shared/owner_draw_dialog_control.hpp"

struct ShapeFileStruct;
extern void *unknown_art_ac1074;
extern ShapeFileStruct *unknown_shape_ac1104;
extern ShapeFileStruct *unknown_shape_ac110c;
extern ShapeFileStruct *unknown_shape_ac1128;
extern ShapeFileStruct *unknown_shape_ac1010;
void *Unknown_Get_Art_6f2b40();

namespace OwnerDraw {

// Sets the art of the control registered under key by its kind (unknown_6c): the background image
// (unknown_74) and the two shapes unknown_e0 / unknown_e4.
void __fastcall unknown_set_control_art_5ea960(unsigned int key)
{
    UnknownControlRecord *record = unknown_registry_a73640.Find(key);
    if (record != 0) {
        int kind = record->unknown_6c;
        if (kind == 0x94) {
            record->unknown_74 = (int)Unknown_Get_Art_6f2de0();
            record->unknown_e0 = (int)unknown_art_ac1074;
            record->unknown_e4 = (int)unknown_art_ac1074;
        } else if (kind == 0x103) {
            record->unknown_74 = (int)Unknown_Get_Art_6f2830();
            record->unknown_e0 = (int)unknown_shape_ac110c;
            record->unknown_e4 = (int)unknown_shape_ac110c;
        } else if (kind == 0x108) {
            record->unknown_74 = (int)Unknown_Get_Art_6f2b40();
            record->unknown_e0 = (int)unknown_shape_ac1104;
            record->unknown_e4 = (int)unknown_shape_ac1104;
        } else if (kind == 0xBC6) {
            record->unknown_74 = (int)Unknown_Get_Art_6f2830();
            record->unknown_e0 = (int)unknown_shape_ac110c;
            record->unknown_e4 = (int)unknown_shape_ac110c;
        } else if (kind == 0xBC7) {
            record->unknown_74 = (int)Unknown_Get_Art_6f2830();
            record->unknown_e0 = (int)unknown_shape_ac110c;
            record->unknown_e4 = (int)unknown_shape_ac110c;
        } else {
            record->unknown_74 = (int)Unknown_Get_Art_006f3480();
            record->unknown_e0 = (int)unknown_shape_ac1128;
            record->unknown_e4 = (int)unknown_shape_ac1010;
        }
    }
}

}
