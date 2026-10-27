// int IPXManagerClass::Get_Private_Message(void *buf, int *buflen, int *conn_id) (0x00525D30, slot 3)
// Reads the next packet, polling the connections round-robin.
#include "shared/ipx_manager.hpp"

int IPXManagerClass::Get_Private_Message(void *buf, int *buflen, int *conn_id)
{
    if (!IPXStatus || !Listening || NumConnections == 0) {
        return 0;
    }
    if (CurConnection >= NumConnections) {
        CurConnection = 0;
    }
    for (int i = 0; i < NumConnections; i++) {
        int rc = Connection[CurConnection]->Get_Packet(buf, buflen);
        int id = Connection[CurConnection]->ID;
        CurConnection++;
        if (CurConnection >= NumConnections) {
            CurConnection = 0;
        }
        if (rc) {
            *conn_id = id;
            return 1;
        }
    }
    return 0;
}
