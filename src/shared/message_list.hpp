// MessageListClass (Westwood's on-screen message list; "MessageListClass::Init(Width: %d)" debug text
// at 0x005B4C60). Only the members the recovered functions use are named; the class has no vtable.
// Constructor 0x005B4BD0, Init 0x005B4C60.
#ifndef RA2_SHARED_MESSAGE_LIST_HPP
#define RA2_SHARED_MESSAGE_LIST_HPP

#include "shared/debug_printf.hpp"

// A message node (a MessageNode_006f15c0 of shared/message_gadget_layout.hpp; the list is linked through the
// LinkClass-style slots: slot 1 is the next node, slot 4 appends to a list, slot 9 removes the node and returns the next one;
// slots 11 and 20-27 are GadgetClass's: Draw_All, Set_Focus, Clear_Focus, Has_Focus, Draw_Me).
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
    virtual void unknown_slot10();
    virtual void Draw_All(bool forced);                         // slot 11 (GadgetClass)
    virtual void unknown_slot12();
    virtual void unknown_slot13();
    virtual void unknown_slot14();
    virtual void unknown_slot15();
    virtual void unknown_slot16();
    virtual void unknown_slot17();
    virtual void unknown_slot18();
    virtual void unknown_slot19();
    virtual void Set_Focus();                                   // slot 20 (GadgetClass)
    virtual void Clear_Focus();                                 // slot 21
    virtual bool Has_Focus();                                   // slot 22
    virtual void unknown_slot23();
    virtual void unknown_slot24();
    virtual void unknown_slot25();
    virtual void unknown_slot26();
    virtual int Draw_Me(int forced);                            // slot 27

    char unknown_04[0x0C - 0x04];
    int X;                                                      // +0x0C
    int Y;                                                      // +0x10
    char unknown_14[0x24 - 0x14];
    int Expires;                                                // +0x24 the SystemTimerClass time it goes away (0: never)
    int Identifier;                                             // +0x28
    unsigned Style;                                             // +0x2C the text print flags
    unsigned short *Text;                                       // +0x30 one of the list's text slots
    int Color;                                                  // +0x34 the ColorSchemes index
    int MaximumWidth;                                           // +0x38
    char unknown_3c[0x40 - 0x3C];
    bool unknown_40;                                            // +0x40 (set on the beacon text edit line)
    bool unknown_41;                                            // +0x41                                            // +0x41
};

// An empty function the edit removal calls (0x00738100).
void Unknown_00738100();

extern bool unknown_flag_a3f208;         // 0x00A3F208 (game mode 3: new messages are marked)
extern bool unknown_flag_a3f209;         // 0x00A3F209 (game mode 4)

class MessageListClass {
public:
    MessageListClass();                                                             // 0x005B4BD0
    ~MessageListClass() { Reset(); }                                               // expands 0x005B4C40
    // Init with the default width of 640 (0x005B4C40).
    void Reset();
    // Resets the list and its geometry: position, maximum messages (at most 14) and characters (at most 112),
    // an optional second position (-1: the same), and the selection range; width is the pixel width.
    // Adds a message (an optional "prefix: " and the text, wrapped to the width; the rest goes in further messages).
    // The text of the message with the identifier, or none (0x005B5160).
    unsigned short *Get_Message(int identifier);
    // The message with the identifier, or none (0x005B5190).
    UnknownMessageNode *Get_Label(int identifier);
    // Gives the edit line the focus when one is open (0x005B53E0).
    void Set_Edit_Focus();
    // Opens the edit line with the text (none: empty) and the cursor character; with AdjustEdit it takes the last
    // row of the list (dropping the oldest message when the list is full). A width of 0 or less is TextWidth (0x005B5410).
    UnknownMessageNode *Add_Edit(int color, unsigned style, unsigned short const *text, char cursor, int width);
    // Closes the edit line and gives its row back to the list (0x005B5580).
    void Remove_Edit();
    // Puts the messages one under the other from the top of the list, below the edit line when it is open
    // (an inline helper with no out-of-line copy; name hypothesis; Add_Edit, Remove_Edit).
    void Restack_Messages()
    {
        int y;
        if (IsEdit) {
            y = Height + Y;
        } else {
            y = Y;
        }
        UnknownMessageNode *node = First;
        while (node != 0) {
            node->Y = y;
            node = node->Next();
            y += Height;
        }
    }
    // Edit-line keyboard and mouse input: input is the key number (cleared when used), key the character
    // when the caller has it (0: from the keyboard). 0: not used, 1: a character went in, 2: changed or closed,
    // 3: sent (Return), 4: a character went in and the start of the line went to OverflowBuf (0x005B56F0).
    int Input(int &input, unsigned short key);
    // The number of messages, with the edit line when it is a row of the list (0x005B5C30).
    int Num_Messages();
    // Sets the pixel width of the list (TextWidth is 8 less) and of every message and the edit line (0x005B5C60).
    void Set_Width(int width);
    // Cuts the first characters off src into dest (when given): at least min_chars and at most max_chars, at a
    // space looked for forward from min_chars or backward from max_chars; src keeps the rest. The count (0x005B5CB0).
    int Trim_Message(unsigned short *dest, unsigned short *src, int min_chars, int max_chars, int scan_start);
    // Draws the edit line (with its cursor while it has the focus and there is room) and the messages (0x005B5B30).
    void Draw();
    // Appends the text to the message with the identifier and prefix when it is still shown and has room
    // (0x005B51C0; Red Alert's Concat_Message; 0: not added).
    int Concat_Message(unsigned short const *prefix, int identifier, unsigned short const *text, int delay);
    UnknownMessageNode *Add_Message(unsigned short const *prefix, int identifier, unsigned short const *text, int color,
        unsigned style, int delay, bool unknown_flag);                              // 0x005B4DA0
    // Removes the messages that have expired, frees their text slots and restacks the rest (0x005B5610); whether any went.
    int Update_Messages();
#ifdef MESSAGE_LIST_DECLARE_EDIT_BUF
    // The edit text after the 'to' prefix (EditBuf + EditInitPos; 0x005B55E0; Westwood's Get_Edit_Buf).
    // Behind a guard (shared/main_loop.hpp defines it): a new member here renumbers
    // Refresh_Wonline_Players 0x0073FEE0's $L labels.
    unsigned short *Get_Edit_Buf();
#endif
    void Init(int x, int y, int max_messages, int max_chars, int unknown_arg5, int x2, int y2,
        bool unknown_flag, int first, int last, int width);                         // 0x005B4C60

    UnknownMessageNode *First;               // +0x000 the message nodes
    int X;                          // +0x004
    int Y;                          // +0x008
    int MaxMessages;                // +0x00C
    int MaxChars;                   // +0x010
    int Height;                     // +0x014 (19)
    bool unknown_18;                // +0x018
    bool IsEdit;                    // +0x019 an edit line is open (EditLabel)
    bool AdjustEdit;                // +0x01A (set when no second position: the edit line is the last row of the list)
    int EditX;                      // +0x01C the edit line's position
    int EditY;                      // +0x020
    UnknownMessageNode *EditLabel;  // +0x024 the edit line
    unsigned short EditBuf[162];    // +0x028 the edit text
    unsigned short OverflowBuf[162];  // +0x16C
    int EditCurPos;                 // +0x2B0 (the text length when the edit opens)
    int EditInitPos;                // +0x2B4
    unsigned short EditCursor;      // +0x2B8 the cursor character
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
