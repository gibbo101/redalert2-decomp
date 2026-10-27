#include "shared/wwcrc_engine.hpp"
// @ref ??RWWCRCEngine@@QAEJPBXH@Z=00493fc0
void WWCRCEngine::operator()(short datum) { short value[1]; value[0] = datum; (*this)(value, sizeof(value)); }
