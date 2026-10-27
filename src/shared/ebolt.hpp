#ifndef RA2_EBOLT_HPP
#define RA2_EBOLT_HPP
#include "shared/foot.hpp"     // UnitClass (shared/unit.hpp when included first)
// EBolt name from VectorClass<EBolt *> RTTI; layout from original constructor.
// Start/End and Owner meanings are checked by draw and attachment operations.
class EBolt {
public:
 EBolt();
 static void __fastcall Update_All_004B2210();
 void Setup_004B2430(CoordStruct start,CoordStruct end,int value);
 void Draw_004B2170();
 // Pure drawing helper; association with EBolt is a hypothesis (original ECX unused).
 void Draw_Line_004B1850(CoordStruct start,CoordStruct end,int color,int first_depth,int second_depth);
 void Draw_Bolt_004B1900(CoordStruct start,CoordStruct end,int count);
 ~EBolt() { if(Owner) { Owner->unknown_5c4=0; Owner=0; } }
 static void Delete_All_004B23B0();
 CoordStruct Owner_Coord_004B2510();
 void Attach_004B2580(TechnoClass *owner,int index);
 CoordStruct Start; // +00
 CoordStruct End; // +0c
 int unknown_18;
 int unknown_1c;
 UnitClass *Owner; // +20
 int unknown_24;
 int unknown_28;
 bool unknown_2c;
};
#endif
