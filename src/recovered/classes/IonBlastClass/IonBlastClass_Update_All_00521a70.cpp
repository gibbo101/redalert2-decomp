// IonBlastClass::Update_All() (0x00521A70): one frame of every blast, last
// first (a finished blast deletes itself from the list).
void IonBlastClass::Update_All()
{
    for (int i = IonBlasts.Count() - 1; i >= 0; i--) {
        IonBlasts[i]->AI();
    }
}
