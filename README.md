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


