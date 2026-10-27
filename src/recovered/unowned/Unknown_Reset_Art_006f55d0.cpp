// void __fastcall Unknown_Reset_Art_006F55D0(int width, int height) -- 0x006F55D0
// Frees the art blocks and rebuilds the layout for the new size (hypothesis).
// @ref ?Unknown_6F5400@@YIXXZ=006f5400
// @ref ?Unknown_006F4C90@@YIXHH@Z=006f4c90

void __fastcall Unknown_6F5400();
void __fastcall Unknown_006F4C90(int width, int height);

void __fastcall Unknown_Reset_Art_006F55D0(int width, int height)
{
    Unknown_6F5400();
    Unknown_006F4C90(width, height);
}
