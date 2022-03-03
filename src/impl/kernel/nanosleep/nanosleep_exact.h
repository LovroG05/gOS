#pragma once

#include "../types.h"

ui16 nanosleep_exact_init();
ui16 nanosleep_exact(ui32 nanoseconds);
ui16 nanosleep_exact_continue(ui32 nanoseconds, ui32 hint);
