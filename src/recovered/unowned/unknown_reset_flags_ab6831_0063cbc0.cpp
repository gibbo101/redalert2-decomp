// void unknown_reset_flags_ab6831() -- 0x0063CBC0
// Purpose: sets the byte at 0x00AB6831 to 0xFF and clears the two
// bytes after it.
// Assumptions: what the three bytes are (a value and two flags) is
// unknown.
// @ref ?unknown_mode_ab6831@@3DA=00ab6831
// @ref ?unknown_flag_ab6832@@3_NA=00ab6832
// @ref ?unknown_flag_ab6833@@3_NA=00ab6833

extern char unknown_mode_ab6831;
extern bool unknown_flag_ab6832;
extern bool unknown_flag_ab6833;

void unknown_reset_flags_ab6831()
{
    unknown_mode_ab6831 = (char)0xFF;
    unknown_flag_ab6832 = false;
    unknown_flag_ab6833 = false;
}
