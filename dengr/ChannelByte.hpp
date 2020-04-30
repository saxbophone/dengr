#ifndef COM_SAXBOPHONE_DENGR_CHANNEL_BYTE
#define COM_SAXBOPHONE_DENGR_CHANNEL_BYTE

#include <cstdint>


// TODO: Change to namespace com::saxbophone::dengr when move to C++20 complete
namespace dengr {
    /**
     * @brief A 14-bit "byte", as output from the 8-to-14 modulator
     * @details This is the last layer of data encoding before the physical
     * layer of Pits and Lands is reached on the recording surface of the disc
     * itself.
     * @note "Channel Byte" is not an official term used within the reference
     * standard (ECMA-130) itself, but is used in this library as a term of
     * convenience for the alternative which would be "14-bit byte" (this is
     * incidentally, similar to the phrasing used in ECMA-130).
     * @warn Don't set the two most significant bits of this type. It's declared
     * as 16-bit because 14-bit isn't an option, but it should be used as if
     * it's 14-bit. It might be packed into a 14-bit bitfield in structures that
     * use it.
     */
    typedef std::uint16_t ChannelByte;
}
