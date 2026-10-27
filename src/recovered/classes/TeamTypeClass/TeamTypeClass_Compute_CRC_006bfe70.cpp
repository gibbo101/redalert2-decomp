// void TeamTypeClass::Compute_CRC(WWCRCEngine &crc) const (0x006BFE70)
#include "shared/team_type.hpp"
// @ref ?Compute_CRC@AbstractTypeClass@@UBEXAAVWWCRCEngine@@@Z=00410960
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80

void TeamTypeClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractTypeClass::Compute_CRC(crc);
    crc((long)Group);
    crc(Recruiter);
    crc(Autocreate);
    crc(Prebuild);
    crc(Reinforce);
    crc(Whiner);
    crc(Aggressive);
    crc(LooseRecruit);
    crc(Suicide);
    crc(Droppod);
    crc(UseTransportOrigin);
    crc((long)Priority);
    crc((long)Max);
    crc((long)unknown_bc);
    if (Owner != 0) {
        crc((long)((AbstractClass *)Owner)->Kind_Of());
    }
    if (Owner != 0) {
        crc(((AbstractClass *)Owner)->Fetch_ID());
    }
    crc((long)TechLevel);
    if (Tag != 0) {
        crc(((AbstractClass *)Tag)->Fetch_ID());
    }
    crc((long)Waypoint);
    crc((long)TransportWaypoint);
    crc((long)unknown_d4);
    if (Script != 0) {
        crc(((AbstractClass *)Script)->Fetch_ID());
    }
    if (TaskForce != 0) {
        crc(((AbstractClass *)TaskForce)->Fetch_ID());
    }
}
