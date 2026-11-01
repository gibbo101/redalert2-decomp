// 0x0063FB60: a player's port.
void OwnerTalkClass::Unknown_0063FB60(int id, unsigned short port)
{
    for (int index = 0; index < Connections.Count(); index++) {
        if (Connections[index]->ID == id) {
            Connections[index]->Port = port;
            break;
        }
    }
}
