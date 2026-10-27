// void unknown_reset_flags_ac109c() -- 0x006F1A20
// Purpose: sets the byte at 0x00AC109C to 'H' (0x48) and clears the two
// bytes after it.
// Assumptions: what the three bytes are (a mode letter and two flags) is
// unknown.
// @ref ?unknown_mode_ac109c@@3DA=00ac109c
// @ref ?unknown_flag_ac109d@@3_NA=00ac109d
// @ref ?unknown_flag_ac109e@@3_NA=00ac109e

extern char unknown_mode_ac109c;
extern bool unknown_flag_ac109d;
extern bool unknown_flag_ac109e;

void unknown_reset_flags_ac109c()
{
    unknown_mode_ac109c = 'H';
    unknown_flag_ac109d = false;
    unknown_flag_ac109e = false;
}
