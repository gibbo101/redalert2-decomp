// int NullModemClass::Change_IRQ_Priority(int irq) (0x005D1E40)
// Nothing to do under Windows.
#include "shared/null_modem.hpp"

int NullModemClass::Change_IRQ_Priority(int irq)
{
    return 0;
}
