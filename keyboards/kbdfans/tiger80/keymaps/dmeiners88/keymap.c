#include QMK_KEYBOARD_H

#define _BASE 0
#define _MAGIC 1
#define _FN 2
#define _GAME 3

enum my_keycodes { VDSK_CH = SAFE_RANGE, VDSK_LK };

static bool vdesk_state = false;
static bool vdesk_lock  = false;

void change_virtual_desktop(void) {
    if (vdesk_lock) {
        rgblight_blink_layer_repeat(3, 250, 3);
    } else {
        tap_code16(LCTL(LGUI(vdesk_state ? KC_LEFT : KC_RGHT)));
        vdesk_state = !vdesk_state;
        rgblight_blink_layer_repeat(1, 100, 1);
    }
}

void toggle_virtual_desktop_lock(void) {
    vdesk_lock = !vdesk_lock;
    rgblight_blink_layer_repeat(vdesk_lock ? 3 : 2, 750, 1);
}

bool conditionally_reset_keyboard(void) {
    if ((get_mods() & (MOD_BIT(KC_RCTL) | MOD_BIT(KC_RALT))) == (MOD_BIT(KC_RCTL) | MOD_BIT(KC_RALT))) {
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_setrgb(RGB_RED);
        return true;
    }
    return false;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT_tkl_f13_ansi_tsangan(
        KC_ESC,     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,         KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  VDSK_CH, KC_MPLY, KC_MNXT, KC_MUTE,
        KC_GRV,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,          KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP,
        KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,          KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN,
        MO(1),      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,          KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,             KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,          KC_UP,
        KC_LCTL,    KC_LGUI, KC_LALT,                            LT(1, KC_SPC),                                     KC_RALT, MO(2),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_MAGIC] = LAYOUT_tkl_f13_ansi_tsangan(
        _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, VDSK_LK, KC_MSTP, KC_MPRV, _______,
        _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, KC_PSCR, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______,          _______,          _______,
        _______, _______, _______,                            _______,                                           _______, _______, _______, _______, _______, _______
    ),

    [_FN] = LAYOUT_tkl_f13_ansi_tsangan(
        QK_BOOT, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
        _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
        _______, _______, _______, KC_SCRL, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
        _______, _______, _______, _______, _______, TG(3),   _______,       _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______,          _______,           RGB_HUI,
        _______, _______, _______,                            _______,                                           _______, _______, _______, RGB_RMOD, RGB_HUD, RGB_MOD
    ),

    [_GAME] = LAYOUT_tkl_f13_ansi_tsangan(
        _______,  _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______,          _______,          _______,
        _______, _______, _______,                            KC_SPC,                                            _______, _______, _______, _______, _______, _______
    )
};
// clang-format on

const rgblight_segment_t PROGMEM _black_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, HSV_BLACK}); // unused
const rgblight_segment_t PROGMEM _cyan_layer[]  = RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_CYAN});
const rgblight_segment_t PROGMEM _green_Layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_GREEN});
const rgblight_segment_t PROGMEM _red_layer[]   = RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_RED});

const rgblight_segment_t *const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(_black_layer, _cyan_layer, _green_Layer, _red_layer);

void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case VDSK_CH:
            if (record->event.pressed) {
                change_virtual_desktop();
            }
            return false;
        case VDSK_LK:
            if (record->event.pressed) {
                toggle_virtual_desktop_lock();
            }
            return false;
        case QK_BOOT:
            return conditionally_reset_keyboard();
        default:
            return true;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, IS_LAYER_ON_STATE(state, _BASE));
    rgblight_set_layer_state(1, IS_LAYER_ON_STATE(state, _MAGIC));

    if (IS_LAYER_ON_STATE(state, _MAGIC)) {
        register_code(KC_F24);
    } else {
        unregister_code(KC_F24);
    }

    return state;
}
