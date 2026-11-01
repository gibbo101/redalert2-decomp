void LogicClass::Detach(AbstractClass const *target, bool all)
{
    if (target != 0 && target->Kind_Of() == 0x2C) {
        for (int index = 0; index < unknown_tags_866160.Count(); index++) {
            if (target == (AbstractClass *)unknown_tags_866160[index]) {
                unknown_tags_866160.Delete(index);
                index--;
            }
        }
    }
}
// @ref ?unknown_tags_866160@@3V?$DynamicVectorClass@PAVTagClass@@@@A=00866160
