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

# Project/Library Names
set(EXECUTABLE_NAME "floorheating")
set(LIBRARY_NAME    "floorheatlib")

### CMAKE MODULES
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)
include(Warnings)


### EXTERNAL LIBRARIES
# include(AddGitSubmodule)
include(FetchContent)
## json lib 
# add_git_submodule(external/json)


FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG  v3.10.1 
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(json)

### Cross building 
if(BUILDING_RASPI_ZERO)
    message("Using CMake Module: ${PATH_CMAKE_MODUL}")
    message("Cross Build for Target Architektur: ${CMAKE_SYSTEM_PROCESSOR}")
endif(BUILDING_RASPI_ZERO)

### SUB DIRECTORIES
add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(app)

### INSTALL TARGETS



install(TARGETS ${EXECUTABLE_NAME}
        # ${LIBRARY_NAME}
        # LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

install(TARGETS ${LIBRARY_NAME}
        LIBRARY DESTINATION lib
        COMPONENT Libraries
        COMPONENT Development 
        PUBLIC_HEADER DESTINATION include/smartfloorheading
        COMPONENT Development)

if(${BUILDING_RASPI_ZERO})
  install(CODE "
  execute_process(COMMAND ${CMAKE_SOURCE_DIR}/utils/copybin.sh ${PATH_INSTALLDIR} ${IPTARGET} ${USER} ${PASSWORD}
  RESULT_VARIABLE result)
  if(NOT result EQUAL 0)
    message(FATAL_ERROR \"Install failed! \${result}\")
  endif()
  ")
endif()
