#!/usr/bin/env python3


'''
This helper script can be used to re-generated the data-driven test data used
to test the EFM encoder/decoder, the tests for which are in the file efm.cpp
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
