// VectorClass<Wstring>::VectorClass(unsigned size, Wstring const *array) (0x00674AF0): the out-of-line copy MultiMission's
// constructor calls for GameModes (the header body, as an explicit specialization declared in that draft).
template <>
VectorClass<Wstring>::VectorClass(unsigned size, Wstring const *array)
    : Vector(0), VectorMax(size), IsValid(true), IsAllocated(false)
{
    if (size) {
        if (array) {
            Vector = new ((void *)array) Wstring[size];
        } else {
            Vector = new Wstring[size];
            IsAllocated = true;
        }
    }
}
