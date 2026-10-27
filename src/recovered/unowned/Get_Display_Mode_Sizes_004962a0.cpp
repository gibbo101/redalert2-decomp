#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/directdraw.hpp"
#include "shared/video_mode_size.hpp"
#include "shared/crt_memory.hpp"
extern IDirectDraw *DirectDrawObject;
HRESULT __stdcall Collect_Display_Mode_004961f0(DDSURFACEDESC *description,void *context);
int __cdecl Compare_Video_Mode_Size_00496260(void const *left,void const *right);
extern "C" void __cdecl qsort(void *base,unsigned int count,unsigned int size,int (__cdecl *compare)(void const *,void const *));
// The real derived constructor body, with the base constructor external in this unit.
template <class T>
DynamicVectorClass<T>::DynamicVectorClass(unsigned size,T const *array)
    : VectorClass<T>(size,array)
{
    GrowthStep=10;
    ActiveCount=0;
}
// @ref ?DirectDrawObject@@=008523cc
// @ref ?Collect_Display_Mode_004961f0@@=004961f0
// @ref ?Compare_Video_Mode_Size_00496260@@=00496260
// @ref ??0?$VectorClass@PAUDDSURFACEDESC@@@@=004967d0
// @ref ??_7?$DynamicVectorClass@PAUDDSURFACEDESC@@@@6B@=0079e764
// @ref ??_7?$VectorClass@PAUDDSURFACEDESC@@@@6B@=0079e744
// @ref _qsort=00781d46
VideoModeSize *__fastcall Get_Display_Mode_Sizes_004962a0(DWORD minimumWidth,DWORD minimumHeight,
    DWORD maximumWidth,DWORD maximumHeight,DWORD bitDepth)
{
    if (!DirectDrawObject) return 0;
    DynamicVectorClass<DDSURFACEDESC *> descriptions;
    if (DirectDrawObject->EnumDisplayModes(0,0,&descriptions,Collect_Display_Mode_004961f0)==0 && descriptions.Count()!=0) {
        int *result=new int[descriptions.Count()*2+1];
        int *next=result;
        memset(result,0,descriptions.Count()*8+4);
        int count=0;
        for (int i=0;i<descriptions.Count();++i) {
            DDSURFACEDESC *description=descriptions[i];
            if (description->dwWidth<=maximumWidth && description->dwHeight<=maximumHeight &&
                description->dwWidth>=minimumWidth && description->dwHeight>=minimumHeight &&
                description->ddpfPixelFormat.dwRGBBitCount==bitDepth) {
                *next++=(int)description->dwWidth;
                *next++=(int)description->dwHeight;
                ++count;
            }
            delete descriptions[i];
        }
        if (next==result) {
            delete[] result;
            return 0;
        }
        qsort(result,count,8,Compare_Video_Mode_Size_00496260);
        return (VideoModeSize *)result;
    }
    return 0;
}
