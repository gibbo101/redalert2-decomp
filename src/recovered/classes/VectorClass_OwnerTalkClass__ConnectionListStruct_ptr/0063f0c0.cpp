// 0x0063F0C0
OwnerTalkClass::~OwnerTalkClass()
{
    while (Connections.Count()) {
        delete Connections[0];
        Connections.Delete(0);
    }
}
