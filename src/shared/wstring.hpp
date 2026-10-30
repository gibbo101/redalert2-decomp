// Wstring: a heap-allocated, null-terminated character string.
//
// No RTTI or vtable: the class name comes from the RTTI of its containers
// (VectorClass<Wstring> 0x007A9644, DynamicVectorClass<Wstring> 0x007A9664)
// and from INIClass, which takes and returns Wstring values. Member names
// describe observed behaviour; original member names are not recovered.
//
// Layout (4 bytes):
//   +0x00 char *Buffer   owned heap block from operator new, or null.
//
// A null Buffer reads as the empty string through the conversions (the
// shared empty literal at 0x0083C55C) and as length 0. Comparisons treat
// two null strings as equal and one null string as different from any
// non-null one, otherwise compare with strcmp (case sensitive).
//
// Every mutation reallocates exactly: concatenation allocates the combined
// length, copies the old text, appends, then frees the old block.
//
// The members are defined in one translation unit in address order
// (0x0076D910-0x0076E7B8 so far); /Ob2 inlines Release, the conversions and
// the concatenation helpers into their callers there.
//
// shared/ini_class.hpp includes this header (INIClass compiles exact with
// the full class; an earlier minimal copy there was removed).
#ifndef RA2_SHARED_WSTRING_HPP
#define RA2_SHARED_WSTRING_HPP

#include "shared/crt_string.hpp"

extern "C" unsigned int __cdecl strlen(char const *string);
extern "C" char *__cdecl strncpy(char *destination, char const *source, unsigned int count);
extern "C" char *__cdecl strncat(char *destination, char const *source, unsigned int count);
extern "C" char *__cdecl strchr(char const *string, int character);
extern "C" void *__cdecl memset(void *destination, int value, unsigned int count);
#pragma intrinsic(strlen, memset)
// C library calls of the later members (0x0076EE20-0x0076F610).
extern "C" int __cdecl tolower(int character);
extern "C" int __cdecl toupper(int character);
extern "C" int __cdecl atoi(char const *string);
extern "C" int __cdecl sprintf(char *buffer, char const *format, ...);
extern "C" char *__cdecl strstr(char const *string, char const *find);
extern "C" unsigned int __cdecl strcspn(char const *string, char const *characters);

void *__cdecl operator new(unsigned int size);
void __cdecl operator delete(void *block);

class Wstring {
public:
    Wstring();                                          // 0x0076D910
    Wstring(char const *string);                        // 0x0076D920
    Wstring(Wstring const &other);                      // 0x0076D980
    ~Wstring();                                         // 0x0076D9E0

    bool operator==(char const *string) const;         // 0x0076DA00
    bool operator==(Wstring const &other) const;       // 0x0076DA70
    bool operator!=(char const *string) const;         // 0x0076DAE0
    bool operator!=(Wstring const &other) const;       // 0x0076DB50

    Wstring &operator=(char const *string);            // 0x0076DBC0
    Wstring &operator=(Wstring const &other);          // 0x0076DC30

    // Appends; always returns true (a null string appends nothing).
    bool Concatenate(char const *string);              // 0x0076DD00
    // Appends at most `length` characters of `string` (strncat).
    bool Concatenate(unsigned length, char const *string); // 0x0076DDB0
    bool Concatenate(Wstring const &other);            // 0x0076DE40
    Wstring &operator+=(char const *string);           // 0x0076DF10
    Wstring &operator+=(Wstring const &other);         // 0x0076DFC0
    Wstring operator+(char const *string) const;       // 0x0076E090
    Wstring operator+(Wstring const &other) const;     // 0x0076E1C0

    // Deletes `count` characters at `position` after clamping the window to
    // the string; false when nothing remains to delete.
    bool Remove(int position, int count);              // 0x0076E310
    // Deletes every occurrence of `character`; true when any was found.
    bool Remove_Character(char character);             // 0x0076E3E0
    // Deletes all spaces and tabs.
    void Remove_Spaces();                               // 0x0076E4A0
    // Deletes leading / trailing characters that appear in `characters`.
    void Trim_Leading(Wstring const &characters);      // 0x0076E4C0
    void Trim_Trailing(Wstring const &characters);     // 0x0076E520

    // Frees the buffer (the string becomes null).
    void Release();                                     // 0x0076E630
    // Replaces the contents with `size` zero bytes (nothing for a negative size).
    void Set_Size(int size);                            // 0x0076E650
    // Copies into a fixed field of `size` characters, padding with spaces,
    // and terminates it at buffer[size].
    void Copy_Padded(char *buffer, unsigned size) const; // 0x0076E6A0

    char const *Get() const;                            // 0x0076E6F0
    // Character at `index`, or 0 past the end (three identical copies; the
    // two operator names are placeholders for the second and third).
    char Get_Char(unsigned index) const;                // 0x0076E700
    // A second copy of Get (0x0076E730). Not a conversion operator: the original
    // calls INIClass's Wstring overloads with string literals, which an implicit
    // char const * conversion would make ambiguous (Sched29).
    char const *Peek_Buffer() const;                    // 0x0076E730
    char operator[](unsigned index) const;              // 0x0076E740
    char operator()(unsigned index) const;              // 0x0076E770
    unsigned Length() const;                            // 0x0076E7A0

    // Inserts a C string / one character at position (clamped to the
    // length); a null string just takes the text (0x0076E7C0, 0x0076E930).
    bool Insert(char const *string, unsigned position);
    bool Insert(char character, unsigned position);
    // Replaces every occurrence of find with `with` (0x0076EA90; name
    // hypothesis).
    bool Replace(char const *find, char const *with);
    // Replaces the contents with a copy of string (empty for null); true
    // (0x0076ED30; operator= returning a flag; name hypothesis).
    bool Set(char const *string);
    // Replaces the character at index (false past the end; 0x0076EDA0).
    bool Set_Char(char character, unsigned index);
    // Replaces the contents with at most length characters of string,
    // allocating length + 1 bytes (0x0076EDD0; name hypothesis).
    bool Set(unsigned length, char const *string);

    // Lowercases A-Z in place (0x0076EE20; MSChoice.cpp lowers both sides
    // of its name comparisons).
    void To_Lower();                                    // 0x0076EE20
    // A lowercased copy (0x0076EE70; name hypothesis).
    Wstring As_Lower() const;
    // Uppercases a-z in place (0x0076EF40).
    void To_Upper();
    // An uppercased copy (0x0076EF90; name hypothesis).
    Wstring As_Upper() const;
    // Keeps the first length characters (through a temporary; 0x0076F060)
    // and keeps the text before the first `character` (false when absent;
    // 0x0076F120). Names are hypotheses.
    bool Truncate(unsigned length);
    bool Truncate_At(char character);
    // Copies the text from `start` up to the next separator into `token`;
    // returns the position after it (-1 for a negative start). Hypothesis
    // from the MSChoice.cpp callers, which chain the returned position.
    int Get_Token(int start, char const *separators, Wstring &token) const;  // 0x0076F200
    // Copies the line from start up to its CR, LF or CR LF into line and
    // returns the position after it; -1 at the end (0x0076F3D0; name
    // hypothesis).
    int Get_Line(int start, Wstring &line) const;
    // atoi of the text (0x0076F570).
    int As_Integer() const;                             // 0x0076F570
    // Whether the text contains any of characters (0x0076F920, 0x0076F960).
    bool Contains_Any(char const *characters) const;
    bool Contains_Any(Wstring const &characters) const;
    // The text buffer (public: 0x005CB8D0 reads it directly), null for an empty string.
    char *Buffer;
};

// Decimal text of value, optionally zero-padded to width (0x0076F580,
// 0x0076F610), and a C string followed by a Wstring (0x0076F6B0). Names are
// hypotheses; the original passes them in ECX/EDX (__fastcall).
Wstring __fastcall Wstring_From_Integer(int value);
Wstring __fastcall Wstring_From_Integer(int value, int width);
Wstring __fastcall operator+(char const *string, Wstring const &other);
Wstring __fastcall Wstring_Join(Wstring const &left, Wstring const &right);   // 0x0076F7D0

#endif
