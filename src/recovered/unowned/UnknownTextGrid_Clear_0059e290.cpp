// void UnknownTextGrid_0059e290::unknown_clear() -- 0x0059E290
// Purpose: fills an 80x25 character grid (column-major, +0x0000) with
// spaces and its parallel int grid (+0x07D0) with zero, marks it changed
// (+0x2734) and redraws the whole area (0x0059EA90 with 0, 0, 80, 25).
// The owning class (a text console view) is not identified.
// @ref ?unknown_redraw_59ea90@UnknownTextGrid_0059e290@@QAEXHHHH@Z=0059ea90

struct UnknownTextGrid_0059e290 {
    void unknown_clear_0059e290();
    void unknown_redraw_59ea90(int x, int y, int width, int height);

    char Characters[80][25];             // +0x0000
    int Attributes[80][25];              // +0x07D0
    char unknown_2710[0x2734 - 0x2710];
    bool unknown_changed_2734;           // +0x2734
};

void UnknownTextGrid_0059e290::unknown_clear_0059e290()
{
    for (int y = 0; y < 25; y++) {
        for (int x = 0; x < 80; x++) {
            Characters[x][y] = ' ';
            Attributes[x][y] = 0;
        }
    }
    unknown_changed_2734 = true;
    unknown_redraw_59ea90(0, 0, 80, 25);
}
