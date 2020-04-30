#ifndef COM_SAXBOPHONE_DENGR_MODE_2_SECTOR
#define COM_SAXBOPHONE_DENGR_MODE_2_SECTOR


// TODO: Change to namespace com::saxbophone::dengr when move to C++20 complete
namespace dengr {
    /**
     * @brief One chunk of user data to be encoded and written to disc
     * @note This is a RAW CD-ROM Mode 2 Sector consisting of 2352 Bytes
     * (see ECMA-130 sec. 14). As it is in RAW format, it includes not only the
     * User Data section, but the Sync and Header sections as well, which we can
     * set to whatever we like as this library is designed for writing images to
     * disc in RAW mode.
     * @details Definition from @eECMA-130, sec. 4.14:
     * @details The smallest addressable part of a Digital Data Track in the
     * information area that can be accessed independently of other addressable
     * parts of the area.
     * @remarks This is the highest-level data structure for storing user data
     * modelled by this library.
     */
    class Mode2Sector {};
}

#endif // include guard
