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

#pragma once

#include <Kaleidoscope.h>

namespace kaleidoscope {
  class ModRight : public KaleidoscopePlugin {
  public:
    const Key *require_right;
    const Key *require_left;

    ModRight(void);

    void begin(void) final;
  private:
    static bool mod_active_;
    static bool mod_active_left;
    static bool mod_active_right;
    static Key  eventHandlerHook(Key mapped_key, byte row, byte col, uint8_t key_state);
    static void loopHook(bool is_post_clear);
  };
}

extern kaleidoscope::ModRight ModRight;
