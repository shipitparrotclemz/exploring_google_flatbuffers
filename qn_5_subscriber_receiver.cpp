//
// Created by Goh Chang Ming Clement on 3/19/23.
//

#include "qn_5_subscriber_receiver.h"
#include <boost/asio.hpp>
#include <vector>
#include <iostream>
#include "qn_5_subscriber_receiver.h"

using boost::asio::ip::tcp;

void read_property_tree_update(tcp::socket& socket, std::vector<uint8_t>& buffer);

int main() {
    boost::asio::io_context io_context;
    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve("127.0.0.1", "8899");

    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);

    std::vector<uint8_t> buffer;
    read_property_tree_update(socket, buffer);

    // Deserialize the property tree update using Flatbuffers
    // auto update = GetPropertyTreeUpdate(buffer.data());
    std::cout << "deserialize the property tree updates" << std::endl;

    // Update the local property tree with the received update)
    std::cout << "update the local property tree with the received update" << std::endl;

    return 0;
}

void read_property_tree_update(tcp::socket& socket, std::vector<uint8_t>& buffer) {
    uint32_t size = 0;
    boost::asio::read(socket, boost::asio::buffer(&size, sizeof(size)));

    buffer.resize(size);
    boost::asio::read(socket, boost::asio::buffer(buffer.data(), buffer.size()));
}