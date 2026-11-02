// Per-frame update: shrinking radar ping, rotation and pulsing color.
#include "shared/radar_event_class.hpp"
#include "shared/rules.hpp"
#include "shared/crt_math.hpp"
#ifndef MAX
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#endif

void RadarEventClass::Unknown_0063B940()
{
    if (IsVisible) {
        if (!IsRotating && VisibilityTimer == 0) IsVisible = false;
        Plot();
        Radius = MAX(Radius - Rules->RadarEventSpeed, (float)Rules->RadarEventMinRadius);
        float normalized = RotationAngle + (3.14159265358979323846 / 4) - (int)((RotationAngle + (3.14159265358979323846 / 4)) * (2 / 3.14159265358979323846)) * 3.14159265358979323846 / 2;
        if (IsRotating) {
            if (fabs(Radius - Rules->RadarEventMinRadius) < 0.01) {
                if (normalized < RotationSpeed) {
                    RotationAngle = normalized + RotationAngle;
                    IsRotating = false;
                    VisibilityTimer = Unknown_0063C610();
                    DurationTimer = Unknown_0063C620();
                } else {
                    RotationAngle += RotationSpeed;
                    RotationSpeed = MAX(Rules->RadarEventRotationSpeed * (1.0f / 3.0f), RotationSpeed - Rules->RadarEventRotationSpeed * 0.02f);
                }
            } else {
                RotationAngle = RotationSpeed + RotationAngle;
            }
        }
        if (RotationAngle > 6.28318530717958647692) RotationAngle -= 6.28318530717958647692;
        float next_color = ColorSpeed;
        next_color += ColorFactor;
        ColorFactor = next_color;
        if (next_color < 0.0f && ColorSpeed < 0.0f) {
            ColorSpeed = -ColorSpeed;
            ColorFactor = 0.0f;
        } else if (next_color > 1.0f && ColorSpeed > 0.0f) {
            ColorSpeed = -ColorSpeed;
            ColorFactor = 1.0f;
        }
    }
}

// @ref __real@8@3ffec90fdaa22168c000=0079ca80
// @ref __real@8@3ffea2f9836e4e441800=0079d098
// @ref __real@4@3ffdaaaaab0000000000=007a5ea8
// @ref __real@4@3ff9a3d70a0000000000=007a8ea8
