// void SuperClass::Compute_CRC(WWCRCEngine &crc) const (0x0069EB20)
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80
// @ref ?Compute_CRC@AbstractClass@@UBEXAAVWWCRCEngine@@@Z=004101b0

void SuperClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractClass::Compute_CRC(crc);
    crc(unknown_0x55);
    crc(unknown_0x56);
    crc(unknown_0x57);
    crc((long)unknown_0x5C);
    crc((long)unknown_0x60);
    crc(unknown_0x48);
    crc(AnimDetached);
    if (Anim != 0) {
        crc((long)Anim->Loops);
        crc(Anim->Fetch_ID());
    }
}
