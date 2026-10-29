// bool CaptureManagerClass::Detach_Target_468120(AbstractClass *target) (0x00468120)
// TechnoClass::Detach's notice: when the held object goes away, forget it and
// the house it came from. Always true.

bool CaptureManagerClass::Detach_Target_468120(AbstractClass *target)
{
    if (unknown_24 == target) {
        unknown_24 = 0;
        unknown_28 = 0;
    }
    return true;
}
