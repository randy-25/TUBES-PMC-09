cmake_minimum_required(VERSION 3.10)

# Project name and version
project(MyGTK4Project VERSION 1.0)

# Specify the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Collect all source files in the src directory
file(GLOB SRC_FILES
    "${PROJECT_SOURCE_DIR}/src/*.c"
)

# Add the main.c file explicitly
set(SRC_FILES ${SRC_FILES} ${PROJECT_SOURCE_DIR}/main.c)

# Add the executable
add_executable(main ${SRC_FILES})

# Find GTK4 package
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

# Include directories
include_directories(
    ${GTK4_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/header
)

# Link libraries
target_link_libraries(main ${GTK4_LIBRARIES})

# Add compiler flags
add_compile_options(${GTK4_CFLAGS_OTHER})

# Set the output directory for the executable
set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
)
