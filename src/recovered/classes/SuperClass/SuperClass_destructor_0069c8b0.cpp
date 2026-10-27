// SuperClass::~SuperClass() (0x0069C8B0)
// Drops the animation and leaves every list.
// @ref ?unknown_supers_a35db8@@3V?$DynamicVectorClass@PAVSuperClass@@@@A=00a35db8
// @ref ??1AbstractClass@@UAE@XZ=0040ff90
// @ref ?Delete@?$DynamicVectorClass@PAVAbstractClass@@@@QAE_NH@Z=00454b20

// The scalar deleting destructor (0x0069ECD0) calls this out of line.
#pragma auto_inline(off)
SuperClass::~SuperClass()
{
    unknown_69ca70();
    unknown_supers_a35db8.Delete(this);
    Supers.Delete(this);
    unknown_objects_ac0cb0.Delete(this);
    unknown_abstracts_ac0d08.Delete(this);
}
#pragma auto_inline(on)
