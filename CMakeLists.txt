cmake_minimum_required(VERSION 3.10)

project(CryptoDotComAssignment)

set(CMAKE_CXX_STANDARD 17)

# separate the source files and header files for qn 2
set(QN_2_SOURCE_FILES qn_2_read_and_update_parrot.cpp)
set(QN_2_HEADER_FILES qn_2_read_and_update_parrot.h)

# separate the source files and header files for qn 3, server and client
set(QN_3_SERVER_SOURCE_FILES qn_3_server_socket.cpp)
set(QN_3_SERVER_HEADER_FILES qn_3_server_socket.h)

set(QN_3_CLIENT_SOURCE_FILES qn_3_client_socket.cpp)
set(QN_3_CLIENT_HEADER_FILES qn_3_client_socket.h)

set(QN_4_SERVER_SOURCE_FILES qn_4_server_socket.cpp)
set(QN_4_SERVER_HEADER_FILES qn_4_server_socket.h)

set(QN_4_CLIENT_SOURCE_FILES qn_4_client_socket.cpp)
set(QN_4_CLIENT_HEADER_FILES qn_4_client_socket.h)

# Include generated_parrot to be able to use the generated headers
include_directories(generated_parrot)

# Add the Flatbuffers directory to the CMake build
add_subdirectory(lib/flatbuffers)

# Force using static libraries - this embeds the boost code directly into the executable
set(Boost_USE_STATIC_LIBS ON)

#  Add the boost directory to the CMake build
# Boost.Asio is a header-only library; we don't need to build it separately here, and only need to build the dependencies it needs
# Boost.System library is needed as a dependency for Boost.Asio
find_package(Boost 1.58.0 COMPONENTS system REQUIRED)

# Include the boost library, so we can include the boost headers in our code
include_directories(${Boost_INCLUDE_DIRS})

# Add the executable for Question 2
add_executable(Question2 ${QN_2_SOURCE_FILES} ${QN_2_HEADER_FILES})

# Add the executable for Question 3
add_executable(Question3Server ${QN_3_SERVER_SOURCE_FILES} ${QN_3_SERVER_HEADER_FILES})
add_executable(Question3Client ${QN_3_CLIENT_SOURCE_FILES} ${QN_3_CLIENT_HEADER_FILES})

# Add the executable for Question 4
add_executable(Question4Server ${QN_4_SERVER_SOURCE_FILES} ${QN_4_SERVER_HEADER_FILES})
add_executable(Question4Client ${QN_4_CLIENT_SOURCE_FILES} ${QN_4_CLIENT_HEADER_FILES})

# Link the flatbuffers static library only to the target
target_link_libraries(Question2 PRIVATE flatbuffers)

# Link the boost library and flatbuffers static libraries to qn 3 server and client targets
target_link_libraries(Question3Server PRIVATE flatbuffers ${Boost_LIBRARIES})
target_link_libraries(Question3Client PRIVATE flatbuffers ${Boost_LIBRARIES})

# Link the boost library and flatbuffers static libraries to qn 4 server and client targets
target_link_libraries(Question4Server PRIVATE flatbuffers ${Boost_LIBRARIES})
target_link_libraries(Question4Client PRIVATE flatbuffers ${Boost_LIBRARIES})