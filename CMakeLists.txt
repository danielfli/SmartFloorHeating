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
include(Warnings)



### EXTERNAL LIBRARIES

if(USE_CONAN)
    message("Using Conan")
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
endif()

### Cross building 
if(BUILDING_RASPI_ZERO)
    message("Using CMake Module: ${PATH_CMAKE_MODUL}")
    message("Cross Build for Target Architektur: ${CMAKE_SYSTEM_PROCESSOR}")
endif(BUILDING_RASPI_ZERO)

### SUB DIRECTORIES

add_subdirectory(src)
add_subdirectory(app)

### INSTALL TARGETS



install(TARGETS ${EXECUTABLE_NAME}
        EXPORT ${LIBRARY_NAME}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

install(TARGETS ${LIBRARY_NAME}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)

if(${BUILDING_RASPI_ZERO})
  install(CODE "
  execute_process(COMMAND ${CMAKE_SOURCE_DIR}/utils/copybin.sh ${PATH_INSTALLDIR} ${IPTARGET} ${USER} ${PASSWORD}
  RESULT_VARIABLE result)
  if(NOT result EQUAL 0)
    message(FATAL_ERROR \"Install failed! \${result}\")
  endif()
  ")
endif()
