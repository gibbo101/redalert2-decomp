float __fastcall Fast_Atan2_Float_004baba0(float y,float x)
{
    float fx = (float)x;
    float fy = (float)y;
    if (fx == 0.0f) {
        if (fy == 0.0f) {
            return 0.0f;
        }
        if (fy > 0.0f) {
            return 1.5707964f;
        }
        return -1.5707964f;
    }
    int index = abs((int)(fy / fx / unknown_atan_step_817df8));
    float result;
    if (index < 0x1001) {
        result = unknown_atan_table_813df4[index];
    } else {
        result = 1.5707964f;
    }
    if (fx < 0.0f) {
        result = (float)(3.141592653589793 - result);
    }
    if (fy < 0.0f) {
        result = -result;
    }
    return result;
}
