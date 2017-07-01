# dengr
Creates Audio Compact Disc tracks which display images on the reflective side of CDs they are written to

## Plan

The overall process involves generating a raw LCPM audio file that when burned to a Compact Disc as an audio track (CDDA), displays a given bitmap image on the data recording side (where lighter areas represent white and darker areas represent black).

### Method

1. Be informed about the physical dimensions of the disc (inner and outer radii of program area, track spiral pitch).
2. Be informed about the Disc's data capacity, measured in sectors.
3. Use sector count to work out how many bytes of audio can be stored on this disc.
4. Use physical dimensions to calculate total length of disc track (in nm or km)
5. For each sector of audio data to generate:
    - For each byte of audio in the sector:
        - convert the byte offset to a physical offset as the number of nm along the spiral from it's origin point that the byte will be physically located on the disc.
        - get the x/y coördinates of this point in the spiral as mapped into cartesian space.
        - sample the image to see which pixel this x/y point lies in and what colour that pixel is.
        - write out byte `0x30` if it is to be black, or `0xAB` if it is to be white.
    - Reverse-CIRC-encode the sector data (so that the result would produce the input sequence when CIRC encoding is applied to it).
    - Reverse-scramble the sector data according to ECMA-130 (so that the result would produce the input sequennce when scrambling is applied to it).
    - Write out the raw resulting data to file.
6. Burn file to disc as an audio track (wrapping it in a container format such as WAV/AIFF first if need be).
