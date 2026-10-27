// UnknownFloat4_0069aea0 UnknownFloat4_0069aea0::operator+(UnknownFloat4_0069aea0 const &other) const -- 0x0069AEA0
// Purpose: the element-wise sum of two sets of four floats.
// Assumptions: the class (four floats) is unidentified; its zeroing
// constructor clears the words as integers (one xor register), so the
// clear loop is written that way.

struct UnknownFloat4_0069aea0 {
    float Values[4];
    UnknownFloat4_0069aea0 operator+(UnknownFloat4_0069aea0 const &other) const;
};

UnknownFloat4_0069aea0 UnknownFloat4_0069aea0::operator+(UnknownFloat4_0069aea0 const &other) const
{
    UnknownFloat4_0069aea0 result;
    int index;
    for (index = 0; index < 4; index++) {
        *(int *)&result.Values[index] = 0;
    }
    for (index = 0; index < 4; index++) {
        result.Values[index] = other.Values[index] + Values[index];
    }
    return result;
}
