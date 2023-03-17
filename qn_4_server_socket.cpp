//
// Created by Goh Chang Ming Clement on 3/18/23.
//

#include "qn_4_server_socket.h"
#include <boost/asio.hpp>
#include <iostream>
#include <vector>
#include "parrot_generated.h"
#include "flatbuffers/reflection.h"
#include "flatbuffers/util.h"

using boost::asio::ip::tcp;
using namespace ParrotSchema;

const flatbuffers::Table &receive_flatbuffer(tcp::socket &socket, std::vector<uint8_t> &buffer);
void print_parrot(const flatbuffers::Table &table, const reflection::Schema &schema);

int main() {
    // Initialize a Boost.Asio io_context
    boost::asio::io_context io_context;

    // Create an acceptor to listen for incoming connections
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8899));

    // Wait for a connection
    tcp::socket socket(io_context);
    acceptor.accept(socket);

    // Load the binary schema (.bfbs) file
    std::string schema_data;
    bool success = flatbuffers::LoadFile("parrot.bfbs", true, &schema_data);
    assert(success);

    // Parse the binary schema
    flatbuffers::Verifier verifier(reinterpret_cast<const uint8_t *>(schema_data.data()), schema_data.size());
    assert(reflection::VerifySchemaBuffer(verifier));
    const reflection::Schema *schema = flatbuffers::GetRoot<reflection::Schema>(schema_data.data());

    // Receive the FlatBuffer object
    std::vector<uint8_t> buffer;
    const flatbuffers::Table &received_flatbuffer = receive_flatbuffer(socket, buffer);

    // Use the received FlatBuffer object (e.g., print its name and color)
    print_parrot(received_flatbuffer, *schema);

    return 0;
}

const flatbuffers::Table &receive_flatbuffer(tcp::socket &socket, std::vector<uint8_t> &buffer) {
    // Read the size of the incoming FlatBuffer
    uint32_t size = 0;
    boost::asio::read(socket, boost::asio::buffer(&size, sizeof(size)));

    // Resize the buffer to the required size
    buffer.resize(size);

    // Read the FlatBuffer data from the socket
    boost::asio::read(socket, boost::asio::buffer(buffer.data(), size));

    // Deserialize the FlatBuffer object
    const flatbuffers::Table *table = reinterpret_cast<const flatbuffers::Table *>(buffer.data());

    // Return the received FlatBuffer object
    return *table;
}

void print_parrot(const flatbuffers::Table &table, const reflection::Schema &schema) {
    // Get the root table of the schema
    const reflection::Object *root_table = schema.root_table();

    // Traverse the fields of the root table and print their values
    for (const auto *field : *root_table->fields()) {
        // Access the field's data using the reflection API
        reflection::BaseType elem_type = field->type()->base_type();
        auto field_offset = field->offset();
        std::cout << field->name()->str() << ": ";

        // Print the field value based on its type
        switch (elem_type) {
            case reflection::BaseType::String: {
                auto str = table.GetPointer<const flatbuffers::String *>(field_offset);
                if (str) {
                    std::cout << str->str();
                } else {
                    std::cout << "(null)";
                }
                break;
            }
            case reflection::BaseType::Byte: { // Assuming the enum is represented as a byte
                auto enum_val = table.GetField<int8_t>(field_offset, 0);
                auto enum_def = schema.enums()->Get(field->type()->index());
                auto enum_name = enum_def->values()->LookupByKey(enum_val)->name();
                std::cout << enum_name->str();
                break;
            }
                // Add more cases for other types if necessary
            default:
                std::cout << "(unsupported type)";
                break;
        }
        std::cout << std::endl;
    }
}