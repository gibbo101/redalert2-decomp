// int VQAClass::Unknown_0071CBC0(int value) (0x0071CBC0): sets the configuration volume (-1 keeps it); returns the old one.
#include "shared/movie.hpp"

int VQAClass::Unknown_0071CBC0(int value)
{
    int old = Config.Volume;
    if (value != -1) {
        Config.Volume = value;
    }
    return old;
}
