// SubzoneTrackingStruct::operator=0056C2E0, member-wise list and tracking-state assignment.
#include "shared/map.hpp"
SubzoneTrackingStruct &SubzoneTrackingStruct::operator=(SubzoneTrackingStruct const &other)
{
    Connections = other.Connections;
    unknown_18 = other.unknown_18;
    unknown_1c = other.unknown_1c;
    unknown_20 = other.unknown_20;
    return *this;
}
