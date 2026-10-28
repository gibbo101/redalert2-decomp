// bool ShapeButtonClass::Unknown_00675300() (0x00675300)
// Stops the span; true if one was running.

bool ShapeButtonClass::Unknown_00675300()
{
    if (unknown_38) {
        unknown_34 = false;
        unknown_3c = 0;
        unknown_38 = 0;
        return true;
    }
    return false;
}
