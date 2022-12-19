### Sources and Headers
file(GLOB LIBRARY_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.c*)
file(GLOB LIBRARY_HEADERS ${CMAKE_SOURCE_DIR}/include/smartfloorheading/*.h*)

### Library
add_library(${LIBRARY_NAME} STATIC
            ${LIBRARY_SOURCES}
            )

target_include_directories(${LIBRARY_NAME} PUBLIC
    ${PROJECT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/include/smartfloorheading
    )

set_target_properties(${LIBRARY_NAME} 
                        PROPERTIES PUBLIC_HEADER ${LIBRARY_HEADERS})

if (${ENABLE_WARNINGS})
    target_set_warnings(TARGET ${LIBRARY_NAME} ENABLE ON AS_ERROR OFF)
endif()