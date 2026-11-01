// float StorageClass::Get_Total_Amount() const (0x0069AE10): the sum of the slots (kept as a whole number).
float StorageClass::Get_Total_Amount() const
{
    int amount = 0;
    for (int i = 0; i < 4; i++) {
        amount += Amounts[i];
    }
    return amount;
}
