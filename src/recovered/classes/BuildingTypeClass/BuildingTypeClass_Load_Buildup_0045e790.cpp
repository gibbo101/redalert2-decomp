// Demand-loaded building buildup image and its animation frame rate.
#include "shared/building_type.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/rules.hpp"
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#include "shared/shape_file.hpp"
// @ref ??_C@_04BOIE@?4SHP?$AA@=007ced14
// @ref __makepath=007831f0
// @ref __ftol=0077f110
// @ref ?Load_Alloc_Data@@YIPAXAAVFileClass@@@Z=00495230
void *__fastcall Load_Alloc_Data(FileClass &file);
extern "C" void __cdecl _makepath(char *, char const *, char const *, char const *, char const *);
void *BuildingTypeClass::unknown_slot48()
{
    if(BuildupData==0 && DemandLoadBuildup) {
        if(strlen(BuildupFile)!=0) {
            char fullname[260];
            _makepath(fullname,0,0,BuildupFile,".SHP");
            Theater_Naming_Convention(fullname,unknown_id_source_a3d290->Theater);
            CCFileClass file(fullname);
            void *shape=Load_Alloc_Data(file);
            if(shape==0) {
                Generic_Naming_Convention(fullname);
                CCFileClass generic(fullname);
                shape=Load_Alloc_Data(generic);
            }
            BuildupData=shape;
            if(shape!=0) {
                int rate=1;
                BuildupDataAllocated=true;
                int frames=((ShapeFileStruct *)shape)->FrameCount/2;
                if(Gate) frames=(int)((unsigned int)GateStages+1u);
                if(frames>0) rate=(int)(Rules->unknown_1178*900.0/frames);
                AnimFrames[0].unknown_00=0;
                AnimFrames[0].unknown_04=frames;
                AnimFrames[0].unknown_08=rate;
            }
        }
        return BuildupData;
    }
    return BuildupData;
}
