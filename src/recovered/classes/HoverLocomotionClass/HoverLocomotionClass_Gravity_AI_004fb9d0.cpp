// @ref ?Fast_Sin@@YAMN@Z=004ba480
// @ref ?Frame@@3HA=00a40d2c
// @ref ?Is_Powered@LocomotionClass@@UAG_NXZ=0053d230
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Unknown_0055A280@MapClass@@QAEHABUCoordStruct@@@Z=0055a280
// @ref ?unknown_facing_offsets_851ac0@@3QBUUnknownFacingOffset@@B=00851ac0
// @ref ?unknown_hover_bob_scale_79c9b8@@3NB=0079c9b8
// @ref __ftol=0077f110
// @ref __real@8@3fff8000000000000000=0079a708
// @ref __real@8@3fff8cccccccccccd000=007a32e0
// @ref __real@8@4008e100000000000000=0079b608
#include "shared/hover_locomotion.hpp"
#include "shared/rules.hpp"
#include "shared/infantry.hpp"
extern double const unknown_hover_bob_scale_79c9b8;
// @ref ?unknown_hover_bob_scale_79c9b8@@3NB=0079c9b8
// @ref __real@8@3fff8cccccccccccd000=007a32e0
inline CoordStruct Hover_Adjacent_Coord_004fb9d0(CoordStruct const &coord,int facing)
{
    UnknownFacingOffset const &offset=unknown_facing_offsets_851ac0[facing&7];
    return CoordStruct(coord.X+offset.X,coord.Y+offset.Y,coord.Z);
}
void HoverLocomotionClass::Gravity_AI_004fb9d0()
{
    int height=LinkedTo->unknown_slot108();
    int clearance=height;
    if (LinkedTo->unknown_4d0!=-1) {
        int ground=Map.Unknown_0055A280(Object_Coord(LinkedTo));
        if (Map.Unknown_0055A280(Hover_Adjacent_Coord_004fb9d0(Object_Coord(LinkedTo),LinkedTo->unknown_4d0))>ground) clearance-=Rules->HoverHeight;
    }
    height=(int)(height+unknown_60);
    int id=LinkedTo->Fetch_ID();
    double period=(id&1?1.0:1.1)*Rules->HoverBob*900;
    double angle=Fast_Sin((double)((Frame+2*id)%(int)period)*unknown_hover_bob_scale_79c9b8/period);
    height=(int)(2*angle+height);
    if (height<0) { unknown_60=0; height=0; }
    bool wasdown=LinkedTo->unknown_74;
    LinkedTo->unknown_74=false;
    LinkedTo->unknown_slot109(height);
    LinkedTo->unknown_74=wasdown;
    if (clearance<Rules->HoverHeight) {
        if (LocomotionClass::Is_Powered()) {
            unknown_60+=((double)Rules->HoverHeight+(double)Rules->HoverHeight-(double)clearance)/(double)Rules->HoverHeight*(double)Rules->unknown_1320;
        }
        if (clearance<Rules->HoverHeight/4) unknown_60+=(double)(Rules->unknown_1320/3);
    }
    unknown_60-=Rules->unknown_1320;
    unknown_60*=Rules->HoverDampen;
}
