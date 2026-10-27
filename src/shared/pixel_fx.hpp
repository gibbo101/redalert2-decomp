// PixelFXClass (RTTI name; vtable 0x007A817C, code 0x0060EB20-0x0060ED3D):
// a small glinting pixel effect. Each instance picks a colour pair from a
// type table (two entries, 0x007EB940: a blue-white and a gold pair, which
// suggests the ore/gem sparkles), a random screen offset, a random blend
// rate and a random lifetime, then ping-pongs its current colour between the
// two colours. Field meanings beyond the arithmetic are hypotheses.
#ifndef RA2_SHARED_PIXEL_FX_HPP
#define RA2_SHARED_PIXEL_FX_HPP

struct PixelFXColor {
    int Red;    // +0x0
    int Green;  // +0x4
    int Blue;   // +0x8
};

// One row of the 0x28-byte type table at 0x007EB940.
struct PixelFXTypeStruct {
    PixelFXColor Bright;     // +0x00 blend target at full phase
    PixelFXColor Dark;       // +0x0C starting colour
    int JitterBits;          // +0x18 bits of random darkening per channel of Bright
    int LifeMask;            // +0x1C mask applied to rand() for the lifetime
    unsigned MaxRate;        // +0x20 blend rate range (inclusive)
    unsigned MinRate;        // +0x24
};

extern PixelFXTypeStruct PixelFXTypes[];   // 0x007EB940

class PixelFXClass {
public:
    PixelFXClass();                       // 0x0060EBF0
    PixelFXClass(int type);               // 0x0060EC10
    virtual ~PixelFXClass();              // 0x0060ED10 (??_G 0x0060ED20)

    void Init(int type);                  // 0x0060EB20
    void Update(int frames);              // 0x0060EC30
    bool Reduce_Life(int frames);         // 0x0060ECC0
    void Set_Offset(int x, int y);        // 0x0060ECF0

    // +0x00 vtable
    PixelFXColor Current;  // +0x04 colour this frame
    int Phase;             // +0x10 0..0x2000; 0x1000 is the Bright peak
    int Rate;              // +0x14 phase step per frame
    PixelFXColor Bright;   // +0x18
    PixelFXColor Dark;     // +0x24
    int XOffset;           // +0x30 -31..32
    int YOffset;           // +0x34 -15..16
    int Life;              // +0x38 frames left
};

#endif
