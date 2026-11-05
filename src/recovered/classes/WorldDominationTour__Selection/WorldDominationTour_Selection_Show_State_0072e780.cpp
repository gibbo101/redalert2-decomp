// void Selection::Show_State(rc_ptr<State> const &state, bool unknown2, bool won) (0x0072E780): moves the
// map to a new state, updating each territory's owner overlay, then (unknown2) plays the zoom and throb
// target animations on the disputed territories (TibSun Selection::Do_Target_Anim).
// The cursor walks follow TibSun wdtsel.cpp: postfix ++, virtual operator bool.
// Walk_Territories is a hypothesis: the main walk's cursor constructor sits one inline level down
// (out of line here, inline in the later anim walks), and no spelling at depth one refuses it.
// @ref ??0?$VectorClass@PAVMSAnim@@@@QAE@IPBQAVMSAnim@@@Z=00730470
// @ref ??_7?$VectorCursor@PAVMSAnim@@V?$DynamicVectorClass@PAVMSAnim@@@@@@6B@=007af3a4
// @ref ??_C@_0L@JIID@TargetZoom?$AA@=007fc588
// @ref ??_G?$VectorCursor@PAVMSAnim@@V?$DynamicVectorClass@PAVMSAnim@@@@@@UAEPAXI@Z=007303f0
// @ref ??B?$VectorCursor@PAVMSAnim@@V?$DynamicVectorClass@PAVMSAnim@@@@@@UBE_NXZ=007303a0
// @ref ??E?$VectorCursor@PAVMSAnim@@V?$DynamicVectorClass@PAVMSAnim@@@@@@UAEAAV0@XZ=00730450
// @ref ??F?$VectorCursor@PAVMSAnim@@V?$DynamicVectorClass@PAVMSAnim@@@@@@UAEAAV0@XZ=00730460
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/wdt_selection.hpp"
#include "shared/ms_anim.hpp"
namespace WorldDominationTour {
inline TerritoryCursor Walk_Territories(TerritoryList &list) { return TerritoryCursor(list); }
typedef DynamicVectorClass<MSAnim *> AnimList;
typedef VectorCursor<MSAnim *, AnimList> AnimCursor;
void Selection::Show_State(rc_ptr<State> const &state, bool unknown2, bool won)
{
    Remove_Territory_Anims();
    AnimList fades;
    AnimList shapes;
    for (TerritoryCursor cursor = Walk_Territories(TheMap->Territories); cursor; cursor++) {
        int index = (*cursor)->Get_Index();
        int old_owner = unknown_488->Owner_Of(index);
        int owner = state->Owner_Of(index);
        if (owner != old_owner) {
            Check_Escape();
            (*cursor)->Set_Owner_State(owner, this, !Escaped || won);
        }
        if (unknown2 && owner == 1) {
            Point2D point = TheMap->Get_Origin() + (*cursor)->Get_Target();
            int x = point.X;
            int y = point.Y;
            if (ZoomingTarget != 0) {
                CCFileClass file(ZoomingTarget->Get_Filename());
                if (file.Is_Available()) {
                    MSFadeAnim *fade = new MSFadeAnim(ZoomingTarget->Get_Filename(), x, y, TargetPalette, 3, 0x200, &Anims);
                    fades.Add(fade);
                }
            }
            CCFileClass file(Target->Name);
            if (file.Is_Available()) {
                MSShapeAnim *shape = new MSShapeAnim(Target->Name, x, y, TargetPalette, 5, true, 0x200);
                int frame = TargetDividingFrame - 1;
                shape->Set_End_Frame(frame);
                shape->Set_Start_Frame(0);
                shape->Set_Frame(0);
                (*cursor)->Set_unknown_2c((int)shape);
                shapes.Add(shape);
            }
        }
    }
    AnimCursor fade(fades);
    for (AnimCursor shape(shapes); shape; shape++) {
        Check_Escape();
        if (fade) {
            if (Escaped) {
                MSAnim *anim = *fade;
                delete anim;
            } else {
                Play_Sound("TargetZoom");
                Add_Anim(*fade);
                Wait_For(*fade, 300000);
            }
            fade++;
        }
        Add_Anim(*shape);
    }
    unknown_488 = state;
}
}
