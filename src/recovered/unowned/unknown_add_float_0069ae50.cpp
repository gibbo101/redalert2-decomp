// float UnknownFloats_0069AE50::unknown_add(float value, int index) -- 0x0069AE50
// Purpose: adds value to element `index` of the float array at +0x00 and
// returns the new element.
// Assumptions: owner unidentified.

struct UnknownFloats_0069ae50 {
    float Values[1];                        // +0x00
    float unknown_add(float value, int index);
};

float UnknownFloats_0069ae50::unknown_add(float value, int index)
{
    return Values[index] += value;
}
