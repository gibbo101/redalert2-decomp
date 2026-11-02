// IonBlastClass::~IonBlastClass() (0x005212F0): leaves the list of blasts.
IonBlastClass::~IonBlastClass()
{
    IonBlasts.Delete(this);
}
