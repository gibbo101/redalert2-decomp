// ProgressBarClass: a filled bar drawn on the logic surface (Westwood's BAR.H;
// RA2 keeps the values as doubles). Not polymorphic; its unit (0x0042B950-
// 0x0042BCCF) has no callers in the executable.
#ifndef RA2_SHARED_PROGRESS_BAR_HPP
#define RA2_SHARED_PROGRESS_BAR_HPP

class ProgressBarClass {
public:
    ProgressBarClass(int x, int y, int width, int height, int forecolor, int backcolor,
                     int bordercolor = 0);                  // 0x0042B970
    bool Update(double value);                              // 0x0042B9D0
    void Redraw() const;                                    // 0x0042BA80

private:
    void Outline() const;                                   // 0x0042BA10
    bool Is_Horizontal() const;                             // 0x0042B9C0
    bool Is_Outlined() const { return BorderColor != 0; }

    int X;                      // +0x00
    int Y;                      // +0x04
    int Width;                  // +0x08
    int Height;                 // +0x0C
    int BarColor;               // +0x10
    int BackColor;              // +0x14
    int BorderColor;            // +0x18
    int unknown_1c;             // +0x1C (never written)
    double CurrentValue;        // +0x20
    double LastDisplayCurrent;  // +0x28
    bool IsDrawn;               // +0x30
};

#endif
