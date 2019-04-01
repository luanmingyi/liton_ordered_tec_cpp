cmake_minimum_required (VERSION 3.5)

project(ordered_tec_lib)

add_library(ordered_tec INTERFACE)
target_sources(ordered_tec INTERFACE
    $<INSTALL_INTERFACE:include/ordered_tec.cpp>
)

install(
    FILES scr/ordered_tec.h scr/ordered_tec.cpp
    DESTINATION include
)

install(
    TARGETS ordered_tec
    EXPORT library_targets
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    INCLUDES DESTINATION include
)

install(
    EXPORT library_targets
    FILE ordered_tec-config.cmake
    NAMESPACE liton::
    DESTINATION lib/cmake/ordered_tec
)
