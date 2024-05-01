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

// LT
#define LT3_ENT LT(3, KC_ENT)
#define LT1_SPC LT(1, KC_SPC)
#define LT2_SCLN LT(2, KC_SCLN)
#define LT5_TAB LT(5, KC_TAB)
#define LT4_SPC LT(4, KC_SPC)

// simple KC
#define XXXXX KC_NO

// mod + kc
#define LBRC KC_RBRC // [
#define SFT_LBRC LSFT(KC_RBRC) // {
#define RBRC KC_BSLS // ]
#define LBRC KC_RBRC // [
#define SFT_RBRC LSFT(KC_BSLS) // }
#define BSLSH LALT(KC_INT3)
#define EQL LSFT(KC_MINUS)
#define TILDE LSFT(KC_EQL) // ~
#define UNDERBAR KC_INT1
#define CARET KC_EQL // ^
#define YEN KC_INT3 // ¥
#define PIPE LSFT(KC_INT3) // |
#define AT KC_LBRC //@
#define CLN KC_QUOTE //:
#define M_F1 RCTL(KC_F1)
#define M_F2 RCTL(KC_F2)
#define M_F3 RCTL(KC_F3)
#define M_F4 RCTL(KC_F4)
#define M_F5 RCTL(KC_F5)
#define M_F6 RCTL(KC_F6)
#define M_F7 RCTL(KC_F7)
#define M_F8 RCTL(KC_F8)
#define M_F9 RCTL(KC_F9)
#define M_F10 RCTL(KC_F10)
#define M_F11 RCTL(KC_F11)
#define M_F12 RCTL(KC_F12)

// short cut command
#define COPY LGUI(KC_C)
#define PASTE LGUI(KC_V)
#define CUT LGUI(KC_X)
#define S_ALL LGUI(KC_A)
#define CLOSE LGUI(KC_W)
#define NEW_TAB LGUI(KC_T)
#define UNDO LGUI(KC_Z)
#define REDO LGUI(LSFT(KC_Z))
#define QUIT LGUI(KC_Q)
#define FIND LGUI(KC_F)
#define SAVE LGUI(KC_S)
#define MEMO RCTL(KC_Q)
#define MIS_CON LCTL(KC_UP)
#define APP_CON LCTL(KC_DOWN)
#define CTR_L LCTL(KC_LEFT)
#define CTR_R LCTL(KC_RIGHT)
#define ZOOM LM(4, MOD_LCTL) //zoom
#define GUI_L LGUI(KC_LEFT)
#define GUI_R LGUI(KC_RIGHT)
#define TAB_R LCTL(KC_TAB)
#define TAB_L C(S(KC_TAB))
#define OP_CLO_T G(S(KC_T))
#define SLEEP A(G(KC_Q))
#define ZOOM_IN LGUI(LSFT(KC_SCLN))
#define ZOOM_OUT LGUI(KC_MINUS)


// mod tap
#define MT_DOT_S MT(MOD_LSFT, KC_KP_DOT)
#define MT_DOT_G MT(MOD_LGUI, KC_KP_DOT)
#define MT_KANA_C MT(MOD_LCTL, KC_LNG1)
#define MT_EISU_S MT(MOD_LSFT, KC_LNG2)
#define MT_0_GUI MT(MOD_LGUI, KC_KP_0)
#define MT_0_SFT MT(MOD_LSFT, KC_KP_0)
#define MT_BS_GU MT(MOD_LGUI, KC_BSPC)
#define MT_MUT_S MT(MOD_LSFT, KC_MUTE)
#define MT_ESC_C MT(MOD_LCTL, KC_ESC)


// mousekey
#define LCLICK KC_BTN1
#define RCLICK KC_BTN2
#define CCLICK KC_BTN3
#define CCLICK KC_BTN3


// home end
#define L_END LCTL(KC_A)
#define R_END LCTL(KC_E)

// カスタムキーコード
enum custom_keycodes {
    M_U_4X = KEYBALL_SAFE_RANGE,
    M_D_4X,
    M_L_4X,
    M_R_4X
};

//キーコンボ関連1
//------------------------------
enum combos {
//  // かな
//  DF_LNG2,
//  // 英数
//  JK_LNG1,
//  EF_ESC,
//  O_SCLN_BS,
//  AW_TAB,
  OP_AT, // @
  L_SCLN_CLN, // :
//  I_L_DELz
  T_G_C_L, // go to left desktop
  T_G_C_R, // go to right desktop
  RL_CLICK // middle click
};

//キーコンボ関連2
//const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
//const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
//const uint16_t PROGMEM ef_combo[] = {KC_E, KC_F, COMBO_END};
//const uint16_t PROGMEM oscln_combo[] = {KC_O, LT2_SCLN, COMBO_END};
//const uint16_t PROGMEM aw_combo[] = {KC_A, KC_W, COMBO_END};
const uint16_t PROGMEM op_combo[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM lscln_combo[] = {KC_L, LT2_SCLN, COMBO_END};
//const uint16_t PROGMEM il_combo[] = {KC_I, KC_L, COMBO_END};
const uint16_t PROGMEM tgc_l_combo[] = {TAB_L, GUI_L, COMBO_END};
const uint16_t PROGMEM tgc_r_combo[] = {TAB_R, GUI_R, COMBO_END};
const uint16_t PROGMEM rl_click_combo[] = {LCLICK, RCLICK, COMBO_END};

//キーコンボ関連3
combo_t key_combos[COMBO_COUNT] = {
//  [DF_LNG2] = COMBO(df_combo, KC_LNG2),
//  [JK_LNG1] = COMBO(jk_combo, KC_LNG1),
//  [EF_ESC] = COMBO(ef_combo, KC_ESC),
//  [O_SCLN_BS] = COMBO(oscln_combo, KC_BSPC),
//  [AW_TAB] = COMBO(aw_combo, KC_TAB),
  [OP_AT] = COMBO(op_combo, AT),
  [L_SCLN_CLN] = COMBO(lscln_combo, CLN),
//  [I_L_DEL] = COMBO(il_combo, KC_DEL)
  [T_G_C_L] = COMBO(tgc_l_combo, CTR_L),
  [T_G_C_R] = COMBO(tgc_r_combo, CTR_R),
  [RL_CLICK] = COMBO(rl_click_combo, CCLICK)
};
//------------------------------

//------------------------------
//オーバーライド
//const key_override_t bs_key_override = ko_make_basic(MOD_MASK_CTRL, KC_A, KC_H);
//const key_override_t **key_overrides = (const key_override_t *[]){
//    &bs_key_override,
//    NULL // Null terminate the array of overrides
//    };

//------------------------------

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  [0] = LAYOUT_universal(
 //,-----------------------------------------------------------.                         ,------------------------------------------------------------
     KC_Q      , KC_W      , KC_E      , KC_R      , KC_T      ,                           KC_Y      , KC_U      , KC_I      , KC_O      , KC_P      ,
 //,-----------+-----------+-----------+-----------+-----------.                         ,-----------+-----------+-----------+-----------+------------
     KC_A      , KC_S      , KC_D      , KC_F      , KC_G      ,                           KC_H      , KC_J      , KC_K      , KC_L      , LT2_SCLN  ,
 //,-----------+-----------+-----------+-----------+-----------.                         ,-----------+-----------+-----------+-----------+------------
     KC_Z      , KC_X      , KC_C      , KC_V      , KC_B      ,                           KC_N      , KC_M      , KC_COMM   , KC_DOT    , KC_SLSH   ,
 //,-----------+-----------+-----------+-----------+-----------+----------.    ,---------+-----------+-----------+-----------+-----------+------------
     LT5_TAB   , KC_LALT   , MT_ESC_C  , MT_BS_GU  , MT_EISU_S , LT1_SPC  ,     LT3_ENT  , MT_KANA_C , XXXXXXX   , XXXXXXX   , XXXXXXX   , KC_MINUS
 //,----------------------------------------------------------------------.    ,----------------------------------------------------------------------
  ),

  [1] = LAYOUT_universal(
 //,-----------------------------------------------------------.                         ,------------------------------------------------------------
     KC_1      , KC_2      , KC_3      , KC_4      , KC_5      ,                           KC_6      , KC_7      , KC_8      , KC_9      , KC_0      ,
 //,-----------+-----------+-----------+-----------+-----------.                         ,-----------+-----------+-----------+-----------+------------
     LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5),                           LSFT(KC_6), LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), EQL       ,
 //,-----------+-----------+-----------+-----------+-----------.                         ,-----------+-----------+-----------+-----------+------------
     CARET     , TILDE     , PIPE      , YEN       , BSLSH     ,                           LBRC      , RBRC      , SFT_LBRC  , SFT_RBRC  , UNDERBAR  ,
 //,-----------+-----------+-----------+-----------+-----------+----------.    ,---------+-----------+-----------+-----------+-----------+------------
     _______   , _______   , _______   , KC_LGUI   , KC_LSFT   , _______,        _______,  KC_LCTL   , XXXXX     , XXXXX     , XXXXX     , KC_MINUS
 //,----------------------------------------------------------------------.    ,----------------------------------------------------------------------
  ),

  [2] = LAYOUT_universal(
 //,-----------------------------------------------------------.                         ,------------------------------------------------------------
     QUIT      , CLOSE     , XXXXX     , OP_CLO_T  , NEW_TAB   ,                           ZOOM_IN   , ZOOM      , KC_PGDN   , KC_PGUP   , KBC_SAVE  ,
 //,-----------+-----------+-----------+-----------+-----------.                         ,-----------+-----------+-----------+-----------+------------
     S_ALL     , SAVE      , XXXXX     , FIND      , XXXXX     ,                           ZOOM_OUT  , LCLICK    , RCLICK    , MO(4)     , _______   ,
 //,-----------+-----------+-----------+-----------+-----------.                         ,-----------+-----------+-----------+-----------+------------
     UNDO      , CUT       , COPY      , PASTE     , REDO      ,                           TAB_L     , GUI_L     , GUI_R     , TAB_R     , KBC_RST   ,
 //,-----------+-----------+-----------+-----------+-----------+----------.    ,---------+-----------+-----------+-----------+-----------+------------
     M_F10     , M_F11     , M_F12     , KC_VOLD   , MT_MUT_S  , KC_VOLU,        APP_CON , MIS_CON   , XXXXX     , XXXXX     , XXXXX     , SLEEP
 //,----------------------------------------------------------------------.    ,----------------------------------------------------------------------
  ),

  [3] = LAYOUT_universal(
 //,-----------------------------------------------------------.                         ,------------------------------------------------------------
     KC_BSPC   , KC_KP_7   , KC_KP_8   , KC_KP_9   , KC_PPLS   ,                           L_END     , KC_PGDN   , KC_PGUP   , R_END     , KC_HOME   ,
 //,-----------+-----------+-----------+-----------+-----------.                         ,-----------+-----------+-----------+-----------+------------
     KC_TAB    , KC_KP_4   , KC_KP_5   , KC_KP_6   , KC_PMNS   ,                           KC_LEFT   , KC_DOWN   , KC_UP     , KC_RIGHT  , KC_END    ,
 //,-----------+-----------+-----------+-----------+-----------.                         ,-----------+-----------+-----------+-----------+------------
     KC_PSLS   , KC_KP_1   , KC_KP_2   , KC_KP_3   , KC_PAST   ,                           M_L_4X    , M_D_4X    , M_U_4X    , M_R_4X    , XXXXX     ,
 //,-----------+-----------+-----------+-----------+-----------+----------.    ,---------+--j---------+-----------+-----------+-----------+------------
     UNDERBAR  , _______   , _______   , MT_0_GUI  , MT_DOT_S  , LT4_SPC ,       _______,  _______   , XXXXX     , XXXXX     , XXXXX     , XXXXX
 //,----------------------------------------------------------------------.    ,----------------------------------------------------------------------
  ),

  [4] = LAYOUT_universal(
 //,-----------------------------------------------------------.                         ,------------------------------------------------------------
     KBC_SAVE  , XXXXX     , SCRL_DVD  , CPI_I100  , CPI_I1K   ,                           XXXXX     , XXXXX     , XXXXX     , XXXXX     , XXXXX     ,
 //,-----------+-----------+-----------+-----------+-----------.                         ,-----------+-----------+-----------+-----------+------------
     XXXXX     , XXXXX     , SCRL_DVI  , CPI_D100  , CPI_D1K   ,                           M_L_4X    , M_D_4X    , M_U_4X    , M_R_4X    , _______   ,
 //,-----------+-----------+-----------+-----------+-----------.                         ,-----------+-----------+-----------+-----------+------------
     XXXXX     , XXXXX     , XXXXX     , XXXXX     , XXXXX     ,                           XXXXX     , XXXXX     , XXXXX     , XXXXX     , XXXXX     ,
 //,-----------+-----------+-----------+-----------+-----------+----------.    ,---------+-----------+-----------+-----------+-----------+------------
     KBC_RST   , XXXXX     , XXXXX     , KC_MRWD   , KC_MPLY   , KC_MFFD,        XXXXX  ,  XXXXX     , XXXXX     , XXXXX     , XXXXX     , XXXXX
 //,----------------------------------------------------------------------.    ,----------------------------------------------------------------------
  ),

  [5] = LAYOUT_universal(
 //,-----------------------------------------------------------.                         ,------------------------------------------------------------
     M_F1      , M_F2      , M_F3      , M_F4      , M_F5      ,                           _______   , _______   , _______   , _______   , KC_BSPC   ,
 //,-----------+-----------+-----------+-----------+-----------.                         ,-----------+-----------+-----------+-----------+------------
     M_F6      , M_F7      , M_F8      , M_F9      , M_F10     ,                           _______   , _______   , _______   , _______   , KC_ESC    ,
 //,-----------+-----------+-----------+-----------+-----------.                         ,-----------+-----------+-----------+-----------+------------
     M_F11     , M_F12     , _______   , _______   , _______   ,                           _______   , _______   , _______   , _______   , KC_TAB    ,
 //,-----------+-----------+-----------+-----------+-----------+----------.    ,---------+-----------+-----------+-----------+-----------+------------
     _______   , _______   , _______   , _______   , _______   , _______,        _______,  _______   , _______   , _______   , _______   , MEMO
 //,----------------------------------------------------------------------.    ,----------------------------------------------------------------------
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 4);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
}
#endif


//マクロに使用する関数
//------------------------------
void tap_key_times(uint16_t keycode, uint8_t times, uint16_t delay) {
  for (uint8_t i = 0; i < times; i++) {
    tap_code(keycode);
    if (i < times - 1) {
      wait_ms(delay);
    }
  }
}

//bool btn1_pressed = true;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool ctrl_held = false;
    if (keycode == KC_LCTL || keycode == KC_RCTL || keycode == MT_KANA_C || keycode == MOD_LCTL) {
        // Ctrlキーが押された場合
        if (record->event.pressed) {
            ctrl_held = true;
        } else {
            ctrl_held = false;
        }
    }
    if (keycode == KC_H && record->event.pressed && ctrl_held) {
        // Ctrlキーが押された状態でHキーが押された場合
        unregister_code(KC_LCTL);
        unregister_code(KC_RCTL);
        register_code(KC_BSPC);
        unregister_code(KC_BSPC);
        register_code(KC_LCTL); // もし左Ctrlキーが元々押されていた場合、再度登録
        return false; // 通常のキー処理をスキップ
    }

    if (record->event.pressed) {

        //マクロキーの設定
        switch (keycode) {
            case M_U_4X:
                tap_key_times(KC_UP, 4, 20);
                return false; // 通常のキー処理をスキップ
            case M_D_4X:
                tap_key_times(KC_DOWN, 4, 20);
                return false; // 通常のキー処理をスキップ
            case M_L_4X:
                tap_key_times(KC_LEFT, 4, 20);
                return false; // 通常のキー処理をスキップ
            case M_R_4X:
                tap_key_times(KC_RIGHT, 4, 20);
                return false; // 通常のキー処理をスキップ
                              //以下を使う場合は ../../rule.mkの MOUSE_KEY_ENABLE = yesが必要
                              //case BTN1_TG:
                              //  btn1_pressed = !btn1_pressed;
                              //  if (btn1_pressed) {
                              //      register_code(KC_MS_BTN1);
                              //  } else {
                              //      unregister_code(KC_MS_BTN1);
                              //  }
                              //return false; // 通常のキー処理をスキップ
                              //break;

        }
    }
    return true;
}

//------------------------------
