#include <boost/asio.hpp>
#include <vector>
#include "parrot_generated.h"
#include "flatbuffers/reflection.h"
#include "flatbuffers/util.h"
#include <iostream>

using boost::asio::ip::tcp;

void read_parrot(tcp::socket &socket, std::vector<uint8_t> &buffer);
void iterate_fields(const flatbuffers::Table *table, const reflection::Object *object, const reflection::Schema *schema);

int main() {
    // Initialize a Boost.Asio io_context
    boost::asio::io_context io_context;

    // Create an acceptor to listen for incoming connections
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8899));

    // Wait for a connection
    tcp::socket socket(io_context);
    acceptor.accept(socket);

    // Receive the Parrot object (serialized as a FlatBuffer) over the socket
    std::vector<uint8_t> buffer;
    read_parrot(socket, buffer);

    // Load the binary schema
    std::string bfbsfile;
    bool is_loaded = flatbuffers::LoadFile("parrot.bfbs", true, &bfbsfile);
    if (!is_loaded) {
        std::cerr << "Failed to load binary schema file." << std::endl;
        return 1;
    }

    // Verify the binary schema
    flatbuffers::Verifier verifier(reinterpret_cast<const uint8_t *>(bfbsfile.c_str()), bfbsfile.length());
    if (!reflection::VerifySchemaBuffer(verifier)) {
        std::cerr << "Invalid binary schema file." << std::endl;
        return 1;
    }

    // Get the schema
    const reflection::Schema *schema = reflection::GetSchema(bfbsfile.c_str());

    // Verify the received FlatBuffer using reflection
    if (!flatbuffers::Verify(*schema, *schema->root_table(), buffer.data(), buffer.size())) {
        std::cerr << "Invalid FlatBuffer received." << std::endl;
        return 1;
    }

    // Get the root table
    auto parrot = flatbuffers::GetAnyRoot(buffer.data());

    // Iterate through the fields of the Parrot object using reflection
    auto parrot_object = schema->root_table();
    iterate_fields(parrot, parrot_object, schema);

    return 0;
}

void read_parrot(tcp::socket &socket, std::vector<uint8_t> &buffer) {
    // Receive the size of the FlatBuffer as a 4-byte unsigned integer
    uint32_t size = 0;
    boost::asio::read(socket, boost::asio::buffer(&size, sizeof(size)));

    // Receive the FlatBuffer data over the socket
    buffer.resize(size);
    boost::asio::read(socket, boost::asio::buffer(buffer.data(), buffer.size()));
}

void iterate_fields(const flatbuffers::Table *table, const reflection::Object *object, const reflection::Schema *schema) {
    for (const reflection::Field *field : *object->fields()) {
        std::cout << "Field name: " << field->name()->str() << ", type: " << field->type()->base_type() << std::endl;
        if (!table) {
            std::cout << "Null table for field: " << field->name()->str() << std::endl;
            continue;
        }
        switch (field->type()->base_type()) {
            case reflection::BaseType::None: {
                std::cout << "None type, no value" << std::endl;
                break;
            }
            case reflection::BaseType::UType: {
                std::cout << "UType: " << table->GetField<uint8_t>(field->offset(), 0) << std::endl;
                break;
            }
            case reflection::BaseType::Bool: {
                std::cout << "Bool: " << table->GetField<uint8_t>(field->offset(), 0) << std::endl;
                break;
            }
            case reflection::BaseType::Byte: {
                std::cout << "Byte: " << static_cast<unsigned int>(table->GetField<uint8_t>(field->offset(), 0)) << std::endl;
                break;
            }
            case reflection::BaseType::UByte: {
                std::cout << "UByte: " << static_cast<unsigned int>(table->GetField<uint8_t>(field->offset(), 0)) << std::endl;
                break;
            }
            case reflection::BaseType::Short: {
                std::cout << "Short: " << table->GetField<int16_t>(field->offset(), 0) << std::endl;
                break;
            }
            case reflection::BaseType::UShort: {
                std::cout << "UShort: " << table->GetField<uint16_t>(field->offset(), 0) << std::endl;
                break;
            }
            case reflection::BaseType::Int: {
                std::cout << "Int: " << table->GetField<int32_t>(field->offset(), 0) << std::endl;
                break;
            }
            case reflection::BaseType::UInt: {
                std::cout << "UInt: " << table->GetField<uint32_t>(field->offset(), 0) << std::endl;
                break;
            }
            case reflection::BaseType::Long: {
                std::cout << "Long: " << table->GetField<int64_t>(field->offset(), 0) << std::endl;
                break;
            }
            case reflection::BaseType::ULong: {
                std::cout << "ULong: " << table->GetField<uint64_t>(field->offset(), 0) << std::endl;
                break;
            }
            case reflection::BaseType::Float: {
                std::cout << "Float: " << table->GetField<float>(field->offset(), 0) << std::endl;
                break;
            }
            case reflection::BaseType::Double: {
                std::cout << "Double: " << table->GetField<double>(field->offset(), 0) << std::endl;
                break;
            }
            case reflection::BaseType::String: {
                auto str = table->GetPointer<const flatbuffers::String *>(field->offset());
                if (str) {
                    std::cout << "String value: " << str->str() << std::endl;
                } else {
                    std::cout << "Null string value" << std::endl;
                }
                break;
            }
            case reflection::BaseType::Vector: {
                if (field->type()->element() == reflection::BaseType::Obj) {
                    // Vector of tables
                    auto vec = table->GetPointer<const flatbuffers::Vector<const flatbuffers::Table *> *>(field->offset());

                    if (vec) {
                        std::cout << "Vector size: " << vec->size() << std::endl;
                        for (size_t i = 0; i < vec->size(); ++i) {
                            const flatbuffers::Table *sub_table = vec->Get(i);
                            if (sub_table) {
                                const reflection::Object *sub_object = schema->objects()->Get(field->type()->index());
                                std::cout << "Table at index " << i << ":" << std::endl;
                                std::cout << "Iterating fields for index " << i << ":" << std::endl;
                                iterate_fields(sub_table, sub_object, schema);
                            } else {
                                std::cout << "Null table at index " << i << std::endl;
                            }
                        }
                    } else {
                        std::cout << "Null vector" << std::endl;
                    }
                } else {
                    // Vector of scalars
                    std::cout << "Vector of scalars: ";
                    switch (field->type()->element()) {
                        case reflection::BaseType::String: {
                            auto str = table->GetPointer<const flatbuffers::String *>(field->offset());
                            if (str) {
                                std::cout << "String value: " << str->str() << std::endl;
                            } else {
                                std::cout << "Null string value" << std::endl;
                            }
                            break;
                        }
                        case reflection::BaseType::UType:
                        case reflection::BaseType::Bool:
                        case reflection::BaseType::UByte: {
                            auto vec = table->GetPointer<const flatbuffers::Vector<uint8_t> *>(field->offset());
                            std::cout << "size: " << vec->size() << std::endl;
                            for (size_t i = 0; i < vec->size(); ++i) {
                                std::cout << "Value at index " << i << ": " << static_cast<unsigned int>(vec->Get(i)) << std::endl;
                            }
                            break;
                        }
                        case reflection::BaseType::Byte: {
                            auto vec = table->GetPointer<const flatbuffers::Vector<uint8_t> *>(field->offset());
                            std::cout << "size: " << vec->size() << std::endl;
                            for (size_t i = 0; i < vec->size(); ++i) {
                                std::cout << "Value at index " << i << ": " << static_cast<int>(vec->Get(i)) << std::endl;
                            }
                            break;
                        }
                        case reflection::BaseType::Short: {
                            auto vec = table->GetPointer<const flatbuffers::Vector<int16_t> *>(field->offset());
                            std::cout << "size: " << vec->size() << std::endl;
                            for (size_t i = 0; i < vec->size(); ++i) {
                                std::cout << "Value at index " << i << ": " << vec->Get(i) << std::endl;
                            }
                            break;
                        }
                        case reflection::BaseType::UShort: {
                            auto vec = table->GetPointer<const flatbuffers::Vector<uint16_t> *>(field->offset());
                            std::cout << "size: " << vec->size() << std::endl;
                            for (size_t i = 0; i < vec->size(); ++i) {
                                std::cout << "Value at index " << i << ": " << vec->Get(i) << std::endl;
                            }
                            break;
                        }
                        case reflection::BaseType::Int: {
                            auto vec = table->GetPointer<const flatbuffers::Vector<int32_t> *>(field->offset());
                            std::cout << "size: " << vec->size() << std::endl;
                            for (size_t i = 0; i < vec->size(); ++i) {
                                std::cout << "Value at index " << i << ": " << vec->Get(i) << std::endl;
                            }
                            break;
                        }
                        case reflection::BaseType::UInt: {
                            auto vec = table->GetPointer<const flatbuffers::Vector<uint32_t> *>(field->offset());
                            std::cout << "size: " << vec->size() << std::endl;
                            for (size_t i = 0; i < vec->size(); ++i) {
                                std::cout << "Value at index " << i << ": " << vec->Get(i) << std::endl;
                            }
                            break;
                        }
                        case reflection::BaseType::Long: {
                            auto vec = table->GetPointer<const flatbuffers::Vector<int64_t> *>(field->offset());
                            if (vec) {
                                std::cout << "size: " << vec->size() << std::endl;
                                for (size_t i = 0; i < vec->size(); ++i) {
                                    std::cout << "Value at index " << i << ": " << vec->Get(i) << std::endl;
                                }
                            } else {
                                std::cout << "Null vector value" << std::endl;
                            }
                            break;
                        }
                        case reflection::BaseType::ULong: {
                            auto vec = table->GetPointer<const flatbuffers::Vector<uint64_t> *>(field->offset());
                            if (vec) {
                                std::cout << "size: " << vec->size() << std::endl;
                                for (size_t i = 0; i < vec->size(); ++i) {
                                    std::cout << "Value at index " << i << ": " << vec->Get(i) << std::endl;
                                }
                                break;
                            } else {
                                std::cout << "Null vector value" << std::endl;
                            }
                            break;
                        }
                        case reflection::BaseType::Float: {
                            auto vec = table->GetPointer<const flatbuffers::Vector<float> *>(field->offset());
                            if (vec) {
                                std::cout << "size: " << vec->size() << std::endl;
                                for (size_t i = 0; i < vec->size(); ++i) {
                                    std::cout << "Value at index " << i << ": " << vec->Get(i) << std::endl;
                                }
                            } else {
                                std::cout << "Null vector value" << std::endl;
                            }
                            break;
                        }
                        case reflection::BaseType::Double: {
                            auto vec = table->GetPointer<const flatbuffers::Vector<double> *>(field->offset());
                            if (vec) {
                                std::cout << "size: " << vec->size() << std::endl;
                                for (size_t i = 0; i < vec->size(); ++i) {
                                    std::cout << "Value at index " << i << ": " << vec->Get(i) << std::endl;
                                }
                            } else {
                                std::cout << "Null vector value" << std::endl;
                            }
                            break;
                        }
                        default:
                            std::cout << "Unhandled scalar type: " << field->type()->element();
                            break;
                    }
                }
                break;
            }
            case reflection::BaseType::Obj: {
                auto sub_table = table->GetPointer<const flatbuffers::Table *>(field->offset());
                const reflection::Object *sub_object = schema->objects()->Get(field->type()->index());
                iterate_fields(sub_table, sub_object, schema);
                break;
            }
            case reflection::BaseType::Union: {
                std::cout << "Union type, not supported in this example" << std::endl;
                break;
            }
            case reflection::BaseType::Array: {
                std::cout << "Array type, not supported in this example" << std::endl;
                break;
            }
            default:
                std::cout << "Unhandled field type: " << field->type()->base_type() << std::endl;
                break;
        }
    }
}