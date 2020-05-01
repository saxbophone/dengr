#ifndef COM_SAXBOPHONE_DENGR_PIT
#define COM_SAXBOPHONE_DENGR_PIT

// TODO: Change to namespace com::saxbophone::dengr when move to C++20 complete
namespace com::saxbophone::dengr {
    /**
     * @brief A single Pit or Land on the physical reflective layer of the disc
     * @remarks This represents the NRZI-encoded version of the sequence of
     * Channel Bits formed by the data in a Channel Frame.
     * @details Definition of the pits/lands can be found in ECMA-130, sec. 11.1
     * @details Definition of how Channel Bits are encoded into these can be
     * found in ECMA-130, sec. 19.4
     */
    enum Pit : bool {
        PIT = true,   /**< A depression on the track's surface */
        LAND = false, /**< A flat area on the track's surface */
    };
}

#endif // include guard
