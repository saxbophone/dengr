[![Stand With Ukraine](https://raw.githubusercontent.com/vshymanskyy/StandWithUkraine/main/banner2-direct.svg)](https://stand-with-ukraine.pp.ua)
# dengr ![continuous-integration](https://github.com/saxbophone/dengr/workflows/continuous-integration/badge.svg) ![GitHub](https://img.shields.io/github/license/saxbophone/dengr)

### (Disc ENGRaver)

Creates optical disc image files which produce visible images on the recordable (shiny) side of the disc when burned to a suitable recordable disc.

### Supported Platforms

Project requires a C++20 compiler. Tested with Github Actions with the following compilers on the following platforms:

- Linux, macOS:
    - GCC 10
    - Clang 10
- Windows
    - Visual Studio 16 2019

## Dedication

This work is dedicated to the late [Kris Kaspersky](https://research.checkpoint.com/2018/tribute-kris-kaspersky/), whose book _CD Cracking Uncovered: Protection against unsanctioned copying_ has been an invaluable resource for explaining and reverse-engineering the lower-level encoding details of Compact Discs.

## Overview

This is a rewrite of a previous idea I had in which I attempted to achieve this by generating a large WAV audio file to produce the visible image instead, however it turns out there's really no advantage to doing it this way, so I may as well produce raw binary (CD-ROM Mode 2) disc images instead, this avoids for the need to mess about with audio file formats and I can just output binary data direct to image file instead. The original prototype is preserved in this Git repository and can be found under the `prototype` tag.

I first got the idea for this project upon noticing that Nirvana's popular album **Nevermind** has a visible ring of a different colour towards the end of the recording side of the disc. It turns out that this visual artifact is produced by the 10 minutes of silence that follows after the last _listed_ track before the _hidden_ bonus track ("Endless, Nameless") is heard. I decided I would try and use this phenomenon to produce discernible images on the recording side of discs by generating the right pattern of binary data on the disc itself.

It turns out I'm not the first person to try this either, a maker has previously published a guide for doing this on Instructables.com: [https://www.instructables.com/id/Burning-visible-images-onto-CD-Rs-with-data-beta/](https://www.instructables.com/id/Burning-visible-images-onto-CD-Rs-with-data-beta/). I am grateful to them for proving that such an idea is possible. The now-obsolete technology _DiscT@2_ ("disc tattoo") as implemented in the Yamaha F1 disc drives also implemented the same concept, albeit also allowing some data to be stored on the disc if desired [further reading: DiscT@2 on Wikipedia](https://en.wikipedia.org/wiki/DiscT@2).

I've decided that in the interests of my own learning (and also to produce a project that provides an all-in-one solution encompassing interpretation of images and producing disc images), I would like to produce my own software that implements such a system for "engraving" images onto the recordable side of optical discs. Initially I shall focus my efforts on producing disc images for Compact Discs, however it is entirely possible that with some tweaking of the disc geometry, the same software may also be used to generate disc images that can be written to DVD or Blu-Ray discs, but I will not focus on nor guarantee this outright.

## Plan

The overall process involves generating a disc image that when burned to a Compact Disc as a data track (CD-ROM, Mode 2), displays a given bitmap image on the data recording side (where lighter areas represent white and darker areas represent black).

### Method

1. Be informed about the physical dimensions of the disc (inner and outer radii of program area, track spiral pitch).
2. Be informed about the Disc's data capacity, measured in sectors.
3. Use sector count to work out how many bytes can be stored on this disc.
4. Use physical dimensions to calculate total length of disc track (in nm or km)
5. For each sector of data to generate:
    - For each byte in the sector:
        - convert the byte offset to a physical offset as the number of nm along the spiral from it's origin point that the byte will be physically located on the disc. **NOTE:** _the spiral data track of optical discs is the involute of a circle, not an archimedean spiral._
        - get the x/y coördinates of this point in the spiral as mapped into Cartesian space.
        - sample the image to see which pixel this x/y point lies in and what colour that pixel is.
        - write out an EFM codeword that would produce "darkness" or "lightness" depending on what pixel shade is at that position
    - Reverse the EFM encoding in the sector
    - Reverse-CIRC-encode the sector data (so that the result would produce the input sequence when CIRC encoding is applied to it).
    - Reverse-scramble the sector data according to ECMA-130 (so that the result would produce the input sequence when scrambling is applied to it).
    - Write out the raw resulting data to an image file.
6. Burn image file to disc using CD-ROM Mode 2.
