#include "qn_3_server_socket.h"
#include <boost/asio.hpp>
#include <iostream>
#include <vector>
#include "parrot_generated.h"

using boost::asio::ip::tcp;
using namespace ParrotSchema;

const Parrot &receive_parrot(tcp::socket &socket, std::vector<uint8_t> &buffer);

int main() {
    // Initialize a Boost.Asio io_context
    boost::asio::io_context io_context;

    // Create an acceptor to listen for incoming connections
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 1234));

    // Wait for a connection
    tcp::socket socket(io_context);
    acceptor.accept(socket);

    // Receive the Parrot object
    std::vector<uint8_t> buffer;
    const Parrot &received_parrot = receive_parrot(socket, buffer);

    // Use the received Parrot object (e.g., print its name and color)
    std::cout << "Name: " << received_parrot.name()->str() << std::endl;
    std::cout << "Color: " << EnumNameColor(received_parrot.color()) << std::endl;

    return 0;
}

const Parrot &receive_parrot(tcp::socket &socket, std::vector<uint8_t> &buffer) {
    // Read the size of the incoming FlatBuffer
    uint32_t size = 0;
    boost::asio::read(socket, boost::asio::buffer(&size, sizeof(size)));

    // Resize the buffer to the required size
    buffer.resize(size);

    // Read the FlatBuffer data from the socket
    boost::asio::read(socket, boost::asio::buffer(buffer.data(), size));

    // Deserialize the Parrot object from the FlatBuffer
    const Parrot *parrot = GetParrot(buffer.data());

    // Return the received Parrot object
    return *parrot;
}