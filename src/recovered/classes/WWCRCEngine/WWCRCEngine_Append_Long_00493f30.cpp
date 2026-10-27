#include "shared/wwcrc_engine.hpp"
// @ref ??RWWCRCEngine@@QAEJPBXH@Z=00493fc0
void WWCRCEngine::operator()(long datum) { long value = datum; (*this)(&value, sizeof(value)); }
