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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

// 自前の絶対数を返す関数。 Functions that return absolute numbers.
int16_t my_abs(int16_t num) {
  if (num < 0) {
    num = -num;
  }
  return num;
}

// 自前の符号を返す関数。 Function to return the sign.
int16_t mmouse_move_y_sign(int16_t num) {
  if (num < 0) {
    return -1;
  }
  return 1;
}


// swipe implement
int16_t current_keycode;
const int16_t SWIPE_THRESHOLD = 10;
bool is_swiped = false;
bool is_repeat = false;
bool is_actioned = false;

// スワイプジェスチャーで何が起こるかを実際に処理する関数
// 上、下、左、右、スワイプなしの5つのオプションがあります
void process_swipe_gesture(int16_t x, int16_t y) {
  // APP_SWIPE
  // desktop control
  if (current_keycode == APP_SWIPE) {
    if (my_abs(x) < my_abs(y)) {
      if (y < 0) {
        // swipe up
        // mission control
        register_code(KC_LCTL);
        register_code(KC_UP);
        unregister_code(KC_UP);
        unregister_code(KC_LCTL);
      } else {
        // swipe down
        // app control
        register_code(KC_LCTL);
        register_code(KC_DOWN);
        unregister_code(KC_DOWN);
        unregister_code(KC_LCTL);
      }
    }
    if (my_abs(x) > my_abs(y)) {
      if (x < 0) {
        // swipe left
        // left desktop
        register_code(KC_LCTL);
        register_code(KC_LEFT);
        unregister_code(KC_LEFT);
        unregister_code(KC_LCTL);
        /* is_repeat = true; */
      } else {
        // swipe right
        // right desktop
        register_code(KC_LCTL);
        register_code(KC_RIGHT);
        unregister_code(KC_RIGHT);
        unregister_code(KC_LCTL);
        /* is_repeat = true; */
      }
    }
  }

  // VOL_SWIPE
  if (current_keycode == VOL_SWIPE) {
    if (my_abs(x) < my_abs(y)) {
      if (y < 0) {
        // swipe up
        // volume up
        register_code(KC_VOLU);
        unregister_code(KC_VOLU);
        /* is_repeat = true; */
      } else {
        // swipe down
        // volume down
        register_code(KC_VOLD);
        unregister_code(KC_VOLD);
        /* is_repeat = true; */
      }
    }
    if (my_abs(x) > my_abs(y)) {
      if (x < 0) {
        // swipe left
      } else {
        // swipe right
      }
    }
  }

  // BROWSE_SWIPE
  // browse control
  if (current_keycode == BROWSE_SWIPE) {
    if (my_abs(x) < my_abs(y)) {
      if (y < 0) {
        // swipe up
        // copy
        register_code(KC_LGUI);
        register_code(KC_C);
        unregister_code(KC_C);
        unregister_code(KC_LGUI);
      } else {
        // swipe down
        // paste
        register_code(KC_LGUI);
        register_code(KC_V);
        unregister_code(KC_V);
        unregister_code(KC_LGUI);
      }
    }
    if (my_abs(x) > my_abs(y)) {
      if (x < 0) {
        // swipe left
        // browse back
        register_code(KC_LGUI);
        register_code(KC_LEFT);
        unregister_code(KC_LEFT);
        unregister_code(KC_LGUI);
      } else {
        // swipe right
        // browse forward
        register_code(KC_LGUI);
        register_code(KC_RIGHT);
        unregister_code(KC_RIGHT);
        unregister_code(KC_LGUI);
      }
    }
  }

  // TAB_SWIPE
  // TAB
  if (current_keycode == TAB_SWIPE) {
    if (my_abs(x) < my_abs(y)) {
      if (y < 0) {
        // swipe up
        // new tab
        register_code(KC_LGUI);
        register_code(KC_T);
        unregister_code(KC_T);
        unregister_code(KC_LGUI);
      } else {
        // swipe down
        // tab close
        register_code(KC_LGUI);
        register_code(KC_W);
        unregister_code(KC_W);
        unregister_code(KC_LGUI);
      }
    }
    if (my_abs(x) > my_abs(y)) {
      /* is_repeat = true; */
      if (x < 0) {
        // swipe left
        // next tab
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        register_code(KC_TAB);
        unregister_code(KC_TAB);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
      } else {
        // swipe right
        // previous tab
        register_code(KC_LCTL);
        register_code(KC_TAB);
        unregister_code(KC_TAB);
        unregister_code(KC_LCTL);
      }
    }
  }

  // MAG_SWIPE
  // MEGNET
  if (current_keycode == MAG_SWIPE) {
    if (my_abs(x) < my_abs(y)) {
      if (y < 0) {
        // swipe up
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_UP);
        unregister_code(KC_UP);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
      } else {
        // swipe down
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_DOWN);
        unregister_code(KC_DOWN);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
      }
    }
    if (my_abs(x) > my_abs(y)) {
      if (x < 0) {
        // swipe left
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LEFT);
        unregister_code(KC_LEFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
      } else {
        // swipe right
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_RIGHT);
        unregister_code(KC_RIGHT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
      }
    }
  }
}


// swipe mode
enum ball_state {
  NONE = 0,
  SWIPE,      // スワイプモードが有効になりスワイプ入力が取れる。 Swipe mode is enabled to take swipe input.
  SWIPING     // スワイプ中。 swiping.
};

enum ball_state state;  // 現在のクリック入力受付の状態 Current click input reception status
uint16_t click_timer;   // タイマー。状態に応じて時間で判定する。 Timer. Time to determine the state of the system.
uint16_t swipe_timer;

//
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
  int16_t current_x = mouse_report.x;
  int16_t current_y = mouse_report.y;

  if (current_x != 0 || current_y != 0) {
    switch (state) {
      case SWIPE:
        click_timer = timer_read();

        if (my_abs(current_x) >= SWIPE_THRESHOLD || my_abs(current_y) >= SWIPE_THRESHOLD) {
          rgblight_sethsv(HSV_PINK);
          process_swipe_gesture(current_x, current_y);
          is_swiped = true;

          if (is_repeat == false) {
            state = SWIPING;
          }
        }
        break;

      default:
        break;
    }
  } else {
    switch (state) {
      case SWIPE:
        rgblight_sethsv(HSV_SPRINGGREEN);
        break;

      case SWIPING:
        if (timer_elapsed(click_timer) > 300) {
          state = SWIPE;
        }
        break;

      default:
        break;
    }
  }
  mouse_report.x = current_x;
  mouse_report.y = current_y;

  return mouse_report;
}
