// NullModemConnClass::~NullModemConnClass() (0x005CDB90)
// Frees the send buffer (the base destructor follows).
#include "shared/null_modem.hpp"

NullModemConnClass::~NullModemConnClass()
{
    delete SendBuf;
}
