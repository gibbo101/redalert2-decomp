// int FirewallSettings::Get_Allocation_Delta(int count, unsigned short *original_ports, unsigned short *ports,
// bool *relative, bool *sequential) (0x005BAC50; Detect 0x005BA2C0): sorts the mangled ports (the original ports
// alongside), then classifies the allocation: incremental (delta 1) or semi-incremental (2), absolute sequences,
// else relative to the original ports; returns the delta (0 when none fits). delta is recomputed before the
// delta == 2 test: with one assignment VC6 threads the failed delta == 1 sub-tests past it.
#include "shared/firewall_settings.hpp"
#include "shared/debug_printf.hpp"
// @ref ??_C@_0CG@NGDL@Incremental?5port?5allocation?5dete@=007e6768
// @ref ??_C@_0CL@GAG@Semi?9incremental?5port?5allocation@=007e673c
// @ref ??_C@_0DC@FED@Looks?5good?5for?5a?5relative?5port?5r@=007e6698
// @ref ??_C@_0DD@DPKI@Probable?5absolute?5allocation?5seq@=007e66cc
// @ref ??_C@_0DJ@KLFN@Looks?5good?5for?5absolute?5allocati@=007e6700
// @ref ??_C@_0DK@OEFH@Detected?5probable?5broken?5relativ@=007e665c
// @ref ??_C@_0EG@CPIC@Looking?5for?5port?5allocation?5patt@=007e6790
// @ref ??_C@_0DP@PFHK@Mangler?5is?5seeing?5packets?5from?5p@=007e6420

int FirewallSettings::Get_Allocation_Delta(int count, unsigned short *original_ports, unsigned short *ports, bool *relative, bool *sequential)
{
    Debug_Printf("Looking for port allocation pattern in original_ports %d, %d, %d, %d\n",
        original_ports[0], original_ports[1], original_ports[2], original_ports[3]);

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count - 1; j++) {
            if (ports[j] > ports[j + 1]) {
                int temp = ports[j];
                ports[j] = ports[j + 1];
                ports[j + 1] = temp;
                temp = original_ports[j];
                original_ports[j] = original_ports[j + 1];
                original_ports[j + 1] = temp;
            }
        }
    }

    int delta;
    delta = ports[1] - ports[0];
    if (delta == 1 && ports[2] - ports[1] == delta && ports[3] - ports[2] == delta) {
        Debug_Printf("Incremental port allocation detected\n");
        *relative = false;
        *sequential = true;
        return delta;
    }
    delta = ports[1] - ports[0];
    if (delta == 2 && ports[2] - ports[1] == delta && ports[3] - ports[2] == delta) {
        Debug_Printf("Semi-incremental port allocation detected\n");
        *relative = false;
        *sequential = true;
        return delta;
    }
    int delta2 = ports[2] - ports[1];
    int delta3 = ports[3] - ports[2];
    if (delta == delta2) {
        if (delta2 == delta3) {
            Debug_Printf("Looks good for absolute allocation sequence delta of %d\n", delta);
            *relative = false;
            *sequential = true;
            return delta;
        }
        Debug_Printf("Probable absolute allocation sequence delta of %d\n", delta);
        *relative = false;
        *sequential = false;
        return delta;
    }
    if (delta2 == delta3) {
        Debug_Printf("Probable absolute allocation sequence delta of %d\n", delta2);
        *relative = false;
        *sequential = false;
        return delta2;
    }

    for (int k = 0; k < count; k++) {
        ports[k] -= original_ports[k];
    }
    delta = ports[1] - ports[0];
    delta2 = ports[2] - ports[1];
    delta3 = ports[3] - ports[2];
    if (delta == delta2) {
        if (delta2 == delta3) {
            Debug_Printf("Looks good for a relative port range delta of %d\n", delta);
            *relative = true;
            *sequential = true;
            return delta;
        }
    } else if (delta != delta3) {
        if (delta2 == delta3) {
            Debug_Printf("Detected probable broken relative port range delta of %d\n", delta2);
            *relative = true;
            *sequential = false;
            return delta2;
        }
        *sequential = false;
        *relative = false;
        return 0;
    }
    Debug_Printf("Detected probable broken relative port range delta of %d\n", delta);
    *relative = true;
    *sequential = false;
    return delta;
}
