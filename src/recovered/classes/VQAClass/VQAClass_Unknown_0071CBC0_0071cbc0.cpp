// int VQAClass::Unknown_0071CBC0(int value) (0x0071CBC0): sets a configuration value (-1 keeps it); returns the old one.
#include "shared/movie.hpp"

int VQAClass::Unknown_0071CBC0(int value)
{
    int old = unknown_1d4;
    if (value != -1) {
        unknown_1d4 = value;
    }
    return old;
}
