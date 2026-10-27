// void ThemeClass::unknown_6e8180() -- 0x006E8180
// Purpose: when a sample is attached (+0x2C), runs 0x00407FE0 on it; then
// sets the flag at +0x11.
// Assumptions: layout as in ThemeClass::Suspend (0x006E8270); what
// 0x00407FE0 does to the sample (a fade?) and the flag's meaning are
// unknown.
// @ref ?unknown_sample_407fe0@@YIXPAX@Z=00407fe0

void __fastcall unknown_sample_407fe0(void *sample);    // 0x00407FE0

class ThemeClass {
public:
    void unknown_6e8180();

    int Current;                    // +0x00
    int Playing;                    // +0x04
    int Suspended;                  // +0x08
    char unknown_0c[0x11 - 0x0C];
    bool unknown_11;                // +0x11
    char unknown_12[0x2C - 0x12];
    void *Sample;                   // +0x2C
};

void ThemeClass::unknown_6e8180()
{
    if (Sample != 0) {
        unknown_sample_407fe0(Sample);
    }
    unknown_11 = true;
}
