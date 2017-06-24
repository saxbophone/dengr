# dengr
Creates Compact Disc image files which display images on the reflective side of CDs they are written to

## Plan

I originally intended to write the data to CDs in CDROM mode 2, but this requires a lot of messing around with reversing encoding formats (EFM, CIRC, etc...) which is a massive hassle.

Instead, I've theorised that I may be able to get visible shapes to appear on the data side of the CD by writing 'white' as random audio samples (roughly white noise) and 'black' as completely silent audio (complete 0s).

Method:

1. Be informed about the physical dimensions of the disc (inner and outer radii of program area, track spiral pitch).
2. Be informed about the Disc's music audio capacity, as measured in seconds (or samples???)
3. Use audio capacity to work out amount of data the audio takes up (in bytes)
4. Use physical dimensions to calculate total length of disc track (in nm or km)
5. For each byte of audio that is to be written to the disc:
    - convert the byte offset to a physical offset as the number of nm along the spiral from it's origin point that byte will be physically located on the disc
    - get the x/y coördinates of this point in the spiral as mapped into cartesian space
    - sample the image to see which pixel this x/y point lies in and what colour that pixel is
    - write psuedo-random samples for this byte if it lies in a white area or 0 samples if it lies in a black area
