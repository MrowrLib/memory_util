#include <stdint.h>

#include <_Log_>
#include <iostream>
#include <memory_util>
#include <string_format>

_LogToFile_("Example.log");

struct SomeRandomStruct {
    uint32_t number1;
    uint32_t number2;
};

SomeRandomStruct StructInstance{.number1 = 69, .number2 = 420};

int main() {
    auto addressOfStructInstance = reinterpret_cast<uintptr_t>(&StructInstance);

    auto firstNumber  = MemoryUtil::Read<uint32_t>(addressOfStructInstance, 0);
    auto secondNumber = MemoryUtil::Read<uint32_t>(addressOfStructInstance, 4);
    std::cout << string_format("First number: {}", firstNumber) << std::endl;
    std::cout << string_format("Second number: {}", secondNumber) << std::endl;

    MemoryUtil::Write(addressOfStructInstance, MemoryUtil::Bytes{}.Add32(12345).GetBytes());
    MemoryUtil::Write(addressOfStructInstance + 4, MemoryUtil::Bytes{}.Add32(67890).GetBytes());

    firstNumber  = MemoryUtil::Read<uint32_t>(addressOfStructInstance, 0);
    secondNumber = MemoryUtil::Read<uint32_t>(addressOfStructInstance, 4);
    std::cout << string_format("Changed First number: {}", firstNumber) << std::endl;
    std::cout << string_format("Changed Second number: {}", secondNumber) << std::endl;
}
