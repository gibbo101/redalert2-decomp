// AircraftClass::AircraftClass(AircraftTypeClass *type, HouseClass *house) (0x00413A40)
// Takes an ID, creates the type's locomotor and links it to the aircraft,
// initializes from the type, then joins the aircraft list and the techno
// index.
#include "shared/aircraft.hpp"
// @ref ??0FootClass@@QAE@PAVHouseClass@@@Z=004c2930
// @ref ?Create_ID@AbstractClass@@UAGXXZ=0040ffd0
// @ref ?Fetch_ID@AbstractClass@@UAGJXZ=0040ffc0
// @ref _unknown_uuid_IUnknown_7ce610=007ce610
// @ref _unknown_uuid_ILocomotion_7ce600=007ce600
// @ref __imp__CoCreateInstance@20=0079a5f0
// @ref __imp__OleRun@4=0079a5f4
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?Aircraft@@3V?$DynamicVectorClass@PAVAircraftClass@@@@A=00a40398
// @ref ?unknown_object_index_abff58@@3V?$IndexClass@JPAVAbstractClass@@@@A=00abff58
// @ref ??_U@YAPAXI@Z=00782017
// @ref ??_7AircraftClass@@6BIPersistStream@@@=0079b12c
// @ref ??_7AircraftClass@@6BIRTTITypeInfo@@@=0079b110
// @ref ??_7AircraftClass@@6BINoticeSink@@@=0079b108
// @ref ??_7AircraftClass@@6BINoticeSource@@@=0079b100
// @ref ??_7AircraftClass@@6B@=0079b0d8
// @ref ??3@YAXPAX@Z=00781d3b

AircraftClass::AircraftClass(AircraftTypeClass *type, HouseClass *house) :
    FootClass(house),
    Type(type),
    unknown_5b0(false),
    unknown_5b1(false),
    unknown_5b2(false),
    unknown_5b4(0),
    unknown_5b8(false),
    unknown_5b9(false),
    unknown_5ba(false),
    unknown_5bb(5),
    unknown_5bc(true),
    unknown_5bd(true)
{
    Create_ID();
    if (Type != 0) {
        Locomotor.CreateInstance(Type->Locomotor, 0, CLSCTX_ALL);
        Locomotor.Checked()->Link_To_Object(this);
    }
    Init();
    Aircraft.Add(this);
    unknown_object_index_abff58.Add_Index(Fetch_ID(), this);
}
