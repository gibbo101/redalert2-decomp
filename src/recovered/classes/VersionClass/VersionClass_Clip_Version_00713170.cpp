// Narrows the clipping range to a peer's range: -1 when the peer is newer than the range,
// 0 when it is older, else the clipped maximum (0x00713170).
int VersionClass::Clip_Version_00713170(unsigned long min, unsigned long max)
{
    if (min > MaxClipVer) {
        return 0xFFFFFFFF;
    }
    if (max < MinClipVer) {
        return 0;
    }
    if (min > MinClipVer) {
        MinClipVer = min;
    }
    if (max < MaxClipVer) {
        MaxClipVer = max;
    }
    return MaxClipVer;
}
