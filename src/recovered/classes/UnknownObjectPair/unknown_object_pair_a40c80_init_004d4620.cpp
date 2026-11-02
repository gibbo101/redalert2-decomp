// Dynamic initializer of a global UnknownObjectPair (0x004D4620, _$E): the inline
// constructor clears both pointers, then the atexit destructor (0x004D4640, the following
// _$E draft, emitted by this definition) runs ~UnknownObjectPair 0x005D4A60. Owning unit:
// the global-object block around 0x004D4500.
#include "shared/object_type.hpp"
// @ref ??1UnknownObjectPair@@QAE@XZ=005d4a60
// @ref ?unknown_object_pair_a40c80@@3VUnknownObjectPair@@A=00a40c80
// @ref _atexit=0078298a

UnknownObjectPair unknown_object_pair_a40c80;
