//
// Created by Goh Chang Ming Clement on 3/18/23.
//

#include "qn_4_client_socket.h"
#include <boost/asio.hpp>
#include <vector>
#include "parrot_generated.h"

using boost::asio::ip::tcp;
using boost::asio::ip::tcp;

void send_parrot(tcp::socket &socket, const std::vector<uint8_t> &buffer);

int main() {
    // Initialize a Boost.Asio io_context
    boost::asio::io_context io_context;

    // Connect to the server (replace "localhost" and "1234" with your server's address and port)
    tcp::resolver resolver(io_context);
    tcp::socket socket(io_context);
    boost::asio::connect(socket, resolver.resolve("localhost", "8899"));

    flatbuffers::FlatBufferBuilder builder;

    // This is the position of the parrot in the 3D space, as a serialized buffer
    auto position = ParrotSchema::CreatePosition(builder, 1.0f, 2.0f, 3.0f);

    // Create a Talking Talent, as a serialized buffer
    auto talking_talent_name = builder.CreateString("Talking");
    auto talking_talent = ParrotSchema::CreateTalent(builder, talking_talent_name, ParrotSchema::Level_Two);

    // Create a Singing Talent, as a serialized buffer
    auto singing_talent_name = builder.CreateString("Singing");
    auto singing_talent = ParrotSchema::CreateTalent(builder, singing_talent_name, ParrotSchema::Level_Three);

    // Create Parrot, as a serialized buffer
    auto parrot_name = builder.CreateString("Polly");
    auto talents_vector = builder.CreateVector(std::vector<flatbuffers::Offset<ParrotSchema::Talent>>({talking_talent, singing_talent}));
    auto parrot = ParrotSchema::CreateParrot(builder, position, parrot_name, ParrotSchema::Color_Red, talents_vector);

    // Finish the buffer
    builder.Finish(parrot);

    // Send the Parrot object (serialized as a FlatBuffer) over the socket
    send_parrot(socket, std::vector<uint8_t>(builder.GetBufferPointer(), builder.GetBufferPointer() + builder.GetSize()));

    return 0;
}

void send_parrot(tcp::socket &socket, const std::vector<uint8_t> &buffer) {
    // Send the size of the FlatBuffer as a 4-byte unsigned integer
    auto size = static_cast<uint32_t>(buffer.size());
    boost::asio::write(socket, boost::asio::buffer(&size, sizeof(size)));

    // Send the FlatBuffer data over the socket
    boost::asio::write(socket, boost::asio::buffer(buffer.data(), buffer.size()));
}