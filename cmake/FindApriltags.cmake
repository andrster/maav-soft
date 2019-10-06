find_path(APRILTAGS_INCLUDE_DIRS NAMES apriltag.h
    PATHS /usr/local/include/apriltag
)

find_library(APRILTAGS_LIBRARIES NAMES libapriltag apriltag
    /usr/local/lib
)

set(APRILTAGS_LIBRARIES ${APRILTAGS_LIBRARIES} CACHE STRING "")
set(APRILTAGS_INCLUDE_DIRS ${APRILTAGS_INCLUDE_DIRS} CACHE STRING "")

mark_as_advanced(APRILTAGS_INCLUDE_DIRS APRILTAGS_LIBRARIES)
