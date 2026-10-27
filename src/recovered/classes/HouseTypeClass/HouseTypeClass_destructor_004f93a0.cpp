// HouseTypeClass::~HouseTypeClass() (0x004F93A0)
// Removes the type from HouseTypes.

HouseTypeClass::~HouseTypeClass()
{
    Unknown_006ECB90(this, true);
    HouseTypes.Delete(this);
}
