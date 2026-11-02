#include "shared/mix_file_class.hpp"
#include "shared/cc_file_class.hpp"
// Load the shared building depth shape and remap its nonzero pixels.
#include "shared/building_type.hpp"
#include "shared/cc_file_class.hpp"
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#include "shared/shape_file.hpp"
// @ref ?unknown_building_depth_shape_85029c@@3PAUShapeFileStruct@@A=0085029c
// @ref ?Retrieve@MixFileClass@@SIPBXPBD@Z=005956c0
extern "C" char const unknown_building_depth_filename_007cfdb0[];
// @ref _unknown_building_depth_filename_007cfdb0=007cfdb0
extern ShapeFileStruct *unknown_building_depth_shape_85029c;
void BuildingTypeClass::unknown_func_458510()
{
    if(unknown_building_depth_shape_85029c!=0) {
        operator delete(unknown_building_depth_shape_85029c);
        unknown_building_depth_shape_85029c=0;
    }
    int size=CCFileClass(unknown_building_depth_filename_007cfdb0).Size();
    unknown_building_depth_shape_85029c=(ShapeFileStruct *)operator new(size);
    memcpy(unknown_building_depth_shape_85029c,MixFileClass::Retrieve(unknown_building_depth_filename_007cfdb0),size);
    unsigned char *pixels=(unsigned char *)unknown_building_depth_shape_85029c->Get_Frame_Data(0);
    int width=unknown_building_depth_shape_85029c->Get_Width();
    int height=unknown_building_depth_shape_85029c->Get_Height();
    // The file size is dead after the copy; its scratch local is reused for columns.
    for(int row=height;row>0;--row) {
        for(size=0;size<width;++size) {
            if(pixels[size]!=0) pixels[size]-=65;
        }
        pixels+=width;
    }
}
