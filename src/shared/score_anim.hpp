// The score screen's animations (Score.cpp; Westwood's SCORE.CPP classes):
// ScoreAnimClass (RTTI vtable 0x007A928C, Update pure), ScoreTimeClass
// (0x007A9278, cycles shape frames) and ScorePrintClass (0x007A9264, types a
// string). Layout from the constructors 0x006682C0 and 0x006680A0 and
// ScoreTimeClass::Update 0x00667F90; names follow SCORE.CPP where the code
// agrees (hypotheses otherwise).
#ifndef RA2_SHARED_SCORE_ANIM_HPP
#define RA2_SHARED_SCORE_ANIM_HPP

#include "shared/cd_timer.hpp"
#include "shared/system_timer.hpp"

struct ShapeFileStruct;
class ConvertClass;
class ScoreFontClass;
class Surface;

class ScoreAnimClass {
public:
    ScoreAnimClass(int x, int y, void const *data);             // 0x006682C0
    virtual ~ScoreAnimClass() {}                                // deleting 0x00668370
    virtual void Pause();                                       // slot 1 0x00668300 (stops the timer)
    virtual void Resume();                                      // slot 2 0x00668350 (starts it)
    virtual bool Update(Surface *surface) = 0;                       // slot 3

    int XPos;                                       // +0x04
    int YPos;                                       // +0x08
    CDTimerClass<SystemTimerClass> Timer;           // +0x0C
    void const *DataPtr;                            // +0x18 shape or string
};

class ScoreTimeClass : public ScoreAnimClass {
public:
    ScoreTimeClass(int x, int y, void const *data, int maxStage, int delay, ConvertClass *drawer); // 0x00667F40
    virtual ~ScoreTimeClass() {}                                // deleting 0x00668390
    virtual bool Update(Surface *surface);                           // slot 3 0x00667F90

    int Stage;                                      // +0x1C current frame
    int MaxStage;                                   // +0x20
    int DelayFrames;                                // +0x24
    ConvertClass *Drawer;                           // +0x28
};

class ScorePrintClass : public ScoreAnimClass {
public:
    ScorePrintClass(void const *string, int x, int y, ScoreFontClass *font, bool background);  // 0x006680A0
    virtual ~ScorePrintClass() {}                               // deleting 0x006683B0
    virtual bool Update(Surface *surface);                           // slot 3 0x006680F0

    int Stage;                                      // +0x1C characters typed
    int unknown_20;                                 // +0x20
    bool Background;                                // +0x24
    ScoreFontClass *Font;                           // +0x28 draws the string
};

// Set by every ScorePrintClass::Update (0x00AB6F9C; purpose unknown).
extern bool unknown_score_print_ab6f9c;

#endif
