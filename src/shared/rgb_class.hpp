// RGBClass: a palette colour (Westwood name; three unsigned bytes, no vtable).
//
// Evidence: VectorClass<RGBClass> (vtable 0x0079DA54) and TypeList<RGBClass>
// (0x0079DA74) in the CCINI unit: ID(T const *) divides by 3, new T[n]
// zeroes all three bytes per element (0x0046D660), assignment copies a word
// and a byte, and operator== (0x0046D720) compares the three bytes in order.
// The member names Red/Green/Blue are Westwood's; their order is a hypothesis.
#ifndef SHARED_RGB_CLASS_HPP
#define SHARED_RGB_CLASS_HPP

class NoInitClass;

class RGBClass {
public:
#ifdef RGB_DECLARE_DEFAULT_CONSTRUCTOR
    RGBClass();
#else
    RGBClass() : Red(0), Green(0), Blue(0) {}
#endif
    RGBClass(RGBClass const &from, RGBClass const &to, float ratio); // 0x0063CC80, original constructor call at60894e
    RGBClass(NoInitClass const &noinit) {}      // load path (ParticleClass::Load)
    RGBClass(unsigned char red, unsigned char green, unsigned char blue) : Red(red), Green(green), Blue(blue) {}

    bool operator==(RGBClass const &that) const
    {
        return Red == that.Red && Green == that.Green && Blue == that.Blue;
    }
    bool operator!=(RGBClass const &that) const
    {
        return !(*this == that);
    }

    // Moves this colour toward target by ratio/256 (0x0063CF20; Westwood's
    // RGBClass::Adjust; accepted as RgbTriplet::BlendRgbTowardTarget_0063cf20).
    void Adjust(int ratio, RGBClass const &target);

    // A second out-of-line Adjust that works blue first (0x004FEF70).
    void unknown_4fef70(int ratio, RGBClass const &target);

    int Difference(RGBClass const &other) const; // 0x0063CFB0 weighted absolute difference

    // Sets the three channels (an out-of-line copy at 0x004F6BC0, after House.cpp).
#ifdef RGB_DECLARE_BRIGHTEN
    // This colour as `color` brightened by `factor` (0x0063CDF0; TibSun RGBClass::Set(color, factor);
    // guarded: this header is in Refresh_Wonline_Players 0x0073FEE0's closure).
    RGBClass &Set(RGBClass const &color, float factor);
#endif
    void Set(unsigned char red, unsigned char green, unsigned char blue)
    {
        Red = red;
        Green = green;
        Blue = blue;
    }

    unsigned char Red;      // +0x00
    unsigned char Green;    // +0x01
    unsigned char Blue;     // +0x02
};

#endif
