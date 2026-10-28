// A radiation or chrono beam (RadBeam.cpp, 0x00635440-0x006362D9; 0xB8 bytes).
// Allocate (0x00635440) makes one and lists it in RadBeamList::Array
// (shared/rad_beam_list.hpp). Layout from the constructor 0x006356B0, the
// setters and the step computations 0x00635B30-0x00636020. The class name
// and member names are hypotheses (public YR references call it RadBeam);
// TechnoClass 0x006CA1D0 calls the setters out of line.
#ifndef RA2_SHARED_RAD_BEAM_HPP
#define RA2_SHARED_RAD_BEAM_HPP

#include "shared/coord.hpp"
#include "shared/rgb_class.hpp"

class RadBeam {
public:
    RadBeam(int type);                              // 0x006356B0
    static RadBeam *__fastcall Allocate(int type);  // 0x00635440 (type 1 for TechnoClass beams)
    void Set_Color(RGBClass const &color);          // 0x00635710 (+0x18)
    void Set_Depth(int depth);                      // 0x00635730 (+0x04; the screen height difference of the ends)
    void Set_Source(CoordStruct const &coord);      // 0x00635740 (+0x1C)
    void Set_Target(CoordStruct const &coord);      // 0x00635760 (+0x28)
    void Set_Period(int period);                    // 0x00635780 (+0x34)
    void Set_Amplitude(double amplitude);           // 0x00635790 (+0x38)
    void unknown_6357b0(double value);              // 0x006357B0 (+0x40)
    void unknown_6357d0(int value);                 // 0x006357D0 (+0x48)
    void Deactivate();                              // 0x006357E0 (IsActive false)
    bool Is_Active() const;                         // 0x006357F0
    void Set_Step_Length(int length);               // 0x00635800 (+0x10)
    // Delta = Target - Source and its Length.
    void Compute_Delta();                           // 0x00635B30
    // Steps (Length / StepLength), StepDelta, Current, the wave value and
    // the current colour for a new pass.
    void Start_Pass();                              // 0x00635BA0
    // Delta, Length, Steps and the per-step delta at +0x60.
    void unknown_635f80();                          // 0x00635F80
    // The wave value at time unknown_6c, Delta moved along +0x60 by
    // unknown_48 * unknown_6c * unknown_40 steps, then Length, Steps and StepDelta.
    void unknown_636020();                          // 0x00636020
    // The start (Current) and end (+0x98) of step unknown_78 on the wave, and
    // its colour.
    void unknown_636130();                          // 0x00636130
    // One frame of a type 2 beam; true once the period is over.
    bool unknown_635e00();                          // 0x00635E00
    // Draws one segment on the current surface (inlined by unknown_635e00).
    void Draw_Line(CoordStruct const &start, CoordStruct const &end, short color);   // 0x00635810

    bool unknown_00;                                // +0x00
    bool IsActive;                                  // +0x01 (true; Deactivate clears it)
    int Depth;                                      // +0x04
    int Type;                                       // +0x08
    int unknown_0c;                                 // +0x0C
    double StepLength;                              // +0x10 (Allocate: 10 for type 1, else 20)
    RGBClass Color;                                 // +0x18
    CoordStruct Source;                             // +0x1C
    CoordStruct Target;                             // +0x28
    int Period;                                     // +0x34
    double Amplitude;                               // +0x38
    double unknown_40;                              // +0x40
    int unknown_48;                                 // +0x48
    CoordStruct Delta;                              // +0x4C Target - Source
    double Length;                                  // +0x58 length of Delta
    CoordStruct unknown_60;                         // +0x60 Delta / Steps (unknown_635f80)
    int unknown_6c;                                 // +0x6C time within the period
    double unknown_70;                              // +0x70 the wave value
    int unknown_78;                                 // +0x78
    int Steps;                                      // +0x7C
    CoordStruct StepDelta;                          // +0x80
    CoordStruct Current;                            // +0x8C
    CoordStruct unknown_98;                         // +0x98 the step's end (unknown_636130)
    int unknown_a4;                                 // +0xA4
    double unknown_a8;                              // +0xA8 colour scale (unknown_636130)
    RGBClass CurrentColor;                          // +0xB0
    int unknown_b4;                                 // +0xB4 (size 0xB8)
};

#endif
