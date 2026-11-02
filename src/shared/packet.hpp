// PacketClass (Packet.cpp, 0x00602A60-0x00602FD0): the tagged-field packet of the Westwood Online
// messages. Layout follows original sender698D00 and the602Axx members; receive members remain declarations.
// Current is intentionally uninitialized by the short-ID constructor.
#ifndef RA2_SHARED_PACKET_HPP
#define RA2_SHARED_PACKET_HPP
#include "shared/packet_field.hpp"

class PacketClass {
public:
    PacketClass(short id = 0) : Size(0), ID(id), Head(0) {}
    void Add_Field(PacketField_004BAD50 *field); // 00602A90
    char *Create_Comms_Packet(int &size); // 00602BB0, originalRET4
    void Add_Field(char const *id, char value) { Add_Field(new PacketField_004BAD50(id, value)); }
    void Add_Field(char const *id, unsigned char value) { Add_Field(new PacketField_004BAD50(id, value)); }
    void Add_Field(char const *id, int value) { Add_Field(new PacketField_004BAD50(id, value)); }
    void Add_Field(char const *id, unsigned int value) { Add_Field(new PacketField_004BAD50(id, value)); }
    void Add_Field(char const *id, char const * value) { Add_Field(new PacketField_004BAD50(id, value)); }
    void Add_Field(char const *id, void const *value, unsigned short length) { Add_Field(new PacketField_004BAD50(id, value, length)); }
    PacketClass(char *buffer);                                         // 0x00602AA0 (parses a received block)
    ~PacketClass();                                                    // 0x00602A60 (deletes the fields)

#ifdef RA2_PACKET_UNIT
    // Declared only for Packet.cpp (RA2_PACKET_UNIT, set by its first source).
    PacketField_004BAD50 *Find_Field(char const *id);                  // 0x00602CD0 (expanded in every Get_Field)
    bool Get_Field(char const *id, char &data);                        // 0x00602D10
    bool Get_Field(char const *id, short &data);                       // 0x00602DB0
    bool Get_Field(char const *id, unsigned short &data);              // 0x00602E00
    bool Get_Field(char const *id, int &data);                         // 0x00602E50
    bool Get_Field(char const *id, char *data);                        // 0x00602EA0 (strcpy)
#endif
    bool Get_Field(char const *id, unsigned char &data);               // 0x00602D60
    bool Get_Field(char const *id, unsigned int &data);                // 0x00602F10
    bool Get_Field(char const *id, void *data, int &length);           // 0x00602F60 (length in/out)

    union { int unknown_00; struct { unsigned short Size; short ID; }; };                                                    // +0x00
    PacketField_004BAD50 *Head;                                                        // +0x04 field list
    PacketField_004BAD50 *Current;                                                     // +0x08
};

#endif
