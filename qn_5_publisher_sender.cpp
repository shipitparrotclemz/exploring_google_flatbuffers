//
// Created by Goh Chang Ming Clement on 3/19/23.
//

#include "qn_5_publisher_sender.h"
#include <boost/asio.hpp>
#include <vector>
#include <set>
#include <thread>
#include <iostream>

using boost::asio::ip::tcp;

void handle_client(std::shared_ptr<tcp::socket> socket, std::set<std::shared_ptr<tcp::socket>>& clients);

int main() {
    boost::asio::io_context io_context;
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8899));

    std::set<std::shared_ptr<tcp::socket>> clients;

    auto socket = std::make_shared<tcp::socket>(io_context);
    acceptor.accept(*socket);
    std::thread(handle_client, socket, std::ref(clients)).detach();

    return 0;
}

void handle_client(std::shared_ptr<tcp::socket> socket, std::set<std::shared_ptr<tcp::socket>>& clients) {
    clients.insert(socket);

    // Example: Send property tree updates to all clients
    while (true) {
        // ... (Update the property tree)

        // Serialize the property tree update using Flatbuffers
        // flatbuffers::FlatBufferBuilder builder;
        // ... (Build the Flatbuffer using the builder)

        // Send the update to all clients
        for (const auto& client : clients) {
            // Send the size of the FlatBuffer as a 4-byte unsigned integer
            uint32_t size = builder.GetSize();
            boost::asio::write(*client, boost::asio::buffer(&size, sizeof(size)));

            // Send the FlatBuffer data
            boost::asio::write(*client, boost::asio::buffer(builder.GetBufferPointer(), builder.GetSize()));
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}