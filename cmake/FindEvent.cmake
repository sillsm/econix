# Find Libevent
# http://monkey.org/~provos/libevent/
#
# Once done, this will define:
#
#  Event_FOUND - system has Event
#  Event_INCLUDE_DIRS - the Event include directories
#  Event_LIBRARIES - link these to use Event
#
 
#if (EVENT_INCLUDE_DIR AND EVENT_LIBRARY)
#  # Already in cache, be silent
#  set(EVENT_FIND_QUIETLY TRUE)
#endif (EVENT_INCLUDE_DIR AND EVENT_LIBRARY)
 
find_path(LibEvent_INCLUDE_DIR event.h
  PATHS /usr/include
  PATH_SUFFIXES event
)
 
find_library(EVENT_LIBRARY
  NAMES event
  PATHS /usr/lib /usr/local/lib
)
 
set(LibEvent_LIBS ${EVENT_LIBRARY} )
 
add_definitions(-DLIBNET_LIL_ENDIAN)

 
mark_as_advanced(LibEvent_INCLUDE_DIR LibEvent_LIBS)