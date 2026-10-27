int FactoryClass::Count_Type_004B9E40(TechnoTypeClass *type) const
{
    int total = 0;
    if (Object && Object->unknown_slot32() == type) total = 1;
    int count = Queue.Count();
    if (count > 0) {
        TechnoTypeClass *const *next = &Queue[0];
        do {
            if (*next == type) ++total;
            ++next;
        } while (--count);
    }
    return total;
}
