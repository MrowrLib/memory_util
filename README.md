# `#include <memory_util>`

```cpp
#include <memory_util>

void Example() {
    // Read
    auto dog = MemoryUtil::Read<Dog*>(0x69420);

    // Follow pointers to values
    auto number = MemoryUtil::Read<uint32_t>(0x69420, {0x4, 0x0, 0xc});

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

## Installation

```lua
-- xmake
add_repositories("MrowrLib https://github.com/MrowrLib/Packages.git")
add_requires("memory_util")
```

```cmake
# CMake/vcpkg (coming soon)
```

## What?

Some helper functions for reading/writing/searching the current process memory space.

> _And a helpful `Bytes` utility class for managing your bytes!_

## Why?

I was tired of writing the same code over and over again.

This code is especially lovely for following multi-level pointers, e.g.

```cpp
auto number = MemoryUtil::Read<uint32_t>(0x69420, {0x4, 0x0, 0xc});
```

And I needed it for searching for arrays of bytes (AoB) in the current process.

> _I also think the `Bytes` class is adorable and helpful_

## License

Use however, no attribution required.

```
BSD Zero Clause License (SPDX: 0BSD)

Permission to use, copy, modify, and/or distribute this software for any purpose
with or without fee is hereby granted.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
THIS SOFTWARE.
```
