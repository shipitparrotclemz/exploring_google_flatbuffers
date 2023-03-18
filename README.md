# Crypto.com Assignment with Google FlatBuffers

Hi! Thank you for vetting through my thoughts and submissions!

This README.md details my thought process, and hopefully makes it easy for you to vet this easier!

## Q: What is Google FlatBuffers?

A: This was my first time being exposed to Google FlatBuffers, so I had to bite the bullet and read the documentation to get a gist of things.

**FlatBuffers - Overview**
https://google.github.io/flatbuffers/index.html#flatbuffers_overview

And I realized that FlatBuffers is a serialization library.

However, we might ask:

#### Q: What makes FlatBuffers better than other serialization library out there?

A: A couple of reasons, which I am rather impressed, but tad skeptical about :)

**1. Fast access to serialized data, specifically by avoiding the need for deserialization during access.** 

It represents hierarchical data in a flat binary buffer, such that we can access the serialized data without deserializing the data.

**2. Memory Efficiency and Speed**

It only uses a fixed and small-sized flat binary buffer to access the serialized data in C++.

Also, it speeds up reading and writing, by allowing memory-mapping (mmap) or streaming.

Memory mapping allows us to access the serialized data directly from the file, and write directly to the file without having to copy the file data into memory and vice-versa.

This avoids us from having to unnecessarily spend more instructions (time) and memory to copy data from file to memory and vice-versa.

**3. Allows for Optional fields.**

Allows us to have a flexible schema. When adding a new field, we don't have to imput our existing data with the new field.

**4. Small amount of generated code**

Easy to integrate into existing codebase, and less generated code to worry about.

**5. Strongly-typed, allows us to fail fast at compile time**

Allows us to detect for errors at compile time, and not at runtime.

**6. Cross Platform with no Dependencies**

C++ Code works with any recent gcc / clang.

## Question 1: Write a sample schema that can represent a property tree (property name, property value, property type, and sub-properties).

We defined a Parrot Schema in `parrot.fbs`

Source: Writing a schema
- https://google.github.io/flatbuffers/flatbuffers_guide_writing_schema.html

## Question 2: Write code snippets in C++ that can read/update on the property object generated by the FlatBuffers compiler.

**Step 1: Download the `flatc` command line compiler**

- choice "folder for installation"
- cd "folder for installation"
- git clone https://github.com/google/flatbuffers.git
- cd flatbuffers
- cmake -G "Unix Makefiles" (install cmake if need)
- make
- sudo ln -s /full-path-to-flatbuffer/flatbuffers/flatc /usr/local/bin/flatc
- chmod +x /full-path-to-flatbuffer/flatbuffers/flatc
- run in any place as "flatc"

Source: How to install flatc and flatbuffers on linux ubuntu
- https://stackoverflow.com/a/55394568

**Step 2: Compile the schema into a CPP header file**

cd back to the root of this directory.

Compile the schema into a CPP header file `generated_parrot.h` with the `parrot.fbs` flatbuffer schema, with features of c++17 standard.

```
flatc -c -o generated_parrot parrot.fbs --cpp-std c++17
```

Source: Using the schema compiler
- https://google.github.io/flatbuffers/flatbuffers_guide_using_schema_compiler.html

**Step 3: Add FlatBuffers as a static library to this CMake project.**

We need to add FlatBuffers as a static library to the project.

1. Create a `lib` folder at the root, and clone the FlatBuffers repository into it

- https://github.com/google/flatbuffers

Remove the `.git` folder in the cloned repository. Source control it as part of this project too.

**Step 4: Write a sample code snippet in C++ that can read on the property object generated by the FlatBuffers compiler, `generated_parrot.h`.**

Please see `read_and_update_parrot.cpp` :)

**Step 5: Add the following instructions to our CMakeLists.txt**

```cmake
cmake_minimum_required(VERSION 3.10)

project(CryptoDotComAssignment)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES qn_2_read_and_update_parrot.cpp)
set(HEADER_FILES qn_2_read_and_update_parrot.h)

# Include generated_parrot to be able to use the generated headers
include_directories(generated_parrot)

# Add the Flatbuffers directory to the CMake build
add_subdirectory(lib/flatbuffers)

# Add the Flatbuffers directory to the CMake build
add_executable(Question2 ${SOURCE_FILES} ${HEADER_FILES})

# Link the Flatbuffers static library only to the target
target_link_libraries(Question2 PRIVATE flatbuffers)
```

**Step 6. Build the Project with CMake**

```sh
// In the root, create a build folder
// This will store our files that are generated by CMake
mkdir build
cd build

// Configure the project and generate a native build system
cmake ..

// Call the build system to compile / link the project
cmake --build .
```

**Step 7: Execute the executable `Question2`**

```sh
➜  build git:(master) ✗ ./Question2    
Parrot name: Polly
Parrot name (directly accessed without deserialization): Polly
Updated Parrot name: UpdatedPolly
```

## Question 3: Write code snippets in C++ that can send/receive the property object over TCP socket.

**Step 1: We will be using the boost library to create a TCP socket.**

Specifically, `boost/asio.hpp`

Download the boost library from https://www.boost.org/users/download/ if you do not have boost yet.

We will use at least 1.58.0

we will not source control boost as a library in the `lib` folder, as its too large.

Instead, we will setup the `CMakeLists.txt` file in abit, to find the boost libraries automatically in our system.

**Step 2: Setup `CMakeLists.txt`**

Specifically, to 
- find the boost library on the user's system, and allow it to be included in our code
- separate the source files and header files for qn 2 and 3 (server + client)
- set separate executables for qn 2 and 3 (server + client)

The `CMakeLists.txt` should look like this:

```cmake
cmake_minimum_required(VERSION 3.10)

project(CryptoDotComAssignment)

set(CMAKE_CXX_STANDARD 17)

# New: separate the source files and header files for qn 2
set(QN_2_SOURCE_FILES qn_2_read_and_update_parrot.cpp)
set(QN_2_HEADER_FILES qn_2_read_and_update_parrot.h)

# New: separate the source files and header files for qn 3, server and client
set(QN_3_SERVER_SOURCE_FILES qn_3_server_socket.cpp)
set(QN_3_SERVER_HEADER_FILES qn_3_server_socket.h)

set(QN_3_CLIENT_SOURCE_FILES qn_3_client_socket.cpp)
set(QN_3_CLIENT_HEADER_FILES qn_3_client_socket.h)

# Include generated_parrot to be able to use the generated headers
include_directories(generated_parrot)

# Add the Flatbuffers directory to the CMake build
add_subdirectory(lib/flatbuffers)

# Force using static libraries - this embeds the boost code directly into the executable
set(Boost_USE_STATIC_LIBS ON)

# New: Add the boost directory to the CMake build
# Boost.Asio is a header-only library; we don't need to build it separately here, and only need to build the dependencies it needs
# Boost.System library is needed as a dependency for Boost.Asio
find_package(Boost 1.58.0 COMPONENTS system REQUIRED)

# New: Include the boost library, so we can include the boost headers in our code
include_directories(${Boost_INCLUDE_DIRS})

# new: Add the executable for Question 2
add_executable(Question2 ${QN_2_SOURCE_FILES} ${QN_2_HEADER_FILES})

# new: Add the executable for Question 3
add_executable(Question3Server ${QN_3_SERVER_SOURCE_FILES} ${QN_3_SERVER_HEADER_FILES})
add_executable(Question3Client ${QN_3_CLIENT_SOURCE_FILES} ${QN_3_CLIENT_HEADER_FILES})

# new: Link the flatbuffers static library only to the target
target_link_libraries(Question2 PRIVATE flatbuffers)

# new: Link the boost library and flatbuffers static libraries to qn 3 server and client targets
target_link_libraries(Question3Server PRIVATE flatbuffers ${Boost_LIBRARIES})
target_link_libraries(Question3Client PRIVATE flatbuffers ${Boost_LIBRARIES})
```

**Step 3: Write a code snippet `qn_3_server_socket.cpp`, which will listen on a TCP socket, and receive the parrot object.**

View the code here `qn_3_server_socket.cpp`

**Step 4: Write a code snippet `qn_3_client_socket.cpp`, which will connect to the server TCP socket, create a parrot flatbuffer object (serialized), and send it over the socket to the server.**

View the code here `qn_3_client_socket.cpp`


**Step 5: Build the project**

```sh
// change directory to build, so we compile the project in the build folder
cd build

// Configure the project and generate a native build system
cmake ..

// Call the build system to compile / link the project
// Now, we will have the two new executables, Question3Server, Question3Client
cmake --build .
```

**Step 6: Run the server and client, each on two separate terminals**

```sh
// Go to the build folder, where the executables are
cd build
```

Run the server. This will be responsible for listening on the socket, receiving the parrot object, and printing it

It should suspend at this point, since it is waiting for the client to send the parrot object over the socket

```sh
./Question3Server
```

It should terminate right away, since the client will send the parrot object over the socket and terminate.
```sh
// Run the client. This will be responsible for connecting to the server, creating a parrot object, and sending it over the socket
./Question3Client
```

We should get this on the server; The server should terminate after printing the parrot object
```sh
➜  build git:(master) ✗ ./Question3Server      
Name: Polly
Color: Red
➜  build git:(master) ✗ 
```

This on the client; The client should terminate after sending the parrot object to the server
```sh
➜  build git:(master) ✗ ./Question3Client
➜  build git:(master) ✗ 
```

## Question 4: Write code snippets in C++ that use the reflection API to read from the TCP socket and iterate over the elements stored inside the property tree.

**Q: What is the Google Flatbuffers Reflection API?**

A: It is a feature that allows us to inspect and manipulate FlatBuffers data at runtime. 

With the reflection API, we can access FlatBuffers data without knowing their schema at compile time. 

This is useful when we want to work with different FlatBuffers schemas that are not known ahead of time, 

or when we want to implement generic tools that can work with any FlatBuffers data.

**Step 1: Generate a binary fbs with flatc**

We will use the `flatc` compiler to generate the reflection schema.

The reflection schema is a FlatBuffers schema that describes the schema of another FlatBuffers schema.

The reflection schema is generated by the `flatc` compiler, and is used by the reflection API.

This command below will generate a file (`parrot.bfbs`) that needs to be read to fully reflect the types inside the .fbs file.

```sh
cd build
flatc -b --schema ../parrot.fbs
```

**Step 2: Create a server socket which will listen on a TCP socket, and receive the parrot object**

- `qn_4_server_socket.cpp`

**Step 3: Create a client socket which will send the parrot object to the server**

- `qn_4_client_socket.cpp`

**Step 4: Update CMakeLists.txt` to add them as executables

```cmake
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

set(QN_4_SERVER_SOURCE_FILES qn_4_client_socket.cpp)
set(QN_4_SERVER_HEADER_FILES qn_4_client_socket.h)

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
```

**Step 5: Build the project**

```sh
// change directory to build, so we compile the project in the build folder
cd build

// Configure the project and generate a native build system
cmake ..

// Call the build system to compile / link the project
// Now, we will have the two new executables, Question4Server, Question4Client
cmake --build .
```

**Step 6: Spin up the server and client, each on two separate terminals**

```sh
// Go to the build folder, where the executables are
cd build

// Run the server. This will be responsible for listening on the socket, receiving the parrot object, and printing it
./Question4Server
```

```sh
// Go to the build folder, where the executables are
cd build

// Run the client. This will be responsible for connecting to the server, creating a parrot object, and sending it over the socket
./Question4Client
```

We should get

Client

```sh
➜  build git:(master) ✗ ./Question4Client
➜  build git:(master) ✗ 
```

Server

```sh
➜  build git:(master) ✗ ./Question4Server              
color: Red
name: Polly
position: x: 1, y: 2, z: 3
talents: (unsupported type)
```