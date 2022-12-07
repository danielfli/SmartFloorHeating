set (APP_SOURCES "main.cpp")

add_executable(${EXECUTABLE_NAME} ${APP_SOURCES})

target_link_libraries(${EXECUTABLE_NAME} PUBLIC
    ${LIBRARY_NAME}
    ${LIBRARY_HEADERS}
    # ${CONAN_CXXOPTS}
)
target_include_directories(${LIBRARY_NAME} PUBLIC
    "./"
)
if (${ENABLE_WARNINGS})
    target_set_warnings(TARGET ${EXECUTABLE_NAME} ENABLE ON AS_ERROR OFF)
endif()