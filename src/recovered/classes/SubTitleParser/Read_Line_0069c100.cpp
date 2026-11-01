// bool __fastcall Read_Line(Straw &input, unsigned short *buffer, int count) (0x0069C100): one line of the
// script: up to count characters, carriage returns dropped; true at the end of the input.
bool __fastcall Read_Line(Straw &input, unsigned short *buffer, int count)
{
    *buffer = 0;
    bool eof = false;
    int length = 0;
    while (length < count) {
        unsigned short character;
        if (input.Get(&character, sizeof(character)) != sizeof(character)) {
            eof = true;
            break;
        }
        if (character == '\n') {
            break;
        }
        if (character != '\r') {
            buffer[length] = character;
            length++;
        }
    }
    buffer[length] = 0;
    return eof;
}
