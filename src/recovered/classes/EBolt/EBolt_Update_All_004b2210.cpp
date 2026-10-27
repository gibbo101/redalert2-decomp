#include "shared/ebolt.hpp"
extern CoordStruct const unknown_ebolt_zero_00853028;
// @ref ?unknown_ebolt_zero_00853028@@=00853028
// The no-argument fastcall convention is an exact-code hypothesis.
void __fastcall EBolt::Update_All_004B2210()
{
 for(int i=unknown_EBolt_list_00853050.Count()-1;i>=0;--i) {
  EBolt *bolt=unknown_EBolt_list_00853050[i];
  if(bolt->Owner) {
   CoordStruct coord=bolt->Owner->unknown_slot43(bolt->unknown_24);
   if(coord!=unknown_ebolt_zero_00853028) bolt->Start=coord;
  }
  bolt->Draw_004B2170();
  if(!bolt->unknown_28) {
   unknown_EBolt_list_00853050.Delete(bolt);
   delete bolt;
  }
 }
}
