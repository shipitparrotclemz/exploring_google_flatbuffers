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

const Parrot &receive_flatbuffer(tcp::socket &socket, std::vector<uint8_t> &buffer);
void print_parrot(const Parrot &parrot, const reflection::Schema &schema);

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
    const Parrot &received_parrot = receive_flatbuffer(socket, buffer);

    // Use the received FlatBuffer object (e.g., print its name and color)
    print_parrot(received_parrot, *schema);

    return 0;
}

const Parrot &receive_flatbuffer(tcp::socket &socket, std::vector<uint8_t> &buffer) {
    // Read the size of the incoming FlatBuffer
    uint32_t size = 0;
    boost::asio::read(socket, boost::asio::buffer(&size, sizeof(size)));

    // Resize the buffer to the required size
    buffer.resize(size);

    // Read the FlatBuffer data from the socket
    boost::asio::read(socket, boost::asio::buffer(buffer.data(), size));

    // Deserialize the FlatBuffer object
    const Parrot *parrot = flatbuffers::GetRoot<Parrot>(buffer.data());

    // Return the received Parrot object
    return *parrot;
}

void print_parrot(const Parrot &parrot, const reflection::Schema &schema) {
    // Get the root table of the schema
    const reflection::Object *root_table = schema.root_table();

    // Traverse the fields of the root table and print their values
    for (const auto *field : *root_table->fields()) {
        // Access the field's data using the reflection API
        reflection::BaseType elem_type = field->type()->base_type();
        std::cout << field->name()->str() << ": ";

        // Print the field value based on its type
        switch (elem_type) {
            case reflection::BaseType::String: {
                if (strcmp(field->name()->c_str(), "name") == 0) {
                    std::cout << parrot.name()->str();
                }
                break;
            }
            case reflection::BaseType::Byte: { // Assuming the enum is represented as a byte
                if (strcmp(field->name()->c_str(), "color") == 0) {
                    std::cout << EnumNameColor(parrot.color());
                }
                break;
            }
            case reflection::BaseType::Obj: {
                if (strcmp(field->name()->c_str(), "position") == 0) {
                    auto position = parrot.position();
                    std::cout << "x: " << position->x() << ", y: " << position->y() << ", z: " << position->z();
                } else if (strcmp(field->name()->c_str(), "talents") == 0) {
                    auto talents_vec = parrot.talents();
                    std::cout << "[";
                    for (size_t i = 0; i < talents_vec->size(); ++i) {
                        auto talent = talents_vec->Get(i);
                        std::cout << "{name: " << talent->name()->str() << ", level: " << EnumNameLevel(talent->level()) << "}";
                        if (i < talents_vec->size() - 1) {
                            std::cout << ", ";
                        }
                    }
                    std::cout << "]";
                } else {
                    std::cout << "(unsupported object)";
                }
                break;
            }
            default:
                std::cout << "(unsupported type)";
                break;
        }
        std::cout << std::endl;
    }
}