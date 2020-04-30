### A brief description of the type hierarchies defined in this directory

Listed below in order of decreasing level (where earlier entries indicate that these levels are closer to the "User" and later ones indicate that they are closer to the "Physical").

Note that sub-items indicate types _contained_ within their parent, not that they are closer to the physical layer.

- `Mode2Sector`
    - `Byte`
- `ScrambledSector`
    - `Byte`
- `F1Frame`
    - `Byte`
- `F2Frame`
    - `Byte`
- `Section`
    - `F3Frame`
        - `Byte`
- `ChannelByte`
- `ChannelFrame`
    - `Byte`
    - `MergingBits`
    - `ChannelByte`
