// Movie subtitles (RA2 only; RTTI DynamicVectorClass<SubTitle *> 0x007AC194): one caption of a movie's
// subtitle script (subtitle.txt, a UTF-16 file of "BeginMovie <name>" sections holding
// "<Time=..., Duration=..., Position=..., Color=r:g:b, Text="...">" entries), the parser that reads a
// section and the manager (VQAMovieCompanion, shared/movie.hpp) that shows them. Class SubTitle's
// members live in 0x0069B0C0-0x0069B16F; the parser's in 0x0069B680-0x0069C17F. Names other than
// SubTitle are hypotheses (Westwood's later Renegade BinkMovie code has the same parts).
#ifndef RA2_SHARED_SUBTITLE_HPP
#define RA2_SHARED_SUBTITLE_HPP

#include "shared/straw.hpp"

class SubTitle {
public:
    SubTitle();                                                                    // 0x0069B0C0
    ~SubTitle();                                                                   // 0x0069B0F0
    void Set_Color(unsigned char red, unsigned char green, unsigned char blue);    // 0x0069B100
    void Set_Text(unsigned short const *text);                                     // 0x0069B120

    void Set_Display_Time(unsigned long time) { DisplayTime = time; }
    unsigned long Get_Display_Time() const { return DisplayTime; }
    void Set_Display_Duration(unsigned long duration) { Duration = duration; }
    unsigned long Get_Display_Duration() const { return Duration; }
    unsigned long Get_RGB_Color() const { return Color; }
    void Set_Line_Position(int line) { LinePosition = line; }
    int Get_Line_Position() const { return LinePosition; }
    void Set_Alignment(int alignment) { Alignment = alignment; }
    int Get_Alignment() const { return Alignment; }
    unsigned short *Get_Text() const { return Text; }

    unsigned long DisplayTime;  // +0x00 movie time (1/60 s)
    unsigned long Duration;     // +0x04 (default 1200)
    unsigned long Color;        // +0x08 0xRRGGBB (default white)
    int LinePosition;           // +0x0C 1-based text line (default 15)
    int Alignment;              // +0x10 0 left, 1 right, 2 center (default)
    unsigned short *Text;       // +0x14 owned copy
};

template <class T> class DynamicVectorClass;

class SubTitleParser {
public:
    SubTitleParser(Straw &input);                                                  // 0x0069B680
    ~SubTitleParser();                                                             // 0x0069B6C0
    DynamicVectorClass<SubTitle *> *Get_Sub_Titles(char const *moviename);         // 0x0069B6D0
    bool Find_Movie_Entry(char const *moviename);                                  // 0x0069B9A0
    bool Parse_Sub_Title(unsigned short *string, SubTitle *subtitle);              // 0x0069BAD0
    void Parse_Token(unsigned short *token, unsigned short *param, SubTitle *subtitle);   // 0x0069BC60
    unsigned short *Get_Next_Line();                                               // 0x0069BCB0

    Straw &Input;                   // +0x000
    unsigned short Buffer[0x400];   // +0x004
    int LineNumber;                 // +0x804
};

#endif
