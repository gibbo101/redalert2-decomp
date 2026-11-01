void LogicClass::Remove(ObjectClass *object)
{
    if (object->unknown_84) {
        Delete(object);
        object->unknown_84 = false;
    }
}
