// keyball44
/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"
#include "toxa_keycode.h"


// layer_names------------------------------
enum layer_names {
    _DEF = 0,
    _FUNC,
    _SYM,
    _NUM,
    _MOUSE,
    _ADJ,
    _CUR2
};


// LT------------------------------
#define SYM_SPC LT(_SYM, KC_SPC)
#define MOU_SCLN LT(_MOUSE, KC_SCLN)
#define NUM_ENT LT(_NUM, KC_ENT)
#define CUR2_DOT LT(_CUR2, KC_KP_DOT)
#define MOU_AST LT(_MOUSE, KC_PAST)
#define FUNC_BS LT(_FUNC, KC_BSPC)


// カスタムキーコード------------------------------
enum custom_keycodes {
    SPD_UP = KEYBALL_SAFE_RANGE
};


// マクロ用変数------------------------------
// SPD_UP用
static bool spd_up = false;
static int arrow_count = 0;
enum arrow_held {
    NONE = 0,
    UP,
    RIGHT,
    LEFT,
    DOWN
};
enum arrow_held arrow_held = NONE;

// Ctrl+h用
static bool ctrl_held = false;
static bool ctrl_h_held = false;
static int ctrl_held_delay = 0;

#define M_REPEAT_TH 300


//キーコンボ関連1------------------------------
//*変更する際はconfig.hの記載も忘れないこと
enum combos {
    RL_CLICK, // middle click
    S_RL_CLICK
};

//キーコンボ関連2
const uint16_t PROGMEM rl_click_combo[] = {L_CLICK, R_CLICK, COMBO_END};
const uint16_t PROGMEM s_rl_click_combo[] = {KC_MPLY, KC_MFFD, COMBO_END};

//キーコンボ関連3
combo_t key_combos[COMBO_COUNT] = {
  [RL_CLICK] = COMBO(rl_click_combo, M_CLICK),
  [S_RL_CLICK] = COMBO(s_rl_click_combo, LSFT(M_CLICK))
};


// タップダンス------------------------------
// ※一旦不使用（便利ではあった。使う時があった場合の資料として記載）
/*
enum {
  T_MA = 0, // mission control とapplication control
  T_BR, // () と {}
  T_BL,
  T_SBR, // <> と []
  T_SBL
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [T_MA] = ACTION_TAP_DANCE_DOUBLE(MIS_CON, APP_CON),
    [T_BR] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_9), R_BRC),
    [T_BL] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_8), L_BRC),
    [T_SBR] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_DOT), R_SQBR),
    [T_SBL] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_COMM), L_SQBR)
};
*/
//------------------------------

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  // デフォルトレイヤー
  [_DEF] = LAYOUT_universal(
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    ESC_A     , KC_Q      , KC_W      , KC_E      , KC_R      , KC_T      ,                               KC_Y      , KC_U      , KC_I      , KC_O      , KC_P      , AT_A      ,
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    TAB_C     , KC_A      , KC_S      , KC_D      , KC_F      , KC_G      ,                               KC_H      , KC_J      , KC_K      , KC_L      , MOU_SCLN  , CLN_C     ,
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    UNDERB_S  , Z_GUI     , KC_X      , KC_C      , KC_V      , KC_B      ,                               KC_N      , KC_M      , KC_COMM   , KC_DOT    , SLSH_GUI  , MINUS_S   ,
//,-----------+-----------+-----------+-----------+-----------+-----------+-----------.     ,-----------+-----------+-----------+-----------+-----------+-----------+-----------.
                            BSLSH     , KC_RCTL   , FUNC_BS   , EISU_S    , SYM_SPC   ,       NUM_ENT   , KANA_C    , XXXXXXX   , XXXXXXX   ,             TG(_FUNC)
//,-----------------------------------------------------------------------------------.     ,-----------------------------------------------------------------------------------.
  ),

  //ファンクションレイヤー
  [_FUNC] = LAYOUT_universal(
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    SCSH_3    , M_F1      , M_F2      , M_F3      , M_F4      , M_F5      ,                               KC_MINUS  , KC_7      , KC_8      , KC_9      , KC_PSLS   , KC_BSPC   ,
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    SCSH_4    , M_F6      , M_F7      , M_F8      , M_F9      , M_F10     ,                               KC_0      , KC_4      , KC_5      , KC_6      , MOU_AST   , KC_TAB    ,
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    SCSH_5    , M_F11     , M_F12     , XXXXX     , XXXXX     , XXXXX     ,                               KC_DOT    , KC_1      , KC_2      , KC_3      , KC_PPLS   , KC_SPC    ,
//,-----------+-----------+-----------+-----------+-------_----+-----------+----------.     ,-----------+-----------+-----------+-----------+-----------+-----------+-----------.
                            EJECT_SSD , XXXXX     , _______   , XXXXX     , XXXXX     ,       NUM_ENT   , KC_0      , XXXXXXX   , XXXXXXX   ,             TG(_FUNC)
//,-----------------------------------------------------------------------------------.     ,-----------------------------------------------------------------------------------.
  ),

  //記号レイヤー
  [_SYM] = LAYOUT_universal(
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    KC_LALT   , LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5),                               LSFT(KC_6), LSFT(KC_7), L_PAREN   , R_PAREN   , BSLSH     , BACK_QUO  ,
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    KC_LCTL   , XXXXX     , XXXXX     , L_BRC     , R_BRC     , XXXXX     ,                               CARET     , TILDE     , PIPE      , DOLLAR    , PLUS      , AST       ,
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    KC_LSFT   , KC_LGUI   , XXXXX     , L_SQBR    , R_SQBR    , XXXXX     ,                               XXXXX     , XXXXX     , LESS      , MORE      , QUESTION  , EQL       ,
//,-----------+-----------+-----------+-----------+-----------+-----------+-----------.     ,-----------+-----------+-----------+-----------+-----------+-----------+-----------.
                            YEN       , _______   , _______   , KC_LSFT   , _______   ,       XXXXX     , XXXXX     , XXXXXXX   , XXXXXXX   ,             XXXXX  
//,-----------------------------------------------------------------------------------.     ,-----------------------------------------------------------------------------------.
  ),

  //数字/カーソルレイヤー
  [_NUM] = LAYOUT_universal(
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    KC_LALT   , XXXXX     , KC_7      , KC_8      , KC_9      , KC_MINUS  ,                               HOME      , KC_PGDN   , KC_PGUP   , END       , XXXXX     , XXXXX     ,
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    KC_TAB    , XXXXX     , KC_4      , KC_5      , KC_6      , KC_0      ,                               KC_LEFT   , KC_DOWN   , KC_UP     , KC_RIGHT  , XXXXX     , XXXXX     ,
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    KC_LSFT   , KC_LGUI   , KC_1      , KC_2      , KC_3      , KC_DOT    ,                               XXXXX     , XXXXX     , XXXXX     , XXXXX     , XXXXX     , XXXXX     ,
//,-----------+-----------+-----------+-----------+-----------+-----------+-----------.     ,-----------+-----------+-----------+-----------+-----------+-----------+-----------.
                            KC_LALT   , _______   , KC_0      , KC_DOT    , SPD_UP    ,       _______   , M_F2      , XXXXXXX   , XXXXXXX   ,             _______
//,-----------------------------------------------------------------------------------.     ,-----------------------------------------------------------------------------------.
  ),

  //マウスレイヤー
  [_MOUSE] = LAYOUT_universal(
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    XXXXX     , XXXXX     , XXXXX     , KC_PGUP   , RELOAD    , NEW_TAB   ,                               MORE      , M_CLICK   , S(M_CLICK), MIS_CON   , KBC_SAVE  , LAST_TAB  ,
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    XXXXX     , S_ALL     , SAVE      , KC_PGDN   , FIND      , LAST_TAB  ,                               LESS      , L_CLICK   , R_CLICK   , MO(_ADJ)  , _______   , NEW_TAB   ,
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    XXXXX     , UNDO      , CUT       , COPY      , PASTE     , REDO      ,                               TAB_L     , BACK      , FORWARD   , TAB_R     , KBC_RST   , CLOSE     ,
//,-----------+-----------+-----------+-----------+-----------+-----------+-----------.     ,-----------+-----------+-----------+-----------+-----------+-----------+-----------.
                            XXXXX     , XXXXX     , DELETE    , KC_LSFT   , SPOT_L    ,       DESK_L    , DESK_R    , XXXXXXX   , XXXXXXX   ,             SLEEP
//,-----------------------------------------------------------------------------------.     ,-----------------------------------------------------------------------------------.
  ),

  //アジャストレイヤー
  [_ADJ] = LAYOUT_universal(
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    RGB_MOD   , XXXXX     , XXXXX     , SCRL_DVD  , CPI_I100  , CPI_I1K   ,                               ZOOM_IN   , KC_VOLU   , KC_MUTE   , XXXXX     , XXXXX     , _______   ,
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    RGB_RMOD  , XXXXX     , XXXXX     , SCRL_DVI  , CPI_D100  , CPI_D1K   ,                               KC_MRWD   , KC_MPLY   , KC_MFFD   , _______   , _______   , _______   ,
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    RGB_M_B   , XXXXX     , XXXXX     , XXXXX     , XXXXX     , XXXXX     ,                               ZOOM_OUT  , KC_VOLD   , XXXXX     , XXXXX     , XXXXX     , _______   ,
//,-----------+-----------+-----------+-----------+-----------+-----------+-----------.     ,-----------+-----------+-----------+-----------+-----------+-----------+-----------.
                            XXXXX     , XXXXX     , XXXXX     , XXXXX     , XXXXX     ,       XXXXX     , XXXXX     , XXXXXXX   , XXXXXXX   ,             XXXXX
//,-----------------------------------------------------------------------------------.     ,-----------------------------------------------------------------------------------.
  ),
  
  //カーソル2
  [_CUR2] = LAYOUT_universal(
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    XXXXX     , XXXXX     , XXXXX     , XXXXX     , XXXXX     , XXXXX     ,                               XXXXX     , XXXXX     , XXXXX     , XXXXX     , XXXXX     , _______   ,
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    XXXXX     , XXXXX     , XXXXX     , XXXXX     , XXXXX     , XXXXX     ,                               XXXXX     , XXXXX     , XXXXX     , XXXXX     , _______   , _______   ,
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    XXXXX     , XXXXX     , XXXXX     , XXXXX     , XXXXX     , XXXXX     ,                               XXXXX     , XXXXX     , XXXXX     , XXXXX     , XXXXX     , _______   ,
//,-----------+-----------+-----------+-----------+-----------+-----------+-----------.     ,-----------+-----------+-----------+-----------+-----------+-----------+-----------.
                            XXXXX     , XXXXX     , XXXXX     , XXXXX     , XXXXX     ,      XXXXX     , XXXXX     , XXXXXXX   , XXXXXXX   ,             XXXXX
//,-----------------------------------------------------------------------------------.     ,-----------------------------------------------------------------------------------.
  ),

};


// clang-format on


// layer state setting ------------------------------
layer_state_t layer_state_set_user(layer_state_t state) {
    
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 5);
    
    //LED------------------------------
    uint8_t layer = biton32(state);
    switch (layer) {
        case _DEF:
            rgblight_sethsv(HSV_CYAN);
            break;
        case _SYM:
            rgblight_sethsv(HSV_BLUE);
            break;
        case _NUM:
            rgblight_sethsv(HSV_CHARTREUSE);
            break;
        case _MOUSE:
            rgblight_sethsv(HSV_PURPLE);
            break;
        case _ADJ:
            rgblight_sethsv(HSV_GOLDENROD);
            break;
        case _FUNC:
            rgblight_sethsv(HSV_CORAL);
            break;
        case _CUR2:
            rgblight_sethsv(HSV_MAGENTA);
            break;
    }

    return state;
}


// oled setting ------------------------------
#ifdef OLED_ENABLE
#    include "lib/oledkit/oledkit.h"

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _DEF:
            oled_write_ln_P(PSTR("Default   "), false);
            break;
        case _SYM:
            oled_write_ln_P(PSTR("Symbol    "), false);
            break;
        case _NUM:
            oled_write_ln_P(PSTR("Num/Cursor"), false);
            break;
        case _MOUSE:
            oled_write_ln_P(PSTR("Mouse     "), false);
            break;
        case _ADJ:
            oled_write_ln_P(PSTR("Adjust    "), false);
            break;
        case _FUNC:
            oled_write_ln_P(PSTR("Func/Num  "), false);
            break;
        case _CUR2:
            oled_write_ln_P(PSTR("Cursor2   "), false);
            break;
    }
}
/*
static const char *format_4d(int d) {
    static char buf[5] = {0}; // max width (4) + NUL (1)
    char        lead   = ' ';
    if (d < 0) {
        d    = -d;
        lead = '-';
    }
    buf[3] = (d % 10) + '0';
    d /= 10;
    if (d == 0) {
        buf[2] = lead;
        lead   = ' ';
    } else {
        buf[2] = (d % 10) + '0';
        d /= 10;
    }
    if (d == 0) {
        buf[1] = lead;
        lead   = ' ';
    } else {
        buf[1] = (d % 10) + '0';
        d /= 10;
    }
    buf[0] = lead;
    return buf;
}
*/
void oledkit_render_info_user(void) {
    oled_render_layer_state();
//    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
//    oled_write_P(PSTR("arrow_count: "),false);
//    oled_write(format_4d(arrow_count), false);
}
#endif


// my keycode process setting------------------------------
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode){
        
            case SPD_UP:
                if (record->event.pressed) {
                    spd_up = true;
                } else {
                    spd_up = false;
                    switch(arrow_held) {
                        case RIGHT:
                            register_code(KC_RIGHT);
                        break;
                        case LEFT:
                            register_code(KC_LEFT);
                        break;
                        case UP:
                            register_code(KC_UP);
                        break;
                        case DOWN:
                            register_code(KC_DOWN);
                        break;
                        case NONE:
                        break;
                    }
                }
                break;
            case KC_RIGHT:
                if (record->event.pressed){
                    arrow_held = RIGHT;
                    arrow_count++;
                        return true;
                } else {
                    arrow_count--;
                    unregister_code(KC_RIGHT);
                    if (arrow_count == 0){
                        arrow_held = NONE;
                    }
                }
                break;
            case KC_LEFT:
                if (record->event.pressed){
                    arrow_held = LEFT;
                    arrow_count++;
                        return true;
                } else {
                    arrow_count--;
                    unregister_code(KC_LEFT);
                    if (arrow_count == 0){
                        arrow_held = NONE;
                    }
                }
                break;
            case KC_UP:
                if (record->event.pressed){
                    arrow_held = UP;
                    arrow_count++;
                        return true;
                } else {
                    arrow_count--;
                    unregister_code(KC_UP);
                    if (arrow_count == 0){
                        arrow_held = NONE;
                    }
                }
                break;
            case KC_DOWN:
                if (record->event.pressed){
                    arrow_held = DOWN;
                    arrow_count++;
                        return true;
                } else {
                    arrow_count--;
                    unregister_code(KC_DOWN);
                    if (arrow_count == 0){
                        arrow_held = NONE;
                    }
                }
                break;
        // ctrl+h backspace------------------------------
            case KC_LCTL:
            case MOD_LCTL:
            case KANA_C:
            case TAB_C:
            case CLN_C:
                if (record->event.pressed){
                    ctrl_held = true;
                }else{
                    ctrl_held = false;
                    ctrl_h_held = false;
                }
                return true;
            case KC_H:
                if (record->event.pressed && ctrl_held){
                    ctrl_h_held = true;
                    return false;
                }else{
                    ctrl_h_held = false;
                    ctrl_held_delay = 0;
                    return true;
                }

        /*
        // MTで対応しきれないキーコードの対処法
        // docに記載あり
            case LSFT_T(DESK_R):
            if (record->tap.count && record->event.pressed) {
                tap_code16(DESK_R); // Send KC_DQUO on tap
                return false;        // Return false to ignore further processing of key
            }
            break;
        */

    }
    return true;
}

//-------------------------------------------------------------
//  matrix_scan_user関数の中でフラグをチェックして必要なマクロを実行する。
//  この関数はQMKががキーの押下をチェックするたび実行される。
//  https://gist.github.com/ypsilon-takai/c4a249087ea19eabd1deb3f9f273de52
//

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    if (spd_up) {
        switch(arrow_held) {
            case RIGHT:
                SEND_STRING(SS_TAP(X_RIGHT)SS_TAP(X_RIGHT)SS_DELAY(20));
            break;
            case LEFT:
                SEND_STRING(SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_DELAY(20));
            break;
            case UP:
                SEND_STRING(SS_TAP(X_UP)SS_TAP(X_UP)SS_DELAY(20));
            break;
            case DOWN:
                SEND_STRING(SS_TAP(X_DOWN)SS_TAP(X_DOWN)SS_DELAY(20));
            break;
            case NONE:
            break;
        }
    }

    if (ctrl_h_held) {
        if (ctrl_held_delay == 0) {
            unregister_code(KC_LCTL);
            register_code(KC_BSPC);
            unregister_code(KC_BSPC);
            register_code(KC_LCTL); // もし左Ctrlキーが元々押されていた場合、再度登録
        }
        if (ctrl_held_delay > M_REPEAT_TH) {
            unregister_code(KC_LCTL);
            SEND_STRING(SS_TAP(X_BSPC)SS_DELAY(20));
            register_code(KC_LCTL);
        }
        ctrl_held_delay++;
    }

};
