// Dynamic initializer of the global serial_manager_00a40a28 (0x004D4890, _$E):
// constructs the null-modem manager (16 send and 16 receive entries of 0xEC
// bytes, magic number 0x1234; 0x005CFFC0) and registers its atexit destructor
// (0x004D48C0, the following _$E draft, emitted by this definition; it calls
// ~NullModemClass 0x005D0050).
#include "shared/null_modem.hpp"
// @ref ??0NullModemClass@@QAE@HHHG@Z=005cffc0
// @ref ??1NullModemClass@@UAE@XZ=005d0050
// @ref ?serial_manager_00a40a28@@3VNullModemClass@@A=00a40a28
// @ref _atexit=0078298a
// @ref _$E3=004d48c0

NullModemClass serial_manager_00a40a28(16, 16, 0xEC, 0x1234);
