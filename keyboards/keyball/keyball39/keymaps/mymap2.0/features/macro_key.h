/* Copyright 2023 kamidai (@d_kamiichi)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// マクロ用変数------------------------------
// SPD_UP用
static bool spd_up = false;
static int arrow_count = 0;
enum arrow_held {
    NO_DIR = 0,
    UP,
    RIGHT,
    LEFT,
    DOWN
};
enum arrow_held arrow_held = NO_DIR;

// mod override用変数
uint8_t mod_state;
/* static bool bspckey_registered = false; */
/* static bool delkey_registered = false; */
/* static bool tabkey_registered = false; */
static bool ctrl_pressed = false;
static bool shift_pressed = false;

#define M_REPEAT_TH 300

// マクロキーを設定
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    current_keycode = keycode;
    mod_state = get_mods();

    switch (keycode) {

        // patern1
        case KC_LCTL:
            if (record->event.pressed) {
                ctrl_pressed = true;
            } else {
                ctrl_pressed = false;
            }
            return true;

        case KC_LSFT:
            if (record->event.pressed) {
                shift_pressed = true;
            } else {
                shift_pressed = false;
            }
            return true;

        case KC_H:
            if (record->event.pressed) {
                if (ctrl_pressed && shift_pressed) {
                    unregister_code(KC_LCTL);
                    unregister_code(KC_LSFT);
                    register_code(KC_DEL);
                    return false;
                }
                if (ctrl_pressed) {
                    unregister_code(KC_LCTL);
                    register_code(KC_BSPC);
                    return false;
                }
            } else {
                unregister_code(KC_BSPC);
                unregister_code(KC_DEL);
                if (ctrl_pressed) {
                    register_code(KC_LCTL);
                }
                if (shift_pressed) {
                    register_code(KC_LSFT);
                }
                return true;
            }

        // pattern2
      /* case KC_H: */
      /*     /1* static bool bspckey_registered; *1/ */
      /*     /1* static bool delkey_registered; *1/ */
      /*     // Initialize a boolean variable that keeps track */
      /*     // of the delete key status: registered or not? */
      /*     if (record->event.pressed) { */
      /*         if (mod_state && MOD_MASK_SHIFT && MOD_MASK_CTRL) { */
      /*             /1* del_mods(MOD_MASK_SHIFT); *1/ */
      /*             /1* del_mods(MOD_MASK_CTRL); *1/ */
      /*             clear_mods(); */
      /*             register_code(KC_DEL); */
      /*             delkey_registered = true; */
      /*             /1* set_mods(mod_state); *1/ */
      /*             return false; */
      /*         } */
      /*         // Detect the activation of either shift keys */
      /*         if (mod_state && MOD_MASK_CTRL) { */
      /*             /1* del_mods(MOD_MASK_CTRL); *1/ */
      /*             clear_mods(); */
      /*             register_code(KC_BSPC); */
      /*             bspckey_registered = true; */
      /*             /1* set_mods(mod_state); *1/ */
      /*             return false; */
      /*         } */
      /*     } else { // on release of KC_BSPC */
      /*         if (bspckey_registered) { */
      /*             unregister_code(KC_BSPC); */
      /*             bspckey_registered = false; */
      /*             set_mods(mod_state); */
      /*             return false; */
      /*         } */
      /*         if (delkey_registered) { */
      /*             unregister_code(KC_DEL); */
      /*             delkey_registered = false; */
      /*             set_mods(mod_state); */
      /*             return false; */
      /*         } */
      /*     } */
      /*     return true; */

      /* case KC_I: */
      /*     // Initialize a boolean variable that keeps track */
      /*     // of the delete key status: registered or not? */
      /*     /1* static bool tabkey_registered; *1/ */
      /*     if (record->event.pressed) { */
      /*         // Detect the activation of either shift keys */
      /*         if (mod_state && MOD_MASK_CTRL) { */
      /*             // First temporarily canceling both shifts so that */
      /*             // shift isn't applied to the KC_DEL keycode */
      /*             /1* del_mods(MOD_MASK_CTRL); *1/ */
      /*             clear_mods(); */
      /*             register_code(KC_TAB); */
      /*             // Update the boolean variable to reflect the status of KC_DEL */
      /*             tabkey_registered = true; */
      /*             // Reapplying modifier state so that the held shift key(s) */
      /*             // still work even after having tapped the Backspace/Delete key. */
      /*             /1* set_mods(mod_state); *1/ */
      /*             return false; */
      /*         } */
      /*     } else { // on release of KC_BSPC */
      /*         // In case KC_DEL is still being sent even after the release of KC_BSPC */
      /*         if (tabkey_registered) { */
      /*             unregister_code(KC_TAB); */
      /*             tabkey_registered = false; */
      /*             set_mods(mod_state); */
      /*             return false; */
      /*         } */
      /*     } */
      /*     // Let QMK process the KC_BSPC keycode as usual outside of shift */
      /*     return true; */

      // macro key
      // SFT + M_CLICK
      case S_M_CLICK:
          if (record->event.pressed) {
              register_code(KC_LSFT);
              register_code(KC_BTN3);
              unregister_code(KC_BTN3);
              unregister_code(KC_LSFT);
              return false;        // Return false to ignore further processing of key
          }
          break;

      // ->
      case R_ARROW:
          if (record->event.pressed) {
              register_code(KC_MINUS);
              unregister_code(KC_MINUS);
              register_code(KC_LSFT);
              register_code(KC_DOT);
              unregister_code(KC_DOT);
              unregister_code(KC_LSFT);
              return false;        // Return false to ignore further processing of key
          }
          break;

      // <-
      case L_ARROW:
          if (record->event.pressed) {
              register_code(KC_LSFT);
              register_code(KC_COMM);
              unregister_code(KC_COMM);
              unregister_code(KC_LSFT);
              register_code(KC_MINUS);
              unregister_code(KC_MINUS);
              return false;        // Return false to ignore further processing of key
          }
          break;

      // =>
      case R_D_ARR:
          if (record->event.pressed) {
              register_code(KC_LSFT);
              register_code(KC_MINUS);
              unregister_code(KC_MINUS);
              register_code(KC_DOT);
              unregister_code(KC_DOT);
              unregister_code(KC_LSFT);
              return false;        // Return false to ignore further processing of key
          }
          break;

      // <=
      case L_D_ARR:
          if (record->event.pressed) {
              register_code(KC_LSFT);
              register_code(KC_COMM);
              unregister_code(KC_COMM);
              register_code(KC_MINUS);
              unregister_code(KC_MINUS);
              unregister_code(KC_LSFT);
              return false;        // Return false to ignore further processing of key
          }
          break;

          // _Mou_NumP
      case LT(_Mou, KC_NO):
          if (record->tap.count && record->event.pressed){
              layer_invert(_NumP);
              return false;
          }
          return true;

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
                  case NO_DIR:
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
                  arrow_held = NO_DIR;
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
                  arrow_held = NO_DIR;
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
                  arrow_held = NO_DIR;
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
                  arrow_held = NO_DIR;
              }
          }
          break;


      // 以下スワイプジェスチャー
      // クリックすると state が SWIPE になり、離したら NONE になる
      // SWIPEの実装はswipe.hに記載する
      case APP_SWIPE:
        if (record->event.pressed) {
          // キーダウン時
          swipe_timer = timer_read();
          is_swiped = false;
          state = SWIPE;
        } else {
          // キーアップ時
          //spot light
          state = NONE;
          if (is_swiped == false && timer_elapsed(swipe_timer) < 300){
            register_code(KC_LGUI);
            register_code(KC_SPACE);
            unregister_code(KC_SPACE);
            unregister_code(KC_LGUI);
          }
        }
        break;

      case VOL_SWIPE:
        if (record->event.pressed) {
          // キーダウン時
          state = SWIPE;
        } else {
          // キーアップ時
          state = NONE;
          if (is_swiped == false && timer_elapsed(swipe_timer) < 300){
            tap_code(KC_MPLY);
          }
        }
        break;

      case BROWSE_SWIPE:
        if (record->event.pressed) {
          // キーダウン時
          state = SWIPE;
        } else {
          // キーアップ時
          state = NONE;
          if (is_swiped == false && timer_elapsed(swipe_timer) < 300){
            register_code(KC_LGUI);
            register_code(KC_R);
            unregister_code(KC_R);
            unregister_code(KC_LGUI);
          }
        }
        break;

      case TAB_SWIPE:
        if (record->event.pressed) {
          // キーダウン時
          state = SWIPE;
        } else {
          // キーアップ時
          state = NONE;
          if (is_swiped == false && timer_elapsed(swipe_timer) < 300){
          }
        }
        break;

      case MAG_SWIPE:
        if (record->event.pressed) {
          // キーダウン時
          state = SWIPE;
        } else {
          // キーアップ時
          state = NONE;
          if (is_swiped == false && timer_elapsed(swipe_timer) < 300){
            register_code(KC_LGUI);
            register_code(KC_LALT);
            register_code(KC_ENT);
            unregister_code(KC_ENT);
            unregister_code(KC_LALT);
            unregister_code(KC_LGUI);
          }
        }
        break;

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
            case NO_DIR:
            break;
        }
    }

};
