// unsigned int Unknown_0073cfd0() (0x0073CFD0)
// The exclusive or of three words (0x00B2AC18, 0x00B2AC20, 0x00B2AC1C).
#include "shared/wol_sink.hpp"
// @ref ?unknown_b2ac18@@3IA=00b2ac18
// @ref ?unknown_b2ac1c@@3IA=00b2ac1c
// @ref ?unknown_b2ac20@@3IA=00b2ac20

unsigned int Unknown_0073cfd0()
{
    return unknown_b2ac18 ^ unknown_b2ac20 ^ unknown_b2ac1c;
}
