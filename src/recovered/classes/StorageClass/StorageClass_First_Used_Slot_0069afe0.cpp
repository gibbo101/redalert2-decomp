// int StorageClass::First_Used_Slot() const (0x0069AFE0): the first slot holding anything, or -1.
int StorageClass::First_Used_Slot() const
{
    for (int i = 0; i < 4; i++) {
        if (Amounts[i] > 0) {
            return i;
        }
    }
    return -1;
}
