#include "shared/rad_beam_list.hpp"
#include "shared/hicolor.hpp"
// @ref ?unknown_635c30@RadBeam@@QAEXXZ=00635c30
bool RadBeam::unknown_6358d0()
{
    if (!unknown_00) {
        unknown_00=true;
        Compute_Delta();
    }
    if (IsActive) {
        Steps=(int)(Length/StepLength);
        int x=Delta.X;
        int y=Delta.Y;
        int z=Delta.Z;
        if(Steps!=0) { x/=Steps; y/=Steps; z/=Steps; }
        StepDelta=CoordStruct(x,y,z);
        Current=Source;
        double phase=unknown_6c;
        phase/=Period;
        unknown_70=phase*Amplitude;
        CurrentColor=Color;
        for(unknown_78=0;double(unknown_78)*StepLength<Length;++unknown_78) {
            unknown_635c30();
            unsigned short green=CurrentColor.Green;
            short pixel=(short)Build_Hicolor_Pixel(CurrentColor.Red,green,CurrentColor.Blue);
            Draw_Line(Current,unknown_98,pixel);
        }
    }
    ++unknown_6c;
    return unknown_6c>=Period;
}
