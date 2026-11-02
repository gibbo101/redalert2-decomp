// void SchemeTable::Set_Theater(int theater) (0x00604AD0): stores the theater and rebuilds every node's list.

void SchemeTable::Set_Theater(int theater)
{
    unknown_00 = theater;
    UnknownSchemeListIterator it;
    HashString *key = Table->Next(it);
    while (key != 0) {
        Rebuild_Node(key->Text);
        key = Table->Next(it);
    }
}
