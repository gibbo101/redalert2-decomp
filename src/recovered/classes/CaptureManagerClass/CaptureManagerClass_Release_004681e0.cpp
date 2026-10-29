// void CaptureManagerClass::Release_4681e0() (0x004681E0)
// Returns the held object to the house it came from (slot 222) and forgets
// both; Capture 0x00467FF0 starts with the same steps.

void CaptureManagerClass::Release_4681e0()
{
    if (unknown_24 != 0) {
        unknown_24->unknown_234 = 0;
        unknown_24->unknown_slot222(unknown_28, true);
        unknown_24 = 0;
        unknown_28 = 0;
    }
}
