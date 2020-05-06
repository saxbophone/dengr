/**
 * @file
 *
 * @remarks This source file forms part of DENGR, a piece of software which
 * produces disc images which produce visible images on the recording side when
 * burned to Compact Disc.
 *
 * @author Joshua Saxby <joshua.a.saxby@gmail.com>
 * @date 2020
 *
 * @copyright Copyright (C) 2020 Joshua Saxby
 *
 * @copyright
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * @copyright
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * @copyright
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef COM_SAXBOPHONE_DENGR_SECTION
#define COM_SAXBOPHONE_DENGR_SECTION

#include <array>

#include "F3Frame.hpp"


namespace com::saxbophone::dengr {
    /**
     * @brief A group of 98 consecutive F₃-Frames
     * @details Definition from @e ECMA-130, sec. 4.13:
     * @details A group of 98 F3-Frames containing one complete table of Control
     * bytes.
     */
    struct Section {
        /**
         * @brief The F₃-Frames that comprise this Section
         */
        std::array<F3Frame, 98> frames;
    };
}

#endif // include guard
