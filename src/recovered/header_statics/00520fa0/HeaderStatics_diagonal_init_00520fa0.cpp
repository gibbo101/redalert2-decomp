// Header-static dynamic initializers of the unit at 0x00520FA0:  the
// shared/unknown_geometry.hpp constants and unknown_static_rect.hpp
// (0x00520FA0-0x00521186), then IonBlast.cpp's file data; the other
// initializer drafts of this plan are emitted by these includes and definitions.
#include "shared/unknown_geometry.hpp"
#include "shared/unknown_static_rect.hpp"
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/vector_class.hpp"
#include "shared/rect.hpp"
#include "shared/surface.hpp"
#include "shared/unknown_globals.hpp"
#define RA2_ION_BLAST_LIST
#include "shared/ion_blast.hpp"

extern "C" int __cdecl abs(int);
#pragma intrinsic(abs)

// IonBlast.cpp's file data (TibSun ionblast.cpp names; the wave constants'
// values match TibSun's): the spiral index to surface offset table and the
// stride it was built for, the 80 precalculated shockwave surfaces, the
// shockwave parameters and the list of blasts in progress. WaveSpeed
// (0x00521190), WavePhaseSpeed (0x005211B0) and IonBlasts (0x005211D0, which
// registers the guarded atexit destructor 0x00521210) have dynamic initializers.
int SpiralIndexToSurfaceLUT[289];
int BlastSurfaceStride = 0;
BSurface *BlastSurfaces[80];

static double const WaveStartDistance = 0.0;
static double const WaveBandWidth = 57.0;
static double const WaveFrequency = 0.11;
static double const WaveAmplitudeFalloff = 25.0;
static double const WaveRockScale = 6.283185307179586;     // 360 degrees in radians
static double const WaveSpeedScale = 0.0125;

static double WaveSpeed = ((256.0 - WaveStartDistance) + WaveBandWidth) * WaveSpeedScale;
static double WavePhaseSpeed = WaveSpeed;

DynamicVectorClass<IonBlastClass *> IonBlastClass::IonBlasts;

// TibSun's MAX (Point_To_Spiral_Index keeps the second operand unless the
// first is larger).
template <class T> inline T Max(T a, T b) { return (a > b) ? a : b; }

Point2D __fastcall Spiral_Index_To_Point(int index);
int __fastcall Point_To_Spiral_Index(Point2D point);
void __fastcall Calculate_Index_To_Surface_LUT(int stride);
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref __CIpow=007821b0
// @ref __ftol=0077f110
// @ref __real@8@3ff78000000000000000=0079a730
// @ref __real@8@3ffe8000000000000000=0079a728
// @ref __real@8@3fff8000000000000000=0079a708
// @ref __real@8@40008000000000000000=0079a6f8
// @ref __real@8@4004b400000000000000=0079a710
// @ref __real@8@4004f000000000000000=0079a718
// @ref __real@8@4005b400000000000000=0079a720
// @ref __real@8@40078000000000000000=0079a700
// @ref _unknown_geometry_angle45=00a51f78
// @ref _unknown_geometry_angle60=00a51e08
// @ref _unknown_geometry_angle90=00a51950
// @ref _unknown_geometry_b=00a51fa8
// @ref _unknown_geometry_c=00a51f80
// @ref _unknown_geometry_deg_to_rad=007a4598
// @ref _unknown_geometry_diagonal=00a51e00
// @ref _unknown_geometry_g=00a51fb0
// @ref _unknown_geometry_h=00a51e10
// @ref _unknown_geometry_i=00a51e30
// @ref _unknown_geometry_j=00a51fa0
// @ref _unknown_geometry_k=00a51df8
// @ref _unknown_geometry_l=00a51e20
// @ref _unknown_geometry_sixty=007a4590
// @ref _unknown_static_rect=00a51de0
// @ref ?SpiralIndexToSurfaceLUT@@3PAHA=00a51958
// @ref ?BlastSurfaceStride@@3HA=00a51fb8
// @ref ?BlastSurfaces@@3PAPAVBSurface@@A=00a51e38
// @ref ?IonBlasts@IonBlastClass@@2V?$DynamicVectorClass@PAVIonBlastClass@@@@A=00a51f88
// @ref _WaveSpeed=00a51df0
// @ref _WavePhaseSpeed=00a51e18
// @ref _WaveStartDistance=007a45a0
// @ref _WaveBandWidth=007a45a8
// @ref _WaveSpeedScale=007a45c8
// @ref ?AI@IonBlastClass@@QAEXXZ=00521340
// @ref ?Draw_It@IonBlastClass@@QAEXXZ=00521ce0
// @ref ??3@YAXPAX@Z=00781d3b
// @ref _atexit=0078298a
// @ref _$S49=00a51948
// @ref ??_7?$DynamicVectorClass@PAVIonBlastClass@@@@6B@=007a45d4
// @ref ??_7?$VectorClass@PAVIonBlastClass@@@@6B@=007a45f4
// @ref ??_E?$DynamicVectorClass@PAVIonBlastClass@@@@UAEPAXI@Z=005224b0
// @ref ??_E?$VectorClass@PAVIonBlastClass@@@@UAEPAXI@Z=00522460
// @ref ??8?$VectorClass@PAVIonBlastClass@@@@UBE_NABV0@@Z=00522200
// @ref ?Resize@?$DynamicVectorClass@PAVIonBlastClass@@@@UAE_NHPBQAVIonBlastClass@@@Z=00522380
// @ref ?Clear@?$DynamicVectorClass@PAVIonBlastClass@@@@UAEXXZ=005221a0
// @ref ?ID@?$DynamicVectorClass@PAVIonBlastClass@@@@UAEHABQAVIonBlastClass@@@Z=00522430
// @ref ?ID@?$DynamicVectorClass@PAVIonBlastClass@@@@UAEHPBQAVIonBlastClass@@@Z=005221d0
// @ref ?Fetch@?$VectorClass@PAVIonBlastClass@@@@UBEPAVIonBlastClass@@H@Z=005221f0
// @ref ?Resize@?$VectorClass@PAVIonBlastClass@@@@UAE_NHPBQAVIonBlastClass@@@Z=00522240
// @ref ?Clear@?$VectorClass@PAVIonBlastClass@@@@UAEXXZ=005222f0
// @ref ?ID@?$VectorClass@PAVIonBlastClass@@@@UAEHABQAVIonBlastClass@@@Z=00522320
// @ref ?ID@?$VectorClass@PAVIonBlastClass@@@@UAEHPBQAVIonBlastClass@@@Z=00522360
