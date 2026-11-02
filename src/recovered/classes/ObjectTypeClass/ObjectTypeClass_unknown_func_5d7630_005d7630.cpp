// void ObjectTypeClass::unknown_func_5d7630() (0x005D7630)
// (Re)loads the image for the current theater: arctic-art types switch to
// their "A" image once in the snow theater (theater 1); the file name gets
// the theater suffix (Theater=) or theater letter (NewTheater=); any owned
// image is freed and the mixfile copy taken; unknown_1bc becomes the larger
// shape dimension, at least 8.
#include "shared/object_type.hpp"
#include "shared/anim_type.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"
// ObjectType.cpp has no empty-rectangle static of its own (no dynamic
// initializer for it in the unit).
#define SHAPE_FILE_EMPTY_RECT Rect(0, 0, 0, 0)
#include "shared/shape_file.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?Theaters@@3PAUTheaterTypeStruct@@A=0079ab68
// @ref _sprintf=007820f4
// @ref _strncpy=007823d0
// @ref __makepath=007831f0
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?Retrieve@MixFileClass@@SIPBXPBD@Z=005956c0
// @ref ??_C@_03HJGP@?$CFsA?$AA@=007e8110
// @ref ??_C@_04BOIE@?4SHP?$AA@=007ced14

extern "C" void __cdecl _makepath(char *path, char const *drive, char const *dir, char const *fname, char const *ext);

void ObjectTypeClass::unknown_func_5d7630()
{
    char fullname[260];
    if (unknown_1e1 && unknown_id_source_a3d290->Theater == 1 && !unknown_a8) {
        if (!unknown_1e2) {
            char buffer[256];
            sprintf(buffer, "%sA", (char const *)unknown_1c8);
            unknown_1c8 = buffer;
            unknown_1e2 = true;
        }
    } else {
        unknown_1e2 = false;
    }

    _makepath(fullname, 0, 0, unknown_1c8, ".SHP");
    if (unknown_1fc) {
        _makepath(fullname, 0, 0, unknown_1c8, Theaters[unknown_id_source_a3d290->Theater].Suffix);
    } else if (unknown_207) {
        Theater_Naming_Convention(fullname, unknown_id_source_a3d290->Theater);
    }

    if (unknown_a8 && unknown_a4 != 0) {
        operator delete(unknown_a4);
    }
    unknown_a4 = 0;
    unknown_a8 = false;
    unknown_a4 = (void *)MixFileClass::Retrieve(fullname);
    if (unknown_a4 != 0) {
        ShapeFileStruct const *shape = (ShapeFileStruct const *)unknown_a4;
        int size;
        if (shape->Width > shape->Height) {
            size = shape->Width;
        } else {
            size = shape->Height;
        }
        unknown_1bc = size > 8 ? size : 8;
    }
}
