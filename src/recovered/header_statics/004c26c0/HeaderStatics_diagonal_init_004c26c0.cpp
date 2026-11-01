#define RA2_COORD_FROM_CELL_INLINE
#define RA2_COORD_AS_CELL
// Header-static dynamic initializers of the unit at 0x004C26C0 and the
// unit's FootClass list; the other drafts of this plan are emitted by this file.
#include "shared/unknown_geometry.hpp"
#include "shared/unknown_static_rect.hpp"
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/vector_class.hpp"
// The list is declared (extern) before it is defined: VC6 emits the
// initializer pair a second time for an extern redeclaration that follows
// the definition.
#include "shared/foot.hpp"

// Member-wise sum of two cells as this unit's code compiles it (Foot.CPP; a
// free sum built through TPoint2D<short>, hypothesis): Search_For_Tiberium_Weighted
// 0x004CBB40, 0x004C45B0 and slot 93 0x004C7220 order the component loads as
// this form does, where TPoint2D<short>::operator+ orders them otherwise. The
// guard is shared with BuildingClass slot 52's unit-local copy.
#ifndef RA2_CELLSTRUCT_PLUS
#define RA2_CELLSTRUCT_PLUS
inline Cell operator+(Cell const &left, Cell const &right)
{
    return TPoint2D<short>(short(left.X + right.X), short(left.Y + right.Y));
}
#endif

// The unit's list of FootClass objects (0x00865F38; name is a hypothesis).
DynamicVectorClass<FootClass *> unknown_FootClass_list_00865f38;
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??8?$VectorClass@PAVFootClass@@@@UBE_NABV0@@Z=004ce290
// @ref ??_7?$DynamicVectorClass@PAVFootClass@@@@6B@=007a1234
// @ref ??_7?$VectorClass@PAVFootClass@@@@6B@=007a1254
// @ref ??_G?$DynamicVectorClass@PAVFootClass@@@@UAEPAXI@Z=004cea40
// @ref ??_G?$VectorClass@PAVFootClass@@@@UAEPAXI@Z=004ce9f0
// @ref ?Clear@?$DynamicVectorClass@PAVFootClass@@@@UAEXXZ=004cdeb0
// @ref ?Clear@?$VectorClass@PAVFootClass@@@@UAEXXZ=004ce380
// @ref ?Fetch@?$VectorClass@PAVFootClass@@@@UBEPAVFootClass@@H@Z=004cdf00
// @ref ?ID@?$DynamicVectorClass@PAVFootClass@@@@UAEHABQAVFootClass@@@Z=004ce4c0
// @ref ?ID@?$DynamicVectorClass@PAVFootClass@@@@UAEHPBQAVFootClass@@@Z=004cdee0
// @ref ?ID@?$VectorClass@PAVFootClass@@@@UAEHABQAVFootClass@@@Z=004ce3b0
// @ref ?ID@?$VectorClass@PAVFootClass@@@@UAEHPBQAVFootClass@@@Z=004ce3f0
// @ref ?Resize@?$DynamicVectorClass@PAVFootClass@@@@UAE_NHPBQAVFootClass@@@Z=004ce410
// @ref ?Resize@?$VectorClass@PAVFootClass@@@@UAE_NHPBQAVFootClass@@@Z=004ce2d0
// @ref ?unknown_FootClass_list_00865f38@@3V?$DynamicVectorClass@PAVFootClass@@@@A=00865f38
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref _$E42=004c28f0
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
// @ref _atexit=0078298a
// @ref _unknown_geometry_angle45=00865f50
// @ref _unknown_geometry_angle60=00865f10
// @ref _unknown_geometry_angle90=00865ee8
// @ref _unknown_geometry_b=00865f68
// @ref _unknown_geometry_c=00865f58
// @ref _unknown_geometry_deg_to_rad=007a11f8
// @ref _unknown_geometry_diagonal=00865f08
// @ref _unknown_geometry_g=00865f70
// @ref _unknown_geometry_h=00865f18
// @ref _unknown_geometry_i=00865f30
// @ref _unknown_geometry_j=00865f60
// @ref _unknown_geometry_k=00865f00
// @ref _unknown_geometry_l=00865f20
// @ref _unknown_geometry_sixty=007a11f0
// @ref _unknown_static_rect=00865ef0

#include "shared/cell.hpp"
