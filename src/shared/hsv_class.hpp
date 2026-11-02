// HSVClass: a hue/saturation/value colour, three bytes like RGBClass (CCINIClass::Get_HSV
// 0x0046A130; the element of DynamicVectorClass<HSVClass>). Names are hypotheses.
//
// The VectorClass<HSVClass> and DynamicVectorClass<HSVClass> members call the comparisons
// out of line: the member operator!= (0x004FF1A0) from VectorClass::operator== and the
// __fastcall equality (0x004FF1E0, a two-byte self jump in the original) from the ID lookups.
#ifndef RA2_SHARED_HSV_CLASS_HPP
#define RA2_SHARED_HSV_CLASS_HPP

class RGBClass;

class HSVClass {
public:
    HSVClass() : Hue(0), Saturation(0), Value(0) {}
    HSVClass(unsigned char hue, unsigned char saturation, unsigned char value)
        : Hue(hue), Saturation(saturation), Value(value) {}
    RGBClass To_RGB() const;                // 0x004FF050 (name hypothesis)
    bool operator!=(HSVClass const &other) const;       // 0x004FF1A0
#ifdef RA2_HSV_UNIT
    // Declared only in the HSV unit 0x004FEF50 (Tiberian Sun's hsv.cpp): a member operator== next to
    // the free one would make every other includer's comparisons ambiguous.
    bool operator==(HSVClass const &other) const;       // 0x004FF170
    // Moves the colour toward hsv by (ratio & 0xFF)/256, value first (0x004FEF70).
    void Adjust(int ratio, HSVClass const &hsv);
    int Difference(HSVClass const &hsv) const;          // 0x004FF000 (squared distance)
    static HSVClass const BlackColor;                   // 0x00A410BC
#endif
    unsigned char Hue;          // +0x00
    unsigned char Saturation;   // +0x01
    unsigned char Value;        // +0x02
};
bool __fastcall operator==(HSVClass const &a, HSVClass const &b);   // 0x004FF1E0

#endif
