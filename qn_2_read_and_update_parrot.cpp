#include "flatbuffers/flatbuffers.h"
#include <iostream>
#include "generated_parrot/parrot_generated.h"

int main() {
    /**
     * Q: How do we create a FlatBuffer object?
     */
    flatbuffers::FlatBufferBuilder builder;

    // Create Position
    auto position = ParrotSchema::CreatePosition(builder, 1.0f, 2.0f, 3.0f);

    // Create Talent
    auto talent_name = builder.CreateString("Talking");
    auto talent = ParrotSchema::CreateTalent(builder, talent_name, ParrotSchema::Level_Two);

    // Create Parrot
    auto parrot_name = builder.CreateString("Polly");
    auto talents_vector = builder.CreateVector(std::vector<flatbuffers::Offset<ParrotSchema::Talent>>({talent}));
    auto parrot = ParrotSchema::CreateParrot(builder, position, parrot_name, ParrotSchema::Color_Red, talents_vector);

    // Finish the buffer
    builder.Finish(parrot);

    // Deserialize the original Parrot object
    auto deserialized_parrot = ParrotSchema::GetParrot(builder.GetBufferPointer());
    std::cout << "Parrot name: " << deserialized_parrot->name()->str() << std::endl;

    /**
     * Q: Doesn't FlatBuffer allow us to access the name directly from the buffer, without deserializing the entire object?
     * A: Yes!
     */

    // Get the buffer pointer and size
    uint8_t *buffer = builder.GetBufferPointer();
    size_t size = builder.GetSize();

    // Access the Parrot's name directly from the buffer
    // get a pointer to the Parrot table in the buffer
    auto parrot_table = flatbuffers::GetRoot<ParrotSchema::Parrot>(buffer);

    // access the name property directly from the buffer without deserializing the entire object
    auto direct_parrot_name = parrot_table->name()->str();

    // This approach is more efficient than deserializing the entire object
    // especially when we only need to access a few properties.
    // However, if we need to access most or all properties of the object...
    // deserializing the entire object may be more convenient.

    // Print the Parrot's name
    std::cout << "Parrot name (directly accessed without deserialization): " << direct_parrot_name << std::endl;

    /**
     * Q: How do we update the Parrot's name?
     * A: FlatBuffers are designed to be immutable once they are created
     * We cannot directly modify the properties of the deserialized object.
     * However, We can create a new FlatBuffer with the updated properties.
     * Create a new Parrot object with the updated name
     */

    // Update the Parrot's name
    std::string new_parrot_name = "UpdatedPolly";

    flatbuffers::FlatBufferBuilder updated_builder;

    auto new_name_offset = updated_builder.CreateString(new_parrot_name);
    auto updated_position = ParrotSchema::CreatePosition(updated_builder, deserialized_parrot->position()->x(), deserialized_parrot->position()->y(), deserialized_parrot->position()->z());

    // Create a new talent offset using the updated_builder
    auto updated_talent_name = updated_builder.CreateString("Talking");
    auto updated_talent = ParrotSchema::CreateTalent(updated_builder, updated_talent_name, ParrotSchema::Level_Two);
    auto updated_talents_vector = updated_builder.CreateVector(std::vector<flatbuffers::Offset<ParrotSchema::Talent>>({updated_talent}));

    auto updated_parrot = ParrotSchema::CreateParrot(updated_builder, updated_position, new_name_offset, deserialized_parrot->color(), updated_talents_vector);

    // Finish the updated buffer
    updated_builder.Finish(updated_parrot);

    // Deserialize and print the updated data
    auto deserialized_updated_parrot = ParrotSchema::GetParrot(updated_builder.GetBufferPointer());
    std::cout << "Updated Parrot name: " << deserialized_updated_parrot->name()->str() << std::endl;

    return 0;
}