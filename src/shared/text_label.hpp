// TextLabelClass (TextLabel.cpp, unit 0x006F13D0-0x006F180F; RTTI vtable 0x007ADCCC, 34 slots):
// a gadget that prints a string; the message list's lines and edit line
// (shared/message_list.hpp). Tiberian Sun txtlabel.h shape with RA2's
// additions after PixWidth (the reveal "typewriter" and hidden flag).
// Layout from the constructor 0x006F15C0 and Draw_Me 0x006F1620:
//   +0x24 UserData1 (the message list's expiry time), +0x28 UserData2 (its id),
//   +0x2C Style, +0x30 Text, +0x34 Color (ColorSchemes index), +0x38 PixWidth
//   (-1: the surface width), +0x3C the edit text scroll position, +0x40 bool
//   (no draw while set), +0x41 bool (reveal the text a character at a time),
//   +0x44 the revealed character count, +0x48 the time of the last reveal step.
//   size 0x4C. Names after PixWidth are hypotheses.
#ifndef RA2_SHARED_TEXT_LABEL_HPP
#define RA2_SHARED_TEXT_LABEL_HPP

#include "shared/gadget.hpp"

class TextLabelClass : public GadgetClass {
public:
    TextLabelClass(wchar_t const *text, int x, int y, int color, unsigned style);   // 0x006F15C0

    virtual int Draw_Me(int forced = false);                        // slot 27 0x006F1620
    virtual void Set_Text(wchar_t const *text) { Text = text; }     // slot 33 (kept copy 0x006F17E0)

    int UserData1;          // +0x24 (signed: MessageListClass::Update_Messages 0x005B5610 compares it with jg)
    unsigned UserData2;     // +0x28
    unsigned Style;         // +0x2C
    wchar_t const *Text;    // +0x30
    int Color;              // +0x34
    int PixWidth;           // +0x38
    int Scroll;             // +0x3C (edit text scroll position; name hypothesis)
    bool IsHidden;          // +0x40 (name hypothesis)
    bool IsRevealed;        // +0x41 (name hypothesis)
    int RevealCount;        // +0x44 (name hypothesis)
    unsigned RevealTime;    // +0x48 (name hypothesis)
};

#endif
