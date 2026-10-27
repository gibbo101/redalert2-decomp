// int Wstring::Get_Line(int start, Wstring &line) const (0x0076F3D0)
// Copies the text from start up to its line end (CR, LF, or CR LF kept in
// the line) and returns the position after it; -1 past the end.
#include "shared/wstring.hpp"

int Wstring::Get_Line(int start, Wstring &line) const
{
    int position = start;
    if (start >= (int)Length()) {
        return -1;
    }
    while (position < (int)Length() && !strchr("\r\n", Buffer[position])) {
        position++;
    }
    int end = position;
    if (Buffer[position] == '\r' && Buffer[position + 1] == '\n') {
        position++;
        end = position;
    }
    line = Buffer + start;
    line.Truncate(end - start + 1);
    return end + 1;
}
