// bool ShapeButtonClass::Unknown_006752D0(int start, int length, bool flag) (0x006752D0)
// Starts the +0x38/+0x3C span unless one is running.

bool ShapeButtonClass::Unknown_006752D0(int start, int length, bool flag)
{
    if (!unknown_38) {
        unknown_38 = start;
        unknown_3c = start + length;
        unknown_34 = flag;
        return true;
    }
    return false;
}
