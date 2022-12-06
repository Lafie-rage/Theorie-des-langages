#ifndef HOC_H
#define HOC_H

#ifdef HOC_L
#include "symbol.h"
#include "hoc.tab.h"
#endif

#ifdef HOC_Y
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symbol.h"
#endif

#ifdef SYMBOL_C_C
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "symbol.h"
#include "hoc.tab.h"

#endif

#endif // HOC_H
