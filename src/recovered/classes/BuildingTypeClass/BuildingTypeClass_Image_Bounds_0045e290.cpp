#include "shared/building_type.hpp"
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#include "shared/shape_file.hpp"

template<>
inline Rect __fastcall Union<Rect>(Rect const &rect1,Rect const &rect2)
{
    if (rect1.Is_Valid()) {
        if (rect2.Is_Valid()) {
            Rect result = rect1;
            if (result.X > rect2.X) {
                result.Width += result.X - rect2.X;
                result.X = rect2.X;
            }
            if (result.Y > rect2.Y) {
                result.Height += result.Y - rect2.Y;
                result.Y = rect2.Y;
            }
            int rect2_right=rect2.X+rect2.Width;
            int result_right=result.X+result.Width;
            if(result_right<rect2_right) {
                result.Width = ((rect2.X + rect2.Width) - result.X) + 1;
            }
            if (result.Y + result.Height < rect2.Y + rect2.Height) {
                result.Height = ((rect2.Y + rect2.Height) - result.Y) + 1;
            }
            return result;
        }
        return rect1;
    }
    return rect2;
}

Rect BuildingTypeClass::unknown_func_45e290()
{
    int frame;
    if(unknown_11ec!=unknown_static_rect)return unknown_11ec;
    ShapeFileStruct const *image=(ShapeFileStruct const *)unknown_slot39();
    if(image==0)return unknown_static_rect;
    int frames=image->Get_Count();
    Rect bounds=unknown_static_rect;
    int width=image->Get_Width();
    int height=image->Get_Height();
    for(frame=0;frame<frames;frame++) {
        bounds=Union(bounds,image->Get_Frame_Rect(frame));
    }
    bool free_buildup=BuildupData==0;
    image=(ShapeFileStruct const *)unknown_slot48();
    if(image) {
        frames=image->Get_Count();
        for(frame=0;frame<frames;frame++) {
            bounds=Union(bounds,image->Get_Frame_Rect(frame));
        }
        if(free_buildup)Free_Buildup();
    }
    if(unknown_11cc) {
        Rect bib=((ShapeFileStruct const *)unknown_11cc)->Get_Frame_Rect(0);
        bounds=Union(bounds,bib);
    }
    int x=bounds.X-width/2;
    int y=bounds.Y-height/2;
    int bounds_width=bounds.Width;
    int bounds_height=bounds.Height;
    unknown_11ec=Rect(x,y,bounds_width,bounds_height);
    return unknown_11ec;
}
