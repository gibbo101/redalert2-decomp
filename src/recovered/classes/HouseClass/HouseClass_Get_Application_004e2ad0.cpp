// IApplication *__stdcall HouseClass::Get_Application() (0x004E2AD0)
#include "shared/techno.hpp"

IApplication *__stdcall HouseClass::Get_Application()
{
    IApplication *application;
    Unknown_00426C60(&unknown_application_84c7dc, IID_IApplication_79c3d0, (void **)&application);
    return application;
}
