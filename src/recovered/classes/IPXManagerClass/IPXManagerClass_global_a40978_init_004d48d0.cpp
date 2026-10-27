// Dynamic initializer of the global IPX connection manager (0x004D48D0;
// registers the destructor thunk 0x004D4910 with atexit).
#include "shared/ipx_manager.hpp"
// @ref ?unknown_ipx_manager_a40978@@3VIPXManagerClass@@A=00a40978
// @ref _atexit=0078298a

IPXManagerClass unknown_ipx_manager_a40978(0x1c7, 0x22e, 0xa0, 0x20, 0x8813, 0xaa03);
