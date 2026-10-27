// void SuperClass::unknown_69ca70() (0x0069CA70)

void SuperClass::unknown_69ca70()
{
    if (Anim != 0) {
        Anim->Loops = 0;
        Anim = 0;
        unknown_abstracts_ac0bf8.Delete(this);
    }
    if (AnimDetached) {
        unknown_abstracts_ac0bf8.Delete(this);
        AnimDetached = false;
    }
}
