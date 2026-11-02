// True with any of the shift, ctrl or alt key bits (0x100, 0x200, 0x400) (0x0051B9B0; VC6 folds the
// three tests into one `test ah, 7`, giving the original's branch with a full-register 1).
bool PlanningModeCommandClass::unknown_slot5(int key) const
{
    return (key & 0x100) || (key & 0x200) || (key & 0x400);
}
