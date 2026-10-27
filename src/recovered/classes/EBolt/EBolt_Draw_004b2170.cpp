#include "shared/ebolt.hpp"
#include "shared/tactical.hpp"
extern Rect unknown_rect_839630;
// @ref ?Draw_Bolt_004B1900@EBolt@@QAEXUCoordStruct@@0H@Z=004b1900
void EBolt::Draw_004B2170()
{
 if(unknown_28) {
  Point2D start,end;
  unknown_tactical_83996c->Unknown_006A29D0(Start,start);
  unknown_tactical_83996c->Unknown_006A29D0(End,end);
  if(Clip_Line(start,end,unknown_rect_839630)) Draw_Bolt_004B1900(Start,End,unknown_2c ? 5 : 10);
  ++unknown_1c;
 }
 unknown_28>>=1;
}
