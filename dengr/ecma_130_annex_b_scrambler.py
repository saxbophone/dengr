#!/usr/bin/env python3

'''
This source file forms part of DENGR, a piece of software which
produces disc images which produce visible images on the recording side when
burned to Compact Disc.

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

from bitstring import BitArray


def kris_kaspersky_scrambler():
    """
    The reference CD sector scrambler implementation offered by Kris Kaspersky
    in his book: "CD Cracking Uncovered: Protection against unsanctioned copying"
    """
    # start value is 15-bit 1 prefixed with 1 for the "bit clock"
    register = 0b1000000000000001
    yield register
    while True:
        # modulo-2 addition with shift
        temp = register >> 1
        temp = register ^ temp
        register = temp >> 1
        # processing polynomial x^15 + x + 1; e.g. 1 << 15 + 1 << 1 + 1 << 0
        if register & (1 << 1):
            register = register ^ (1 << 15)
        if register & (1 << 0):
            register = register ^ ((1 << 15) | (1 << 14))
        yield register


def joshua_saxby_scrambler():
    """
    My own implementation of the CD sector scrambler, based partly on commentary
    and analysis from Kris Kaspersky's aforementioned book, and also based on
    my interpretation of the ECMA-130 Annex B scrambler description
    """
    # start value has least significant bit set to 1
    register = BitArray(uint=0b0000000000000001, length=16)
    # NOTE: BitArray library addresses bits in big-endian order
    # Bit clock = XOR least two significant bits
    register[0] = register[14] ^ register[15]
    yield register.uint
    while True:
        # XOR the register with a copy of itself shifted one right
        copy = register.uint >> 1
        register.uint = register.uint ^ copy
        # shift the result to the right again
        register.uint >>= 1
        # Bit clock = XOR least two significant bits
        register[0] = register[14] ^ register[15]
        # Kris Kaspersky claims that if the first bit (LSB) is set to 1, we
        # should toggle the second MSB (bit right of MSB)
        # The following if block does this, and it DOES cause the output of
        # this implementation to produce sequences identical to other third
        # party produced sequences, but it is not clear yet how this relates
        # to the reference material, ECMA-130 Annex B
        if register[15]:
            register[1] = not register[1]
        yield register.uint


def joshes_try_scrambler():
    """
    An alternative attempt of mine to try and more strictly interpret the
    standard, but it doesn't produce sequences that are at all close to that
    produced by other third parties nor reference implementations
    """
    # start value has least significant bit set to 1
    register = BitArray(uint=0b0000000000000001, length=16)
    while True:
        # Bit clock = XOR least two significant bits
        register[0] = BitArray(bool=(register[14] ^ register[15]))
        yield register.uint
        # shift feedback register right
        register.ror(1)


k = kris_kaspersky_scrambler()
j = joshua_saxby_scrambler()

for _ in range(1170):  # 1170 = 2340 ÷ 2 (scrambler operates on 16-bit words)
    print(
        BitArray(uint=next(k), length=16).hex,
        BitArray(uint=next(j), length=16).hex,
        end=''
    )
    # press ENTER to continue
    dont_care = input()
