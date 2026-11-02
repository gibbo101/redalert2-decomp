// void SuperClass::unknown_69ca70() (0x0069CA70)
// Drops the animation and its entry in the animation list. The explicit
// upcasts in the two Delete calls are the spelling hypothesis that gives this
// body the original inline size (0x0069CB30 then keeps its second
// Delete(int) out of line, and Recharge needs no Is_Present() call).

void SuperClass::unknown_69ca70()
{
    if (Anim != 0) {
        Anim->Loops = 0;
        Anim = 0;
        unknown_abstracts_ac0bf8.Delete((AbstractClass *)this);
    }
    if (AnimDetached) {
        unknown_abstracts_ac0bf8.Delete((AbstractClass *)this);
        AnimDetached = false;
    }
}
