float __fastcall Fast_Atan_Float_004bac50(float value)
{
    float number = (float)value;
    int index = abs((int)(number / unknown_atan_step_817df8));
    float result;
    if (index < 0x1001) {
        result = unknown_atan_table_813df4[index];
    } else {
        result = 1.5707964f;
    }
    if (number < 0.0f) {
        result = -result;
    }
    return result;
}
