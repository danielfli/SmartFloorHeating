cmake_minimum_required(VERSION 3.18.4)

project("smartfloorheading" VERSION 1.0.0 LANGUAGES C CXX)

# Global CMake variables are set here
set(CMAKE_CXX_STANDARD              20)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS   ON)


# Options
option(USE_CONAN            "Whether to use conan"         OFF)
option(ENABLE_WARNINGS      "Enable to add warnings to a target."   ON)
option(ENABLE_TESTING       "Enable a Unit Testing build."          OFF)
option(ENABLE_COVERAGE      "Enable a Code Coverage build."         OFF)
option(ENABLE_CLANG_TIDY    "Enable to add clang tidy."             OFF)
option(ENABLE_CCACHE        "Enable to add Ccache."                 OFF)

# Project/Library Names
set(EXECUTABLE_NAME "floorheating")
set(LIBRARY_NAME    "floorheatlib")

### CMAKE MODULES

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)
# include(ConfigSafeGuards)
include(Warnings)
# include(Docs)
# include(AddGitSubmodule)
# include(FetchContent)


# include(Ccache)

# if (ENABLE_TESTING)
#     include(CTest)
#     endif()
# if (ENABLE_COVERAGE)
#     include(CodeCoverage)
#     append_coverage_compiler_flags()
# endif()

if (ENABLE_LTO)
    find_lto(CXX)
endif()

### EXTERNAL LIBRARIES

if(USE_CONAN)
    message("Using Conan")
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
endif()

### Cross building 
if(BUILDING_RASPI_ZERO)
    include(crossarmv6l)
endif(BUILDING_RASPI_ZERO)

### SUB DIRECTORIES

add_subdirectory(src)
add_subdirectory(app)

### INSTALL TARGETS

# install(TARGETS ${EXECUTABLE_NAME}
#         EXPORT ${LIBRARY_NAME}
#         ARCHIVE DESTINATION lib
#         LIBRARY DESTINATION lib
#         RUNTIME DESTINATION bin)

# install(TARGETS ${LIBRARY_NAME}
#         ARCHIVE DESTINATION lib
#         LIBRARY DESTINATION lib)
