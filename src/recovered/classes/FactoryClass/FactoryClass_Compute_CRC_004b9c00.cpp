#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/factory_class.hpp"
#include "shared/house.hpp"
#include "shared/debug_printf.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ?Compute_CRC@AbstractClass@@UBEXAAVWWCRCEngine@@@Z=004101b0
// @ref ?Frame@@3HA=00a40d2c
extern "C" char const factory_message_007d7f64[];
// @ref _factory_message_007d7f64=007d7f64
extern "C" char const factory_message_007d7f70[];
// @ref _factory_message_007d7f70=007d7f70
extern "C" char const factory_message_007d7f88[];
// @ref _factory_message_007d7f88=007d7f88
extern "C" char const factory_message_007d7f9c[];
// @ref _factory_message_007d7f9c=007d7f9c
extern "C" char const factory_message_007d7fb4[];
// @ref _factory_message_007d7fb4=007d7fb4
extern "C" char const factory_message_007d7fc4[];
// @ref _factory_message_007d7fc4=007d7fc4
extern "C" char const factory_message_007d7fd8[];
// @ref _factory_message_007d7fd8=007d7fd8
extern "C" char const factory_message_007d7fec[];
// @ref _factory_message_007d7fec=007d7fec
extern "C" char const factory_message_007d8004[];
// @ref _factory_message_007d8004=007d8004
extern "C" char const factory_message_007d8018[];
// @ref _factory_message_007d8018=007d8018
extern "C" char const factory_message_007d8038[];
// @ref _factory_message_007d8038=007d8038
void FactoryClass::Compute_CRC(WWCRCEngine &crc) const
{
    Debug_Printf(factory_message_007d8038, Frame);
    Debug_Printf(factory_message_007d8018, Queue.Count());
    Debug_Printf(factory_message_007d8004, Object->Kind_Of());
    Debug_Printf(factory_message_007d7fec, Object->unknown_slot16());
    Debug_Printf(factory_message_007d7fd8, unknown_6c);
    Debug_Printf(factory_message_007d7fc4, unknown_59);
    Debug_Printf(factory_message_007d7fb4, UnspentCost);
    Debug_Printf(factory_message_007d7f9c, unknown_60);
    Debug_Printf(factory_message_007d7f88, unknown_64);
    Debug_Printf(factory_message_007d7f70, Owner->Fetch_ID());
    Debug_Printf(factory_message_007d7f64, const_cast<FactoryClass *>(this)->Fetch_ID());
    AbstractClass::Compute_CRC(crc);
    crc(unknown_6c);
    crc(unknown_59);
    crc((long)UnspentCost);
    crc((long)unknown_60);
    if (Object) crc(Object->Fetch_ID());
    crc((long)unknown_64);
    crc(Owner->Fetch_ID());
}
