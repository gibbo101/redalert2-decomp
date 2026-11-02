// MessageListClass (Westwood's on-screen message list; "MessageListClass::Init(Width: %d)" debug text
// at 0x005B4C60). Only the members the recovered functions use are named; the class has no vtable.
// Constructor 0x005B4BD0, Init 0x005B4C60.
#ifndef RA2_SHARED_MESSAGE_LIST_HPP
#define RA2_SHARED_MESSAGE_LIST_HPP

#include "shared/debug_printf.hpp"

// The message nodes (shared/text_label.hpp; Restack_Messages below needs the complete class).
class TextLabelClass;

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
    TextLabelClass *Get_Label(int identifier);
    // Gives the edit line the focus when one is open (0x005B53E0).
    void Set_Edit_Focus();
#ifdef RA2_MESSAGE_LIST_UNIT
    // Whether the open edit line has the focus (0x005B53F0, unreferenced; Westwood's Has_Edit_Focus; declared for
    // MsgList.cpp only: message_list.hpp is in Refresh_Wonline_Players 0x0073FEE0's closure).
    bool Has_Edit_Focus();
#endif
    // Opens the edit line with the text (none: empty) and the cursor character; with AdjustEdit it takes the last
    // row of the list (dropping the oldest message when the list is full). A width of 0 or less is TextWidth (0x005B5410).
    TextLabelClass *Add_Edit(int color, unsigned style, unsigned short const *text, char cursor, int width);
    // Closes the edit line and gives its row back to the list (0x005B5580).
    void Remove_Edit();
    // Puts the messages one under the other from the top of the list, below the edit line when it is open
    // (an inline helper with no out-of-line copy; name hypothesis; Add_Edit, Remove_Edit).
    void Restack_Messages();
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
    TextLabelClass *Add_Message(unsigned short const *prefix, int identifier, unsigned short const *text, int color,
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

    TextLabelClass *First;               // +0x000 the message nodes
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
    TextLabelClass *EditLabel;  // +0x024 the edit line
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

// Defined once shared/text_label.hpp is in (the sources that restack include it first).
#if defined(RA2_SHARED_TEXT_LABEL_HPP) && !defined(RA2_SHARED_MESSAGE_LIST_RESTACK)
#define RA2_SHARED_MESSAGE_LIST_RESTACK
inline void MessageListClass::Restack_Messages()
{
    int y;
    if (IsEdit) {
        y = Height + Y;
    } else {
        y = Y;
    }
    TextLabelClass *node = First;
    while (node != 0) {
        node->Y = y;
        node = (TextLabelClass *)node->Get_Next();
        y += Height;
    }
}
#endif
