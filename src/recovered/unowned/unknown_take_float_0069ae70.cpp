// float UnknownFloats_0069AE70::unknown_take(float value, int index) -- 0x0069AE70
// Purpose: takes up to value from element `index` of the float array at
// +0x00 (never below what is there) and returns the amount taken.
// Assumptions: owner unidentified (the same array as 0x0069AE50).

struct UnknownFloats_0069ae70 {
    float Values[1];                        // +0x00
    float unknown_take(float value, int index);
};

float UnknownFloats_0069ae70::unknown_take(float value, int index)
{
    float amount = Values[index] < value ? Values[index] : value;
    Values[index] -= amount;
    return amount;
}
