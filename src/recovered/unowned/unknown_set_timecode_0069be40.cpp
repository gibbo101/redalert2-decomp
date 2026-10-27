// void __fastcall unknown_set_timecode(unsigned short const *text, UnknownTimed_0069be40 *target) -- 0x0069BE40
// Purpose: stores the time parsed from a "H:M:S:F" string
// (unknown_parse_timecode, 0x0069BD60) in target +0x04 unless it is 0.
// Assumptions: owner of +0x04 unidentified.
// @ref ?unknown_parse_timecode@@YIIPBG@Z=0069bd60

unsigned __fastcall unknown_parse_timecode(unsigned short const *text);

struct UnknownTimed_0069be40 {
    int unknown_00;
    unsigned Time;                          // +0x04
};

void __fastcall unknown_set_timecode(unsigned short const *text, UnknownTimed_0069be40 *target)
{
    unsigned time = unknown_parse_timecode(text);
    if (time > 0) {
        target->Time = time;
    }
}
