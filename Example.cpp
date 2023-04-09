#include <Logging.h>
#include <Memory.h>
#include <StringFormatting.h>
#include <stdint.h>

#include <iostream>

SetLogFilePath("Example.log");

struct SomeRandomStruct {
    uint32_t number1;
    uint32_t number2;
};

SomeRandomStruct StructInstance{.number1 = 69, .number2 = 420};

int main() {
    auto addressOfStructInstance = reinterpret_cast<uintptr_t>(&StructInstance);

    auto firstNumber  = Memory::Read<uint32_t>(addressOfStructInstance, 0);
    auto secondNumber = Memory::Read<uint32_t>(addressOfStructInstance, 4);
    std::cout << string_format("First number: {}", firstNumber) << std::endl;
    std::cout << string_format("Second number: {}", secondNumber) << std::endl;

    Memory::Write(addressOfStructInstance, Memory::Bytes{}.Add32(12345).GetBytes());
    Memory::Write(addressOfStructInstance + 4, Memory::Bytes{}.Add32(67890).GetBytes());

    firstNumber  = Memory::Read<uint32_t>(addressOfStructInstance, 0);
    secondNumber = Memory::Read<uint32_t>(addressOfStructInstance, 4);
    std::cout << string_format("Changed First number: {}", firstNumber) << std::endl;
    std::cout << string_format("Changed Second number: {}", secondNumber) << std::endl;
}
