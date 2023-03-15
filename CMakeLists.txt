cmake_minimum_required(VERSION 3.10)

project(CryptoDotComAssignment)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES read_and_update_parrot.cpp)
set(HEADER_FILES read_and_update_parrot.h)

# Include generated_parrot to be able to use the generated headers
include_directories(generated_parrot)

# Add the Flatbuffers directory to the CMake build
add_subdirectory(lib/flatbuffers)

# Add the Flatbuffers directory to the CMake build
add_executable(TestParrot ${SOURCE_FILES} ${HEADER_FILES})

# Link the Flatbuffers static library only to the target
target_link_libraries(TestParrot PRIVATE flatbuffers)