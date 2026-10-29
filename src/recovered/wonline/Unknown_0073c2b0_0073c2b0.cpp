// void Unknown_0073c2b0() (0x0073C2B0)
// Opens the Westwood Online registration page for language code unknown_b2ac5c.
#include "shared/wol_sink.hpp"
// @ref ?unknown_open_url_73c580@@YIXPBDH@Z=0073c580
// @ref ?unknown_b2ac5c@@3HA=00b2ac5c
// @ref _sprintf=007820f4

void Unknown_0073c2b0()
{
    char url[256];
    sprintf(url, "http://games2.westwood.com/cgi-bin/cgiclient?register&request=reg_menu&LANGCODE=%d", unknown_b2ac5c);
    unknown_open_url_73c580(url, 0);
}
// @ref ??_C@_0FD@PLDA@http?3?1?1games2?4westwood?4com?1cgi?9b@=007fd5a4
