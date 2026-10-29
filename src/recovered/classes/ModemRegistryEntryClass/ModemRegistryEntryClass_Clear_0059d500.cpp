// ModemRegistryEntryClass::Clear_0059d500 (0x0059D500)
#include "shared/null_modem.hpp"

void ModemRegistryEntryClass::Clear_0059d500()
{
    if (ModemName) {
        delete[] ModemName;
        ModemName = 0;
    }
    if (ModemDeviceName) {
        delete[] ModemDeviceName;
        ModemDeviceName = 0;
    }
    if (ErrorCorrectionEnable) {
        delete[] ErrorCorrectionEnable;
        ErrorCorrectionEnable = 0;
    }
    if (ErrorCorrectionDisable) {
        delete[] ErrorCorrectionDisable;
        ErrorCorrectionDisable = 0;
    }
    if (CompressionEnable) {
        delete[] CompressionEnable;
        CompressionEnable = 0;
    }
    if (CompressionDisable) {
        delete[] CompressionDisable;
        CompressionDisable = 0;
    }
    if (HardwareFlowControl) {
        delete[] HardwareFlowControl;
        HardwareFlowControl = 0;
    }
}
