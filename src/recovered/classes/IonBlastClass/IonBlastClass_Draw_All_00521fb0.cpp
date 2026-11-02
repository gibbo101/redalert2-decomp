// IonBlastClass::Draw_All() (0x00521FB0): rebuilds the offset table when the
// drawing surface's stride changed, then draws every blast's shockwave.
void IonBlastClass::Draw_All()
{
    if (unknown_surface_83995c->Stride() != BlastSurfaceStride) {
        Calculate_Index_To_Surface_LUT(unknown_surface_83995c->Stride());
    }
    for (int i = IonBlasts.Count() - 1; i >= 0; i--) {
        IonBlasts[i]->Draw_It();
    }
}
