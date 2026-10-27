// void NullModemConnClass::Init(int port) -- 0x005CDBB0
// The base initialization, then the serial port handle (+0x4C).

void NullModemConnClass::Init(int port)
{
    ConnectionClass::Init();
    PortHandle = port;
}
