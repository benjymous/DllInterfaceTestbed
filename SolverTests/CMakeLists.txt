CMAKE_MINIMUM_REQUIRED(VERSION 3.16)

# CMake instructions to make the exe

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

PROJECT( SolverTests )

include_directories("../Shared/Include/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../bin/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../bin/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

file(GLOB Glob_Src
     "*.h"
     "*.cpp"
)

add_library(SolverLib STATIC IMPORTED)
set_target_properties(SolverLib
  PROPERTIES
  IMPORTED_LOCATION "../bin/lib/libSolverLib.a"
  IMPORTED_SONAME libSolverLib.a
)

ADD_EXECUTABLE( SolverTests ${Glob_Src} )
target_link_libraries( SolverTests SolverLib )

