// HRESULT __stdcall SuperClass::Load(IStream *stream) (0x0069E9F0)
// Rebuilds the super in place (AbstractClass part only), rejoins the
// animation list while it has an animation, and fixes up the pointers.
// @ref ??0AbstractClass@@QAE@XZ=0040ff10
// @ref ?unknown_abstracts_ac0bf8@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0bf8

HRESULT __stdcall SuperClass::Load(IStream *stream)
{
    HRESULT result = AbstractClass::Load(stream);
    if (FAILED(result)) {
        return result;
    }
    new (this) SuperClass(NoInitClass());
    if (Anim != 0) {
        unknown_abstracts_ac0bf8.Add(this);
    }
    SwizzleManager.Swizzle((void **)&Type);
    SwizzleManager.Swizzle((void **)&House);
    SwizzleManager.Swizzle((void **)&Anim);
    unknown_0x3C.unknown_4 = 0;
    unknown_0x3C.unknown_8 = 0;
    return S_OK;
}
