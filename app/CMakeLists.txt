file(GLOB APP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*")

add_executable(${EXECUTABLE_NAME} ${APP_SOURCES})

target_include_directories(${LIBRARY_NAME} PUBLIC
    ${CMAKE_BINARY_DIR}
    ${CMAKE_PROJECT_DIR}/include/smartfloorheading
    ${CMAKE_PROJECT_DIR}/external
)

find_library(bcm2835 /usr/local/lib/)
# find_package(Boost REQUIRED COMPONENTS program_options)

target_link_libraries(${EXECUTABLE_NAME} PUBLIC
    ${LIBRARY_NAME}
    ${LIBRARY_HEADERS}
    bcm2835.a
    nlohmann_json
)



if (${ENABLE_WARNINGS})
    target_set_warnings(TARGET ${EXECUTABLE_NAME} ENABLE ON AS_ERROR OFF)
endif()