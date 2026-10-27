bool FactoryClass::Abandon_Production_004B97C0()
{
    if (Object) {
        Debug_Printf(unknown_abandon_message_7d7f44, (char const *)Object->Class_Of()->Name);
        Owner->Refund_Money(Object->Class_Of()->unknown_slot33((int)Object->House) - UnspentCost);
        UnspentCost = 0;
        if (unknown_64) unknown_64 = -1;
        Set_Rate(0);
        Stage = 0;
        unknown_6c = true;
        unknown_59 = true;
        if (!Owner->Unknown_004F52F0()) {
            if (Object->Kind_Of() == 15) Owner->unknown_5544 = -1;
            if (Object->Kind_Of() == 1) Owner->unknown_5540 = -1;
            if (Object->Kind_Of() == 2) Owner->unknown_5548 = -1;
            if (Object->Kind_Of() == 6) Owner->unknown_553c = -1;
        }
        ++unknown_a40774;
        delete Object;
        Object = 0;
        --unknown_a40774;
        return true;
    }
    return false;
}
