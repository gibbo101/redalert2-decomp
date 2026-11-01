#include "shared/radar.hpp"
#include "shared/techno.hpp"
#include "shared/map_view.hpp"
#include "shared/color_scheme.hpp"
#include "shared/hicolor.hpp"

extern MouseClass Map;
ColorScheme *__fastcall unknown_color_scheme_663d30(char const *name,int kind);

void RadarClass::Unknown_00632000(Point2D const &point)
{
    if(!unknown_player_a35db4) return;
    if(!unknown_1218->Get_Rect().Is_Point_Within(point)) return;
    Cell cell=Unknown_00631500(point);
    CoordStruct coord(cell.X*256+128,cell.Y*256+128,0);
    coord.Z=Map.Unknown_0055A280(coord);
    bool shadow=unknown_b263d8 && Map.Unknown_00568140(coord);
    bool dim=unknown_b263d8 && Map.Unknown_00568280(coord);
    TechnoClass *tech=0;
    DynamicVectorClass<HashObject<RadarTrackingStruct,TechnoClass *> > &bucket=unknown_1254->Buckets[Unknown_00631C40(point)&255];
    int count=bucket.Count();
    HashObject<RadarTrackingStruct,TechnoClass *> *items=&bucket[0];
    for(int index=0;index<count;++index) {
        TechnoClass *candidate=items[index].Key.unknown_00;
        if(items[index].Key.unknown_04==point &&
            (!shadow || candidate->House->Unknown_004F52B0()) &&
            (!candidate->unknown_slot32()->unknown_1ff || unknown_player_a35db4->Is_Ally(candidate))) {
            tech=candidate;
            break;
        }
    }
    if(tech) {
        HouseClass *owner=tech->House;
        if(tech->unknown_slot48()) owner=tech->unknown_slot51(false);
        int color;
        if(owner) color=Build_Hicolor_Pixel(owner->unknown_55e9.Red,owner->unknown_55e9.Green,owner->unknown_55e9.Blue);
        else color=unknown_color_scheme_663d30("LightGrey",1)->unknown_color_0x330;
        int remaining=tech->unknown_13c.Value();
        if(remaining>0 && ((remaining-1)/Rules->FlashFrameTime)%2==1 && tech->House==unknown_player_a35db4)
            unknown_1218->Put_Pixel(point,~color);
        else unknown_1218->Put_Pixel(point,color);
    } else {
        if(dim) {
            RGBClass color=Unpack_Hicolor_Pixel((unsigned short)unknown_121c->Get_Pixel(point));
            unknown_1218->Put_Pixel(point,Build_Hicolor_Pixel(color.Red>>1,color.Green>>1,color.Blue>>1));
        } else {
            if(!shadow) unknown_1218->Put_Pixel(point,unknown_121c->Get_Pixel(point));
            else unknown_1218->Put_Pixel(point,0);
        }
    }
    unknown_1208=Union(unknown_1208,Rect(point.X,point.Y,1,1)+Point2D(unknown_1498.X,unknown_1498.Y));
}
// @ref _$S62=00ab6308
// @ref __ftol=0077f110

// External references verified against complete original body operands.
// @ref ??_C@_09LBMK@LightGrey?$AA@=007ebfc4
// @ref ?Frame@@3HA=00a40d2c
// @ref ?Is_Ally@HouseClass@@QBE_NPBVTechnoClass@@@Z=004e5580
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?Unknown_0055A280@MapClass@@QAEHABUCoordStruct@@@Z=0055a280
// @ref ?Unknown_00568140@MapClass@@QAE_NABUCoordStruct@@@Z=00568140
// @ref ?Unknown_00568280@MapClass@@QAE_NABUCoordStruct@@@Z=00568280
// @ref ?unknown_b263d8@@3HA=00b263d8
// @ref ?unknown_color_scheme_663d30@@YIPAVColorScheme@@PBDH@Z=00663d30
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?unknown_shift_852fb8@@3HA=00852fb8
// @ref ?unknown_shift_852fbc@@3HA=00852fbc
// @ref ?unknown_shift_852fc0@@3HA=00852fc0
// @ref ?unknown_shift_852fc4@@3HA=00852fc4
// @ref ?unknown_shift_852fc8@@3HA=00852fc8
// @ref ?unknown_shift_852fcc@@3HA=00852fcc
// @ref __ftol=0077f110
// @ref __real@4@3ffe8000000000000000=0079dd80
// @ref __real@8@3ffe8000000000000000=0079a728
