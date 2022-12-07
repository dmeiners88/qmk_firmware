#pragma once

#include "config_common.h"

#define TAPPING_TERM 133

#ifdef LOCKING_SUPPORT_ENABLE
#    undef LOCKING_SUPPORT_ENABLE
#endif

#ifdef LOCKING_RESYNC_ENABLE
#    undef LOCKING_RESYNC_ENABLE
#endif

#define MATRIX_IO_DELAY 20
#define FORCE_NKRO

#ifdef RGBLIGHT_DEFAULT_MODE
#    undef RGBLIGHT_DEFAULT_MODE
#endif

#define RGBLIGHT_LAYERS
#define RGBLIGHT_LAYER_BLINK
