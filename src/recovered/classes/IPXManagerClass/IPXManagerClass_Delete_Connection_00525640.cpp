// int IPXManagerClass::Delete_Connection(int id) (0x00525640)
// Deletes a private connection and closes the gap.
#include "shared/ipx_manager.hpp"

int IPXManagerClass::Delete_Connection(int id)
{
    if (!IPXStatus || NumConnections == 0) {
        return 0;
    }
    for (int i = 0; i < NumConnections; i++) {
        if (Connection[i]->ID == id) {
            delete Connection[i];
            for (int j = i; j < NumConnections - 1; j++) {
                Connection[j] = Connection[j + 1];
            }
            NumConnections--;
            if (CurConnection >= NumConnections) {
                CurConnection = 0;
            }
            return 1;
        }
    }
    return 0;
}
