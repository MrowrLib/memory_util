# `#include <memory_util.h>`

```cpp
#include <memory_util.h>

void Example() {
    auto dog = MemoryUtil::Read<Dog*>(0x69420);
}
```

## What?

Some helper functions for reading/writing/searching the current process memory space.

> _And a helpful `Bytes` utility class for managing your bytes!_

## Installation

### xmake

#### `xmake.lua`

```lua
add_repositories("MrowrLib https://github.com/MrowrLib/Packages.git")
add_requires("memory_util")

target("Example")
    add_packages("memory_util")
```

### vcpkg

#### `CMakeLists.txt`

```cmake
add_executable(Example main.cpp)

# Find memory_util and link it to your target
find_package(memory_util CONFIG REQUIRED)
target_link_libraries(Example PRIVATE memory_util::memory_util)
```

#### `vcpkg.json`

```json
{
    "dependencies": ["mrowr-memory-util"]
}
```

#### `vcpkg-configuration.json`

```json
{
    "default-registry": {
        "kind": "git",
        "repository": "https://github.com/microsoft/vcpkg.git",
        "baseline": "95252eadd63118201b0d0df0b4360fa613f0de84"
    },
    "registries": [
        {
            "kind": "git",
            "repository": "https://github.com/MrowrLib/Packages.git",
            "baseline": "6e1884a73e89d614682de6c28107ef888d99f8a1",
            "packages": ["mrowr-memory-util", "mrowr-log", "mrowr-string-format"]
        }
    ]
}
```

> _Update the default-registry baseline to the latest commit from https://github.com/microsoft/vcpkg_  
> _Update the MrowrLib/Packages baseline to the latest commit from https://github.com/MrowrLib/Packages_  
> _**Don't forget to include mrowr-log and mrowr-string-format** (these are dependencies of memory_util)_

## Why?

I needed a way to read/write/search the current process memory space in a way that was easy to use and read.

This code is especially lovely for following multi-level pointers, e.g.

```cpp
auto number = MemoryUtil::Read<uint32_t>(0x69420, {0x4, 0x0, 0xc});
```

And I needed it for searching for arrays of bytes (AoB) in the current process.

> _I also think the `Bytes` class is adorable and helpful!_

## How?

```cpp
#include <memory_util.h>

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
    auto address2 = MemoryUtil::Find("module.dll", "\x01\x02\x03", "x?x");

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

## Logging

This uses the [`_Log_`](https://github.com/MrowrLib/_Log_.cpp) library.

If you have `spdlog` installed, this will automatically log memory write operation details to `stderr`.

To specify a log file: `_LogToFile_("memory_util.log");`

To disable logging: `#define Log(...)` before including `memory_util.h`

> _By default, nothing will be logged unless you have `spdlog`._

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
