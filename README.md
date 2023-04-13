# `#include <memory_util>`

```cpp
#include <memory_util>

void Example() {
    // Read
    auto dog = MemoryUtil::Read<Dog*>(0x69420);

    // Write
    MemoryUtil::Write(0x69420, {0x01});
    MemoryUtil::WriteProtected(0x69420, {0x01, 0x02}); // VirtualProtect

    // Allocate
    auto address1 = MemoryUtil::Allocate(2048);

    // Free
    MemoryUtil::Free(address1);

    // Search for an Array of Bytes (with optional mask)
    auto address2 = MemoryUtil::Find("program.exe", "\x01\x02\x03", "x?x");

    // Helpful Bytes
    Bytes bytes;
    bytes.AddByte(0x01);
    bytes.AddBytes({0x02, 0x03});
    bytes.AddWord(0x0405);
    bytes.AddDword(0x06070809);
    bytes.AddAddress(address1);

    std::cout << bytes.ToHexString() << std::endl;
}
```
