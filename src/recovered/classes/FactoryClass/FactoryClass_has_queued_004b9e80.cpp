bool FactoryClass::Has_Queued_004B9E80(TechnoTypeClass *type) const
{
    for (int index = 0; index < Queue.Count(); ++index) {
        if (type == Queue[index]) return true;
    }
    return false;
}
