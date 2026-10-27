#include "shared/wstring.hpp"
void const *__fastcall Unknown_Load_Shape_00495270(char const *filename, bool &allocated);
// @ref ?Peek_Buffer@Wstring@@QBEPBDXZ=0076e730
void const *__fastcall Unknown_Load_Shape_00495310(Wstring const &filename, bool &allocated)
{
    return Unknown_Load_Shape_00495270(filename.Peek_Buffer(), allocated);
}
