#include QMK_KEYBOARD_H

enum my_keycodes { VDESK = SAFE_RANGE };

static uint8_t vdesk_state = 0;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_tkl_f13_ansi_tsangan(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,         KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  VDESK,   KC_MPLY, KC_MNXT, KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,          KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,          KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN,
        MO(1)  , KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,          KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,          KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                            LT(1, KC_SPC),                                     KC_RALT, MO(2),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT_tkl_f13_ansi_tsangan(
        _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, KC_MSTP, KC_MPRV, _______,
        _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, KC_PSCR, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______,          _______,          _______,
        _______, _______, _______,                            _______,                                           _______, _______, _______, _______, _______, _______
    ),

    [2] = LAYOUT_tkl_f13_ansi_tsangan(
        _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
        _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
        _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
        _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______,          _______,           RGB_HUI,
        _______, _______, _______,                            _______,                                           _______, _______, _______, RGB_RMOD, RGB_HUD, RGB_MOD
    )

};
// clang-format on

const rgblight_segment_t PROGMEM layer_0[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, HSV_BLACK}); // unused
const rgblight_segment_t PROGMEM layer_1[] = RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_CYAN});

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(layer_0, layer_1);

void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case VDESK:
            if (record->event.pressed) {
                if (vdesk_state) {
                    tap_code16(LCTL(LGUI(KC_LEFT)));
                    vdesk_state = 0;
                } else {
                    tap_code16(LCTL(LGUI(KC_RGHT)));
                    vdesk_state = 1;
                }
            }
            return false;
        case KC_ESC:
            if (IS_LAYER_ON(2) && (get_mods() & (MOD_BIT(KC_RCTL) | MOD_BIT(KC_RALT))) == (MOD_BIT(KC_RCTL) | MOD_BIT(KC_RALT))) {
                // reset to bootloader if RCTL + RALT + FN + ESC is pressed
                reset_keyboard();
                return false;
            }
        default:
            return true;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));

    switch (get_highest_layer(state)) {
        case 0:
            unregister_code(KC_F24);
            break;
        case 1:
            register_code(KC_F24);
            break;
        default:
            break;
    }
    return state;
}
