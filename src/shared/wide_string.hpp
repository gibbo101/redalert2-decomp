// WideString: a heap-allocated, null-terminated 16-bit character string
// (the wide counterpart of Wstring; members 0x0076F9B0-0x007711xx).
//
// Evidence: one owned pointer, wcslen-based length (0x007704A0), wcstol
// conversion (0x00771070), operator delete in the destructor (0x0076FA50);
// MSChoice.cpp splits L","-separated lines with it. The class name is a
// hypothesis (no RTTI); member names describe behaviour.
#ifndef RA2_SHARED_WIDE_STRING_HPP
#define RA2_SHARED_WIDE_STRING_HPP

class WideString {
public:
    WideString();                                       // 0x0076F9B0
    WideString(unsigned short const *string);           // 0x0076F9C0
    WideString(WideString const &other);                // 0x0076FA10
    ~WideString();                                      // 0x0076FA50

    WideString &operator=(unsigned short const *string);   // 0x0076FB70
    WideString &operator=(WideString const &other);     // 0x0076FBD0
    // Comparisons (wcscmp); two null strings are equal, a null and a
    // non-null one are not (0x0076FA70, 0x0076FAB0).
    bool operator==(unsigned short const *string) const;
    bool operator==(WideString const &other) const;
    bool operator!=(unsigned short const *string) const;    // 0x0076FAF0
    bool operator!=(WideString const &other) const;         // 0x0076FB30
    // Appends (always true; a null string appends nothing); sized at four
    // bytes per character (0x0076FC60, 0x0076FCE0, 0x0076FD50).
    bool Concatenate(unsigned short const *string);
    bool Concatenate(unsigned length, unsigned short const *string);
    bool Concatenate(WideString const &other);
    void Remove_Spaces();                                   // (inline; Remove_Character twice)
    void Trim_Leading(WideString const &characters);        // 0x007701D0
    void Trim_Trailing(WideString const &characters);       // 0x00770230
    // Inserts a string / one character at position (clamped to the length);
    // a null string just takes the text (0x007704C0, 0x007705E0).
    bool Insert(unsigned short const *string, unsigned position);
    bool Insert(unsigned short character, unsigned position);
    // Replaces every occurrence of find with `with` (0x007706E0; name hypothesis).
    bool Replace(unsigned short const *find, unsigned short const *with);
    bool Set_Char(unsigned short character, unsigned index);   // 0x00770950
    short Set(unsigned length, unsigned short const *string);  // 0x00770980 (returns a 16-bit 1)
    void To_Lower();                                        // 0x007709E0
    WideString As_Lower() const;                            // 0x00770A30
    void To_Upper();                                        // 0x00770AD0
    WideString As_Upper() const;                            // 0x00770B20
    int Get_Line(int start, WideString &line) const;        // 0x00770EF0
    bool Truncate(unsigned length);                         // 0x00770BC0
    bool Truncate_At(unsigned short character);             // 0x00770C70
    void Set_Size(int size);                                // 0x00770350 (name hypothesis)
    void Copy_Padded(unsigned short *buffer, unsigned size) const;   // 0x007703A0
    unsigned short Get_Char(unsigned index) const;          // 0x00770470
    bool Remove_Character(unsigned short character);        // 0x00770110 (name hypothesis)
    short Remove(int position, int count);                  // 0x00770080 (name hypothesis; returns a 16-bit flag)
    WideString &operator+=(unsigned short const *string);   // 0x0076FDD0
    WideString &operator+=(WideString const &other);        // 0x0076FE50
    // Non-const: with const operands the free operator+ (0x00771460) is the only candidate.
    WideString operator+(WideString const &other);          // 0x0076FFA0
    // As operator=(string), returning a 16-bit 1 (0x007708F0; name and return type hypotheses).
    short Set(unsigned short const *string);
    // The text, or an empty string when null (0x007703F0).
    // The same through a conversion (the original's two forms differ in code).
    operator unsigned short const *() const { return (Buffer == 0) ? (unsigned short const *)L"" : Buffer; }
    unsigned short const *Get() const;                      // 0x007703F0 (out of line; the unit's callers expand it)
    // The same (a second copy, 0x00770430; MultiplayerTeam passes the team
    // name through it).
    unsigned short const *unknown_text_770430() const;
    unsigned Length() const;                            // 0x007704A0
    // A copy with string appended (0x0076FED0; the new buffer is sized at
    // four bytes per character).
    WideString operator+(unsigned short const *string) const;
    // Wide counterpart of Wstring::Get_Token (0x00770D50).
    int Get_Token(int start, unsigned short const *separators, WideString &token) const;
    // wcstol(text, 0, 10) (0x00771070).
    int As_Integer() const;
    // Whether every character is below 0x100 (true for no text; 0x00771080; name hypothesis).
    bool Is_Narrow() const;
    // Whether the text contains any of characters (0x00771540, 0x00771580).
    bool Contains_Any(unsigned short const *characters) const;
    bool Contains_Any(WideString const &characters) const;

private:
    unsigned short *Buffer;     // +0x00
};

// left followed by right (0x00771460; result through ECX, left in EDX).
WideString __fastcall operator+(WideString const &left, WideString const &right);

#endif
