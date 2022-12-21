### Sources and Headers
file(GLOB LIBRARY_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.c*)
file(GLOB LIBRARY_HEADERS ${CMAKE_SOURCE_DIR}/include/smartfloorheating/*.h*)

### Library
add_library(${LIBRARY_NAME} STATIC
            ${LIBRARY_SOURCES}
            )

find_path(bcm2835ApiIncludes bcm2835.h PATHS /usr/local/include)
if(NOT bcm2835ApiIncludes)
    message(FATAL_ERROR "Can't find folder containing bcm2835.h")
endif()

find_file(bcm2835 bcm2835.h PATHS /usr/local/include/ NO_DEFAULT_PATH)
if(NOT bcm2835)
    message(FATAL_ERROR "Can't find bcm2835.h in ${bcm2835ApiIncludes}")
endif()


target_include_directories(${LIBRARY_NAME} PUBLIC
    ${PROJECT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/include/smartfloorheating
    ${bcm2835ApiIncludes}
    ${CURL_INCLUDE_DIR}
    )

set_target_properties(${LIBRARY_NAME} 
    PROPERTIES PUBLIC_HEADER ${LIBRARY_HEADERS})

if (${ENABLE_WARNINGS})
    target_set_warnings(TARGET ${LIBRARY_NAME} ENABLE ON AS_ERROR OFF)
endif()