// void SuperClass::Detach(AbstractClass *target, bool all) (0x0069EAF0)
// Forgets the house, the type or the animation when it goes away.

void SuperClass::Detach(AbstractClass *target, bool)
{
    if (target == (AbstractClass *)House) {
        House = 0;
    }
    if (target == (AbstractClass *)Type) {
        Type = 0;
    }
    if (target == Anim) {
        Anim = 0;
        AnimDetached = true;
    }
}
