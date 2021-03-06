/* -*- mode: c++ -*-
 * Kaleidoscope-ModRight -- Require the use of proper modifier keys
 * Copyright (C) 2017  John SJ Anderson
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#include <Kaleidoscope-ModRight.h>
#include <kaleidoscope/hid.h>

namespace kaleidoscope {
  const Key *ModRight::require_left;
  const Key *ModRight::require_right;

  bool ModRight::mod_active_;
  bool ModRight::mod_active_left;
  bool ModRight::mod_active_right;

  ModRight::ModRight(void) {}

  void ModRight::begin(void) {
    Kaleidoscope.useEventHandlerHook(eventHandlerHook);
    Kaleidoscope.useLoopHook(loopHook);
  }

  void ModRight::loopHook(bool is_post_clear) {
    if (is_post_clear) {
      return;
    }

    // TODO will need to handle configurable keys
    mod_active_      = hid::isModifierKeyActive(Key_LeftShift) || hid::isModifierKeyActive(Key_RightShift);
    mod_active_left  = hid::isModifierKeyActive(Key_LeftShift);
    mod_active_right = hid::isModifierKeyActive(Key_RightShift);
  }

  Key
  ModRight::eventHandlerHook(Key mapped_key, byte row, byte col, uint8_t key_state) {
    // TODO will need to handle configurable keys
    // If Shift is not active, bail out early.
    if (!mod_active_) {
      return mapped_key;
    }

    Key orig, repl;
    const Key *active_list;

    active_list = (mod_active_right) ? require_left : require_right;

    // Try to find the current key in the ilst
    uint8_t i = 0;
    do {
      orig.raw = pgm_read_word(&(active_list[i].raw));
      i++;
    } while (orig.raw != Key_NoKey.raw && orig.raw != mapped_key.raw);
    i--;

    // If not found, bail out.
    if (orig.raw == Key_NoKey.raw) {
      return mapped_key;
    }

    // If found, that means the incorrect shift key was used, so return NoKey instead
    repl.raw = Key_NoKey.raw;

    return repl;
  }
}

kaleidoscope::ModRight ModRight;
