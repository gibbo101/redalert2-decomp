// void unknown_restart_timer() -- 0x0069A160
// Purpose: clears the flag at 0x00ABD52C and stores the time source
// 0x00ABD4C4's current value (0x0069A430) less the base at 0x00ABD4C0 in
// 0x00ABD4E0.
// Assumptions: the globals belong to one unidentified timing object; the
// names are hypotheses.
// @ref ?Value@UnknownTimeSource_0069a160@@QAEHXZ=0069a430
// @ref ?unknown_time_source_abd4c4@@3UUnknownTimeSource_0069a160@@A=00abd4c4
// @ref ?unknown_base_abd4c0@@3HA=00abd4c0
// @ref ?unknown_elapsed_abd4e0@@3HA=00abd4e0
// @ref ?unknown_flag_abd52c@@3_NA=00abd52c

struct UnknownTimeSource_0069a160 {
    int Value();                            // 0x0069A430
};
extern UnknownTimeSource_0069a160 unknown_time_source_abd4c4;
extern int unknown_base_abd4c0;
extern int unknown_elapsed_abd4e0;
extern bool unknown_flag_abd52c;

void unknown_restart_timer()
{
    int now = unknown_time_source_abd4c4.Value();
    unknown_flag_abd52c = false;
    unknown_elapsed_abd4e0 = now - unknown_base_abd4c0;
}
