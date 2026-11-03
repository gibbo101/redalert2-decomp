// Draw the building radius, with a timed concentric radial indicator when configured.
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/rgb_class.hpp"
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
void __fastcall Draw_Radial_Indicator_00451BF0(unsigned int radius,unsigned char mode,
    CoordStruct center,RGBClass color,bool filled,bool radius_is_pixels);
// @ref ?unknown_451930@BuildingClass@@=00451930
// @ref ?Unknown_004F52B0@HouseClass@@=004f52b0
// @ref ?Draw_Radial_Indicator_00451BF0@@=00451bf0
// @ref ?Adjust@RGBClass@@=0063cf20
// @ref __real@8@3ffe8000000000000000=0079a728
// @ref __real@8@4004f000000000000000=0079a718
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref _?$S81@?7??unknown_slot74@BuildingClass@@UAEXH@Z@4EA=0084ece8
// @ref _?white@?7??unknown_slot74@BuildingClass@@UAEXH@Z@4VRGBClass@@A=0084ecf8
// @ref _$E81=00451be0
void BuildingClass::unknown_slot74(int arg1)
{
    unsigned int radius=(unsigned int)unknown_451930();
    if((int)radius>0 && unknown_530 && House->Unknown_004F52B0()) {
        if(Type->ConcentricRadialIndicator) {
            static RGBClass white(255,255,255);
            RGBClass color=House->unknown_55e9;
            unsigned int phase=(timeGetTime()>>1)&0x3ff;
            if(!(phase&0x200)) {
                if(!(phase&0x100)) color.Adjust((~phase)&0xff,white);
                Draw_Radial_Indicator_00451BF0(radius,0,Center_Coord(),color,false,false);
            }
            double scaled=(double)radius+0.5;
            unsigned int pixels=(unsigned int)(int)(scaled/unknown_sqrt_4ba410(2.0)*60.0);
            pixels=(pixels*phase)>>10;
            if(pixels>32) Draw_Radial_Indicator_00451BF0(pixels,0,Center_Coord(),House->unknown_55e9,false,true);
        } else {
            Draw_Radial_Indicator_00451BF0(radius,(unsigned char)arg1,Center_Coord(),House->unknown_55e9,true,false);
        }
    }
}
