// The score screen (Score.cpp; Westwood's SCORE.CPP ScoreClass, not
// polymorphic so no RTTI). Layout from Presentation 0x00663FE0 and the
// helpers after it; names follow SCORE.CPP where the code agrees, the rest
// are hypotheses.
#ifndef RA2_SHARED_SCORE_HPP
#define RA2_SHARED_SCORE_HPP
// Score.cpp inlines these vector members (Add_Anim, Update_Anims, the
// waits on Is_Anim_Done, the Houses loops).
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/vector_class.hpp"
#include "shared/rect.hpp"
#include "shared/score_anim.hpp"
#include "shared/score_font.hpp"
class Surface;
class ConvertClass;

class ScoreClass {
public:
    void Presentation();                                                // 0x00663FE0
    int Add_Anim(ScoreAnimClass *anim);                                // 0x00665E50
    bool Is_Anim_Done(ScoreAnimClass *anim);                            // 0x00665EC0 (no longer listed)
    Rect Count_Up_Print(Surface *surface, unsigned short const *format, int value, int max, int x, int y);    // 0x00666DD0
    void ScoreDelay(int ticks);                                         // 0x00667420
    void Update_Anims();                                                // 0x00667620
    void Blit_Score();                                                  // 0x006676C0
    void Cycle_Wait_Click(bool cycle);                                  // 0x00665EE0
    void Do_Graphs();                                                   // 0x006661E0
    void Do_Graph(int first, int second, int ypos);                     // 0x00666320
    void Show_Credits();                                                // 0x00666B60
    void Print_Time(unsigned long seconds);                             // 0x00666C70

    int XOffset;                                    // +0x00 (screen width - 640) / 2
    int YOffset;                                    // +0x04 (screen height - 400) / 2
    int unknown_08;                                 // +0x08 passed to every ScoreAnimClass::Update
    ScoreFontClass *Font;                           // +0x0C
    ScoreFontClass *unknown_font_10;                // +0x10 the time font
    ConvertClass *Drawer;                           // +0x14
    int Color;                                      // +0x18
    DynamicVectorClass<ScoreAnimClass *> Anims;     // +0x1C
};
#endif
