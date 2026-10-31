#include "shared/techno.hpp"
#include "shared/selection_coord.hpp"
#include "shared/tactical.hpp"
void __fastcall Draw_Double_Selection_Bracket_006c3950(::Coord const &first,::Coord const &second,int color)
{
    ::Coord first_tick=(first+first+first+second)/4;
    ::Coord second_tick=(second+second+second+first)/4;
    if (first.Z>first_tick.Z) {
        unknown_tactical_83996c->unknown_slot24(reinterpret_cast<CoordStruct const &>(first),reinterpret_cast<CoordStruct const &>(first_tick),color,0);
    } else {
        unknown_tactical_83996c->unknown_slot24(reinterpret_cast<CoordStruct const &>(first_tick),reinterpret_cast<CoordStruct const &>(first),color,0);
    }
    if (second.Z>second_tick.Z) {
        unknown_tactical_83996c->unknown_slot24(reinterpret_cast<CoordStruct const &>(second),reinterpret_cast<CoordStruct const &>(second_tick),color,0);
    } else {
        unknown_tactical_83996c->unknown_slot24(reinterpret_cast<CoordStruct const &>(second_tick),reinterpret_cast<CoordStruct const &>(second),color,0);
    }
}
