// void __fastcall Set_Text_Option_006f9fe0(int value) -- 0x006F9FE0
// Purpose: when the text option at 0x007F8CE8 differs from value, frees the text
// tables (0x006F9D90), stores value and has the object at 0x00AD0434 run 0x006F8E30.
// Parse_Command_Line sets it from -str (1) and -nostr (0) with the value in ecx.
// Assumptions: the option's meaning and the observer class are unidentified.
// @ref ?unknown_text_option_7f8ce8@@3HA=007f8ce8
// @ref ?Unknown_006F9D90@@YAXXZ=006f9d90
// @ref ?unknown_6f8e30@UnknownObserver_006f9fe0@@QAEXXZ=006f8e30
// @ref ?unknown_observer_ad0434@@3PAUUnknownObserver_006f9fe0@@A=00ad0434

struct UnknownObserver_006f9fe0 {
    void unknown_6f8e30();                  // 0x006F8E30
};
extern UnknownObserver_006f9fe0 *unknown_observer_ad0434;

extern int unknown_text_option_7f8ce8;       // 0x007F8CE8
void Unknown_006F9D90();                    // 0x006F9D90 frees the text tables

void __fastcall Set_Text_Option_006f9fe0(int value)
{
    if (unknown_text_option_7f8ce8 != value) {
        Unknown_006F9D90();
        unknown_text_option_7f8ce8 = value;
        unknown_observer_ad0434->unknown_6f8e30();
    }
}
