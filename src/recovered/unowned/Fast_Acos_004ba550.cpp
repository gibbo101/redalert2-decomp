float __cdecl Fast_Acos(double value)
{
    float number = (float)value;
    int index = (int)((number + 1.0f) * -2048.0f);
    return unknown_acos_table_80bdd4[-index];
}
