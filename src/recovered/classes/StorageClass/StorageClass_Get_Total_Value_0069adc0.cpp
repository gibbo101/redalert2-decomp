// int StorageClass::Get_Total_Value() const (0x0069ADC0): every slot's amount times its tiberium's value.
// @ref __real@4@00000000000000000000=0079a738
// @ref __ftol=0077f110
// @ref ?unknown_TiberiumClass_list_00ac0b30@@3V?$DynamicVectorClass@PAVTiberiumClass@@@@A=00ac0b30
int StorageClass::Get_Total_Value() const
{
    int value = 0;
    for (int i = 0; i < 4; i++) {
        if (Amounts[i] > 0) {
            value += Amounts[i] * unknown_TiberiumClass_list_00ac0b30[i]->Value;
        }
    }
    return value;
}
