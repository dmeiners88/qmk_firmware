#pragma once

#include "config_common.h"

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
#define RGBLIGHT_DEFAULT_MODE (RGBLIGHT_MODE_STATIC_GRADIENT + 8)

#define RGBLIGHT_DEFAULT_HUE 170
#define RGBLIGHT_DEFAULT_SAT 255
#define RGBLIGHT_DEFAULT_VAL 255

#define RGBLIGHT_LAYERS
