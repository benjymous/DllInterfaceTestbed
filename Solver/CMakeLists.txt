CMAKE_MINIMUM_REQUIRED(VERSION 3.16)

# CMake instructions to make the static lib

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

PROJECT( SolverLib )

include_directories("../Shared/Include/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../bin/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../bin/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

file(GLOB Glob_Src
     "*.h"
     "*.cpp"
)

add_definitions(
    -DSOLVER_EXPORTS
)

ADD_LIBRARY( SolverLib STATIC ${Glob_Src} )

