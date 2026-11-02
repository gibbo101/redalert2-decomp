// IonBlastClass::Clear_All() (0x00521CB0): frees the shockwave surfaces.
void IonBlastClass::Clear_All()
{
    for (int i = 0; i < 80; i++) {
        delete BlastSurfaces[i];
        BlastSurfaces[i] = 0;
    }
}
