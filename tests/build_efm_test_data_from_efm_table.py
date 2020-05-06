#!/usr/bin/env python3

'''
This source file forms part of DENGR, a piece of software which
produces disc images which produce visible images on the recording side when
burned to Compact Disc.

This helper script can be used to re-generated the data-driven test data used
to test the EFM encoder/decoder, the tests for which are in the file efm.cpp

Copyright (C) 2020 Joshua Saxby <joshua.a.saxby@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
'''


def encoding_pair_generator():
    with open('ECMA-130_Annex-D_EFM-Table.txt', 'r') as efm_table:
        for line in efm_table:
            # split each line on space to get two pairs of byte->EFM combinations
            parts = line.split()
            for byte, efm in zip(parts[::2], parts[1::2]):
                # convert each pair into a C++ source code line containing them
                yield 'std::pair<uint8_t, uint16_t>{{0b{0}, 0b{1}}},'.format(
                    byte, efm
                )


for line in encoding_pair_generator():
    print(line)
