// A random HouseTypes index of a country that is Multiplay and not MultiplayPassive (expanded into 0x00672A30).
int UnknownSessionState::Unknown_00672940()
{
    int last = HouseTypes.Count() - 1;
    int index;
    do {
        index = unknown_id_source_a3d290->Random()(0, last);
    } while (!HouseTypes[index]->Multiplay || HouseTypes[index]->MultiplayPassive);
    return index;
}
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ?HouseTypes@@3V?$DynamicVectorClass@PAVHouseTypeClass@@@@A=00a35d08
