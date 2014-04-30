/* 
 * HHKB Layout
 */
#include "keymap_common.h"


#ifdef KEYMAP_SECTION_ENABLE
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
#endif
    /* https://github.com/tmk/tmk_keyboard/blob/5b425731c5b662d107ba0f970a7ae7c7fe97d01b/doc/keycode.txt */
    /* Layer 0: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Backs|
     * |-----------------------------------------------------------|
     * |Fn11  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  :|  '|Enter   |
     * |-----------------------------------------------------------|
     * |Fn12    |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Fn15  |Fn1|
     * `-----------------------------------------------------------'
     *       |Alt|Gui  |         Space         |Gui  |Alt|
     *       `-------------------------------------------'
     */
    KEYMAP(ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSLS,GRV,   \
           TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSPC,       \
           FN11,A,   S,   D,   F,   G,   H,   J,   K,   L,   FN12,QUOT,ENT,             \
           FN13,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RSFT,FN1,             \
                LALT,LGUI,          SPC,                RGUI,RALT),

    /* Layer 1: HHKB mode with Media Keys (HHKB Fn)
     * ,-----------------------------------------------------------.
     * |Pwr| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |Caps |MPT| MP|MNT|   |   |   |   |Psc|Slk|Pus|Up |   |Backs|
     * |-----------------------------------------------------------|
     * |      |VoD|VoU|Mut|   |   |  *|  /|Hom|PgU|Lef|Rig|Enter   |
     * |-----------------------------------------------------------|
     * |        |   |   |   |   |   |  +|  -|End|PgD|Dow|      |   |
     * `-----------------------------------------------------------'
     *       |   |     |                       |     |   |
     *       `-------------------------------------------'
     */ 
    KEYMAP(PWR, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL,   \
           CAPS,MPRV,MPLY,MNXT,TRNS,TRNS,TRNS,TRNS,PSCR,SLCK,PAUS, UP, TRNS, BSPC,      \
           TRNS,VOLD,VOLU,MUTE,TRNS,TRNS,PAST,PSLS,HOME,PGUP,LEFT,RGHT,PENT,            \
           TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PPLS,PMNS,END, PGDN,DOWN,TRNS,TRNS,            \
                TRNS,TRNS,          TRNS,               TRNS,TRNS),

    /* Layer #: Some Mode
     * ,-----------------------------------------------------------.
     * |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     * |-----------------------------------------------------------|
     * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |
     * |-----------------------------------------------------------|
     * |      |   |   |   |   |   |   |   |   |   |   |   |        |
     * |-----------------------------------------------------------|
     * |        |   |   |   |   |   |   |   |   |   |   |      |   |
     * `-----------------------------------------------------------'
     *       |   |     |                       |     |   |
     *       `-------------------------------------------'
     */ 
};


/* id for user defined functions */
enum function_id {
    SCLN_SWAP,
};

enum macro_id {
    LSHIFT_PAREN,
    RSHIFT_PAREN,
};


/*
 * Fn action definition
 */
#ifdef KEYMAP_SECTION_ENABLE
const uint16_t fn_actions[] __attribute__ ((section (".keymap.fn_actions"))) = {
#else
const uint16_t fn_actions[] PROGMEM = {
#endif
    [0] = ACTION_DEFAULT_LAYER_SET(0),                 // Default layer(not used)
    [1] = ACTION_LAYER_TAP_TOGGLE(1),                  // HHKB layer(toggle with 5 taps)

    [11] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_ESC),      // LControl with tap Esc
    [12] = ACTION_FUNCTION(SCLN_SWAP),                 // Close Tab
    [13] = ACTION_MODS_ONESHOT(MOD_LSFT),              // Oneshot Shift*
};

/*
 * Macro definition
 */
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    keyevent_t event = record->event;
    tap_t tap = record->tap;

    switch (id) {
        case LSHIFT_PAREN:
            if (tap.count > 0 && !tap.interrupted) {
                return (event.pressed ?
                        MACRO( D(LSHIFT), D(9), U(9), U(LSHIFT), END ) : MACRO_NONE);
            } else {
                return (event.pressed ?
                        MACRO( D(LSHIFT), END ) : MACRO( U(LSHIFT), END ) );
            }
        case RSHIFT_PAREN:
            if (tap.count > 0 && !tap.interrupted) {
                return (event.pressed ?

                        MACRO( D(RSHIFT), D(0), U(0), U(RSHIFT), END ) : MACRO_NONE);
            } else {
                return (event.pressed ?
                        MACRO( D(RSHIFT), END ) : MACRO( U(RSHIFT), END ) );
            }
    }
    return MACRO_NONE;
}



/*
 * user defined action function
 */
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    keyevent_t event = record->event;
    bool isLShiftPressed;
    bool isRShiftPressed;
    bool isLAltPressed;
    bool isRAltPressed;
    bool isLShiftOneShotted;
    int shiftOneShot;

    switch (id) {
        case SCLN_SWAP:
            if (event.pressed) {
              xprintf("FN SCLN_SWAP \n");

              isLShiftPressed = get_mods() == MOD_BIT(KC_LSHIFT);
              isRShiftPressed = get_mods() == MOD_BIT(KC_RSHIFT);
              isLAltPressed = get_mods() == MOD_BIT(KC_LALT);
              isRAltPressed = get_mods() == MOD_BIT(KC_RALT);
              shiftOneShot = 1280 + MOD_BIT(KC_LSHIFT);
              isLShiftOneShotted = get_oneshot_mods() == shiftOneShot;

              xprintf("%d\n", shiftOneShot);
              xprintf("%d\n", get_oneshot_mods());


              if ( isLAltPressed == false && isRAltPressed == false ) {
                if ( isRShiftPressed ) { del_mods(MOD_BIT(KC_RSHIFT)); }
                else if ( isLShiftPressed == false && isLShiftOneShotted == false) { add_mods(MOD_BIT(KC_LSHIFT)); }
                else if ( isLShiftPressed ) { del_mods(MOD_BIT(KC_LSHIFT)); }
                else if ( isLShiftOneShotted ) { clear_oneshot_mods(); }
              }

              add_key(KC_SCLN);
              send_keyboard_report();

              if ( isLAltPressed == false && isRAltPressed == false ) {
                if ( isRShiftPressed ) { add_mods(MOD_BIT(KC_RSHIFT)); }
                else if ( isLShiftPressed == false ) { del_mods(MOD_BIT(KC_LSHIFT)); }
                else if ( isLShiftPressed ) { add_mods(MOD_BIT(KC_LSHIFT)); }
              }

              del_key(KC_SCLN);
              send_keyboard_report();
            }
            break;
    }
}
