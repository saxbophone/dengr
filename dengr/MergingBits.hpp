#ifndef COM_SAXBOPHONE_DENGR_MERGING_BITS
#define COM_SAXBOPHONE_DENGR_MERGING_BITS

#include <cstdint>


// TODO: Change to namespace com::saxbophone::dengr when move to C++20 complete
namespace dengr {
    /**
     * @brief A sequence of 3 Channel bits delimiting each part of a Channel
     * Frame to prevent encoding issues.
     * @details See @e ECMA-130, secs. 19.3 and 19.4 for more information.
     * @warn Don't set the 5 most significant bits of this type. It's declared
     * as 8-bit because 3-bit isn't an option, but it should be used as if it's
     * 3-bit. It might be packed into a 3-bit bitfield in structures that use
     * it.
     */
    typedef std::uint8_t MergingBits;
}

#endif // include guard
