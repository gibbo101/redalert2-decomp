// BlowfishEngine::~BlowfishEngine() (0x004355F0)
// Releases the COM interface.
#include "shared/blowfish_engine.hpp"

BlowfishEngine::~BlowfishEngine()
{
    if (Interface != 0) {
        Interface->Release();
    }
}
