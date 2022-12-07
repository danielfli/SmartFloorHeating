# Sources and Headers
set(LIBRARY_SOURCES "mini.cpp")
set(LIBRARY_HEADERS "mini.hpp")

# MyLib Library
add_library(${LIBRARY_NAME} STATIC
    ${LIBRARY_SOURCES}
    ${LIBRARY_HEADERS}
    )

target_include_directories(${LIBRARY_NAME} PUBLIC
    "./"
    )

if (${ENABLE_WARNINGS})
    target_set_warnings(TARGET ${LIBRARY_NAME} ENABLE ON AS_ERROR ON)
endif()

if(${ENABLE_LTO})
    target_enable_lto(${LIBRARY_NAME} optimized)
endif()