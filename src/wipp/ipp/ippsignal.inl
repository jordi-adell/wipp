#include <wipp/wippsignal.h>

#include <math.h>

void wipp_triangle(double *buffer, size_t length)
{
    static const double phase = 3*M_PI_2;
    ippsTriangle_Direct_64f(buffer, length, 1.0, 0.5/length, 0, &phase);
}
