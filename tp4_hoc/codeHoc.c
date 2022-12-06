#define _CODE_HOC_C_
#include "io.h"

double add(double x, double y) { return x + y; }
double sub(double x, double y) { return x - y; }
double mul(double x, double y) { return x * y; }
double myDiv(double x, double y)
{
    if (y == 0)
    {
        exeError("ERREUR ARITH : Div de %.8g par 0", x);
    }
    return x / y;
}
