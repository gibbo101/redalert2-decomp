// The colour scheme of each player colour (0x007F3224, 9 entries).
extern char const unknown_color_schemes_7f3224[9];
// @ref ?unknown_color_schemes_7f3224@@3QBDB=007f3224

int UnknownSessionState::Unknown_006715D0(int color)
{
    if (color == -2) {
        color = 8;
    }
    if ((unsigned)color < 9) {
        return unknown_color_schemes_7f3224[color];
    }
    return color;
}
