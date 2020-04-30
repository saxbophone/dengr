#ifndef COM_SAXBOPHONE_DENGR_F3_FRAME
#define COM_SAXBOPHONE_DENGR_F3_FRAME

// TODO: Change to namespace com::saxbophone::dengr when move to C++20 complete
namespace dengr {
    /**
     * @brief One F₃-Frame consisting of the an F₂-Frame with a Control byte
     * prepended
     * @details Definition from @eECMA-130, sec. 4.7:
     * @details A group of 33 8-bit bytes, being an F2-Frame with a control
     * byte, and input to a 8-to-14 encoder.
     */
    class F3Frame {};
}

#endif // include guard
