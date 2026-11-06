// Original006983E0: destructor of the WinMain registration-loop IUnknownPtr local.
#include "shared/iunknown_ptr.hpp"
IUnknownPtr::~IUnknownPtr() { _Release(); }
