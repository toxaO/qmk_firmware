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

// LT
#define LT3_ENT LT(3, KC_ENT)
#define LT1_SPC LT(1, KC_SPC)
#define LT2_SCLN LT(2, KC_SCLN)
#define LT5_TAB LT(5, KC_TAB)
#define LT4_SPC LT(4, KC_SPC)
#define LT4_DOT LT(4, KC_KP_DOT)
#define LT5_SLSH LT(5, KC_SLSH)

// simple KC
#define XXXXX KC_NO

// mod + kc
#define SQ_LBRC KC_RBRC // [
#define LBRC LSFT(KC_RBRC) // {
#define SQ_RBRC KC_BSLS // ]
#define RBRC LSFT(KC_BSLS) // }
#define BSLSH LALT(KC_INT3)
#define EQL LSFT(KC_MINUS)
#define TILDE LSFT(KC_EQL) // ~
#define UNDERBAR KC_INT1
#define CARET KC_EQL // ^
#define YEN KC_INT3 // ¥
#define PIPE LSFT(KC_INT3) // |
#define AT KC_LBRC //@
#define CLN KC_QUOTE //:
#define LESS LSFT(KC_COMM) // <
#define MORE LSFT(KC_DOT) // >
#define QUESTION LSFT(KC_SLSH) // ?
#define PLUS LSFT(KC_SCLN) // +
#define CLN KC_QUOTE // :
#define AST LSFT(KC_QUOTE) // *
#define BACK_QUO LSFT(AT) // ``

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

#define ALT_GUI A(KC_LGUI)

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
#define SPOT_L LGUI(KC_SPC)
#define RELOAD LGUI(KC_R)
#define SCSH_3 LSG(KC_3)
#define SCSH_4 LSG(KC_4)
#define SCSH_5 LSG(KC_5)


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
#define MT_TAB_G MT(MOD_LGUI, KC_TAB)
#define MT_ESC_G MT(MOD_LGUI, KC_ESC)
#define MT_AT_AG LAG_T(AT)
#define MT_CL_G MT(MOD_LGUI, CLN)
#define MT_MI_A MT(MOD_LALT, KC_MINUS)
#define MT_ES_AG LAG_T(KC_ESC)
#define CARET_AG LAG_T(CARET)
#define TILDE_G LGUI_T(TILDE)
#define UNDERB_A LALT_T(UNDERBAR)
#define VOLU_AG LAG_T(KC_VOLU)
#define MUTE_G LGUI_T(KC_MUTE)
#define VOLD_A LALT_T(KC_VOLD)
#define F_CTL LCTL_T(KC_F)
#define J_SFT LSFT_T(KC_J)


// mousekey
#define LCLICK KC_BTN1
#define RCLICK KC_BTN2
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
  T_G_C_L, // go to left desktop
  T_G_C_R, // go to right desktop
  RL_CLICK, // middle click
  S_M_CLICK // sft middle click
};

//キーコンボ関連2
const uint16_t PROGMEM tgc_l_combo[] = {TAB_L, GUI_L, COMBO_END};
const uint16_t PROGMEM tgc_r_combo[] = {TAB_R, GUI_R, COMBO_END};
const uint16_t PROGMEM rl_click_combo[] = {LCLICK, RCLICK, COMBO_END};
const uint16_t PROGMEM s_m_click_combo[] = {GUI_L, GUI_R, COMBO_END};

//キーコンボ関連3
combo_t key_combos[COMBO_COUNT] = {
  [T_G_C_L] = COMBO(tgc_l_combo, CTR_L),
  [T_G_C_R] = COMBO(tgc_r_combo, CTR_R),
  [RL_CLICK] = COMBO(rl_click_combo, CCLICK),
  [S_M_CLICK] = COMBO(s_m_click_combo, LSFT(CCLICK))
};
//------------------------------

// タップダンス
//------------------------------
enum {
  T_MA = 0, // mission control とapplication control
  T_BR, // () と {}
  T_BL,
  T_SBR, // <> と []
  T_SBL
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [T_MA] = ACTION_TAP_DANCE_DOUBLE(MIS_CON, APP_CON),
    [T_BR] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_9), RBRC),
    [T_BL] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_8), LBRC),
    [T_SBR] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_DOT), SQ_RBRC),
    [T_SBL] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_COMM), SQ_LBRC)
};
//------------------------------

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  // デフォルトレイヤー
  [0] = LAYOUT_universal(
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    MT_ES_AG  , KC_Q      , KC_W      , KC_E      , KC_R      , KC_T      ,                               KC_Y      , KC_U      , KC_I      , KC_O      , KC_P      , MT_AT_AG  ,
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    MT_TAB_G  , KC_A      , KC_S      , KC_D      , KC_F      , KC_G      ,                               KC_H      , KC_J      , KC_K      , KC_L      , LT2_SCLN  , MT_CL_G   ,
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    UNDERB_A  , KC_Z      , KC_X      , KC_C      , KC_V      , KC_B      ,                               KC_N      , KC_M      , KC_COMM   , KC_DOT    , LT5_SLSH  , MT_MI_A   ,
//,-----------+-----------+-----------+-----------+-----------+-----------+-----------.     ,-----------+-----------+-----------+-----------+-----------+-----------+-----------.
                            BSLSH     , XXXXX     , KC_BSPC   , MT_EISU_S , LT1_SPC   ,       LT3_ENT   , MT_KANA_C , XXXXXXX   , XXXXXXX   ,             _______
//,-----------------------------------------------------------------------------------.     ,-----------------------------------------------------------------------------------.
  ),

  //記号レイヤー
  [1] = LAYOUT_universal(
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    A(KC_LGUI), KC_1      , KC_2      , KC_3      , KC_4      , KC_5      ,                               KC_6      , KC_7      , KC_8      , KC_9      , KC_0      , BACK_QUO  ,
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    KC_LGUI   , LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5),                               LSFT(KC_6), LSFT(KC_7), TD(T_BL)  , TD(T_BR)  , PLUS      , AST       ,
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    KC_LALT   , XXXXX     , XXXXX     , XXXXX     , CARET     , PIPE      ,                               CARET     , TILDE     , TD(T_SBL) , TD(T_SBR) , QUESTION  , EQL       ,
//,-----------+-----------+-----------+-----------+-----------+-----------+-----------.     ,-----------+-----------+-----------+-----------+-----------+-----------+-----------.
                            YEN       , _______   , _______   , KC_LSFT   , _______   ,       KC_LSFT   , KC_LCTL   , XXXXXXX   , XXXXXXX   ,             _______
//,-----------------------------------------------------------------------------------.     ,-----------------------------------------------------------------------------------.
  ),

  //マウスレイヤー
  [2] = LAYOUT_universal(
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    VOLU_AG   , QUIT      , CLOSE     , KC_PGUP   , RELOAD    , NEW_TAB   ,                               ZOOM_IN   , KC_PGDN   , KC_PGUP   , ZOOM      , MORE      , KBC_SAVE  ,
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    MUTE_G    , S_ALL     , SAVE      , KC_PGDN   , FIND      , OP_CLO_T  ,                               ZOOM_OUT  , LCLICK    , RCLICK    , MO(4)     , _______   , MO(5)     ,
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    VOLD_A    , UNDO      , CUT       , COPY      , PASTE     , REDO      ,                               TAB_L     , GUI_L     , GUI_R     , TAB_R     , LESS      , KBC_RST   ,
//,-----------+-----------+-----------+-----------+-----------+-----------+-----------.     ,-----------+-----------+-----------+-----------+-----------+-----------+-----------.
                            XXXXX     , XXXXX     , CTR_L     , KC_LSFT   , CTR_R     ,       SPOT_L    , TD(T_MA)  , XXXXXXX   , XXXXXXX   ,             SLEEP
//,-----------------------------------------------------------------------------------.     ,-----------------------------------------------------------------------------------.
  ),

  //テンキーレイヤー
  [3] = LAYOUT_universal(
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    KC_BSPC   , XXXXX     , KC_KP_7   , KC_KP_8   , KC_KP_9   , KC_PPLS   ,                               L_END     , KC_PGDN   , KC_PGUP   , R_END     , KC_HOME   , SCSH_3    ,
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    KC_TAB    , EQL       , KC_KP_4   , KC_KP_5   , KC_KP_6   , KC_PMNS   ,                               KC_LEFT   , KC_DOWN   , KC_UP     , KC_RIGHT  , KC_END    , SCSH_4    ,
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    UNDERBAR  , KC_PSLS   , KC_KP_1   , KC_KP_2   , KC_KP_3   , KC_PAST   ,                               M_L_4X    , M_D_4X    , M_U_4X    , M_R_4X    , XXXXX     , SCSH_5    ,
//,-----------+-----------+-----------+-----------+-----------+-----------+-----------.     ,-----------+-----------+-----------+-----------+-----------+-----------+-----------.
                            KC_LALT   , _______   , KC_KP_0   , LT4_DOT   , KC_SPC    ,       _______   , M_F2      , XXXXXXX   , XXXXXXX   ,             _______
//,-----------------------------------------------------------------------------------.     ,-----------------------------------------------------------------------------------.
  ),

  //アジャストレイヤー
  [4] = LAYOUT_universal(
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    RGB_VAI   , RGB_SAI   , RGB_HUI   , SCRL_DVD  , CPI_I100  , CPI_I1K   ,                               XXXXX     , XXXXX     , XXXXX     , XXXXX     , XXXXX     , _______   ,
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    RGB_VAD   , RGB_SAD   , RGB_HUD   , SCRL_DVI  , CPI_D100  , CPI_D1K   ,                               M_L_4X    , M_D_4X    , M_U_4X    , M_R_4X    , _______   , _______   ,
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    RGB_RMOD  , RGB_TOG   , RGB_MOD   , XXXXX     , KBC_SAVE  , XXXXX     ,                               XXXXX     , XXXXX     , XXXXX     , XXXXX     , XXXXX     , _______   ,
//,-----------+-----------+-----------+-----------+-----------+-----------+-----------.     ,-----------+-----------+-----------+-----------+-----------+-----------+-----------.
                            KBC_RST   , XXXXX     , KC_MRWD   , KC_MPLY   , KC_MFFD   ,      XXXXX     , XXXXX     , XXXXXXX   , XXXXXXX   ,             XXXXX
//,-----------------------------------------------------------------------------------.     ,-----------------------------------------------------------------------------------.
  ),

  //ファンクションレイヤー
  [5] = LAYOUT_universal(
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    SCSH_3    , M_F1      , M_F2      , M_F3      , M_F4      , M_F5      ,                               _______   , _______   , _______   , _______   , _______   , _______   ,
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    SCSH_4    , M_F6      , M_F7      , M_F8      , M_F9      , M_F10     ,                               _______   , _______   , _______   , _______   , _______   , _______   ,
//,-----------------------------------------------------------------------.                             ,-----------------------------------------------------------------------.
    SCSH_5    , M_F11     , M_F12     , _______   , _______   , _______   ,                               _______   , _______   , _______   , _______   , _______   , _______   ,
//,-----------+-----------+-----------+-----------+-----------+-----------+-----------.     ,-----------+-----------+-----------+-----------+-----------+-----------+-----------.
                            _______   , _______   , _______   , _______   , _______   ,       _______   , _______   , XXXXXXX   , XXXXXXX   ,             _______
//,-----------------------------------------------------------------------------------.     ,-----------------------------------------------------------------------------------.
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

//ctrl+の設定1
//bool btn1_pressed = true; //type-A
//
//static bool ctrl_pressed = false; //type-B
//static bool exceptionaly_ctrl_layer_pressed = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    //type-A
    //static bool ctrl_held = false;
    //if (keycode == KC_LCTL || keycode == KC_RCTL || keycode == MT_KANA_C || keycode == MOD_LCTL) {
    //    // Ctrlキーが押された場合
    //    if (record->event.pressed) {
    //        ctrl_held = true;
    //    } else {
    //        ctrl_held = false;
    //    }
    //}
    //if (keycode == KC_H && record->event.pressed && ctrl_held) {
    //    // Ctrlキーが押された状態でHキーが押された場合
    //    unregister_code(KC_LCTL);
    //    unregister_code(KC_RCTL);
    //    register_code(KC_BSPC);
    //    unregister_code(KC_BSPC);
    //    register_code(KC_LCTL); // もし左Ctrlキーが元々押されていた場合、再度登録
    //    return false; // 通常のキー処理をスキップ
    //}

    if (record->event.pressed) {
        switch (keycode) {

            //マクロキーの設定
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


//                //ctrl+の設定2 type-B
//            case KC_LCTRL:
//                if (record->event.pressed) {
//                    ctrl_pressed = true;
//                } else {
//                    ctrl_pressed = false;
//                }
//                break;
//
//
//            default:
//
//
//                //ctrl+の設定3 type-B
//                if (ctrl_pressed || exceptionaly_ctrl_layer_pressed) {
//                    switch (keycode) {
//                        case KC_P:
//                            if (record->event.pressed) {
//                                unregister_code(KC_LCTL);
//                                register_code(KC_BSPACE);
//                                exceptionaly_ctrl_layer_pressed = true;
//                            } else {
//                                unregister_code(KC_BSPACE);
//                                if(ctrl_pressed){
//                                    register_code(KC_LCTL);
//                                }
//                                exceptionaly_ctrl_layer_pressed = false;
//                            }
//                            return false;
//                            break;
//
//                        case KC_Q:
//                            if (record->event.pressed) {
//                                unregister_code(KC_LCTL);
//                                register_code(KC_MINUS);
//                                exceptionaly_ctrl_layer_pressed = true;
//                            } else {
//                                unregister_code(KC_MINUS);
//                                if(ctrl_pressed){
//                                    register_code(KC_LCTL);
//                                }
//                                exceptionaly_ctrl_layer_pressed = false;
//                            }
//                            return false;
//                            break;
//                    }
//                }


        }
    }
    return true;
}

//------------------------------
