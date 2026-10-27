float __cdecl Fast_Asin(double value)
{
    float number = (float)value;
    int index = (int)((number + 1.0f) * -2048.0f);
    return (float)(1.5707963267948966 - unknown_acos_table_80bdd4[-index]);
}
