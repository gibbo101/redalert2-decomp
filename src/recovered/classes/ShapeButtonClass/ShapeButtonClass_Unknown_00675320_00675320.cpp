// bool ShapeButtonClass::Unknown_00675320() (0x00675320)
// A disabled button stops the span; otherwise the countdown at +0x3C runs
// and, when it ends, flips +0x34 and restarts from +0x38. True when the
// button needs a redraw.

bool ShapeButtonClass::Unknown_00675320()
{
    if (IsDisabled) {
        return Unknown_00675300();
    }
    if (unknown_3c) {
        unknown_3c--;
        if (!unknown_3c) {
            unknown_34 = !unknown_34;
            unknown_3c = unknown_38;
            return true;
        }
    }
    return false;
}
