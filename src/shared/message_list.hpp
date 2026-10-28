// MessageListClass (Westwood's on-screen message list; "MessageListClass::Init(Width: %d)" debug text
// at 0x005B4C60). Only the members the recovered functions use are named; the class has no vtable.
// Constructor 0x005B4BD0, Init 0x005B4C60.
#ifndef RA2_SHARED_MESSAGE_LIST_HPP
#define RA2_SHARED_MESSAGE_LIST_HPP

#include "shared/debug_printf.hpp"

// A message node (a MessageNode_006f15c0 of shared/message_gadget_layout.hpp; the list is linked through the
// LinkClass-style slots: slot 1 is the next node, slot 4 appends to a list, slot 9 removes the node and returns the next one).
class UnknownMessageNode {
public:
    virtual ~UnknownMessageNode();                              // slot 0
    virtual UnknownMessageNode *Next();                         // slot 1
    virtual void unknown_slot2();
    virtual void unknown_slot3();
    virtual void Append(UnknownMessageNode *list);              // slot 4
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual void unknown_slot8();
    virtual UnknownMessageNode *Remove();                       // slot 9

    char unknown_04[0x10 - 0x04];
    int Y;                                                      // +0x10
    char unknown_14[0x24 - 0x14];
    int Expires;                                                // +0x24 the SystemTimerClass time it goes away (0: never)
    int Identifier;                                             // +0x28
    char unknown_2c[0x30 - 0x2C];
    unsigned short *Text;                                       // +0x30 one of the list's text slots
    char unknown_34[0x38 - 0x34];
    int MaximumWidth;                                           // +0x38
    char unknown_3c[0x41 - 0x3C];
    bool unknown_41;                                            // +0x41
};

extern bool unknown_flag_a3f208;         // 0x00A3F208 (game mode 3: new messages are marked)
extern bool unknown_flag_a3f209;         // 0x00A3F209 (game mode 4)

class MessageListClass {
public:
    MessageListClass();                                                             // 0x005B4BD0
    // Init with the default width of 640 (0x005B4C40).
    void Reset();
    // Resets the list and its geometry: position, maximum messages (at most 14) and characters (at most 112),
    // an optional second position (-1: the same), and the selection range; width is the pixel width.
    // Adds a message (an optional "prefix: " and the text, wrapped to the width; the rest goes in further messages).
    UnknownMessageNode *Add_Message(unsigned short const *prefix, int identifier, unsigned short const *text, int color,
        unsigned style, int delay, bool unknown_flag);                              // 0x005B4DA0
    // Removes the messages that have expired, frees their text slots and restacks the rest (0x005B5610); whether any went.
    int Update_Messages();
    void Init(int x, int y, int max_messages, int max_chars, int unknown_arg5, int x2, int y2,
        bool unknown_flag, int first, int last, int width);                         // 0x005B4C60

    UnknownMessageNode *First;               // +0x000 the message nodes
    int X;                          // +0x004
    int Y;                          // +0x008
    int MaxMessages;                // +0x00C
    int MaxChars;                   // +0x010
    int Height;                     // +0x014 (19)
    bool unknown_18;                // +0x018
    bool unknown_19;                // +0x019
    bool unknown_1a;                // +0x01A (set when no second position)
    int unknown_1c;                 // +0x01C
    int unknown_20;                 // +0x020
    UnknownMessageNode *unknown_24;          // +0x024
    short unknown_28;               // +0x028
    char unknown_2a[0x16C - 0x2A];
    short unknown_16c;              // +0x16C
    char unknown_16e[0x2B0 - 0x16E];
    int unknown_2b0;                // +0x2B0
    int unknown_2b4;                // +0x2B4
    short unknown_2b8;              // +0x2B8
    int Selection_First;            // +0x2BC (first of the selection range)
    int Selection_Last;             // +0x2C0
    int TextWidth;                  // +0x2C4 (the width minus 8)
    unsigned short Texts[14][162];  // +0x2C8 the message texts
    union {
        int unknown_1480[7];        // +0x1480 (7 dwords of 0x10001)
        unsigned short Slot_Free[14];   // +0x1480 whether each text slot is free
    };
};

#endif
