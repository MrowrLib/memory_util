
#pragma once

#include <_Log_.h>

#include <cstdint>
#include <vector>

#include "Bytes.h"

namespace MemoryUtil {

    void Write(uintptr_t address, const std::vector<uint8_t>& bytes, size_t maxBytesToLog = 128) {
        _Log_("Writing {} bytes to address {:x}", bytes.size(), address);
        if (bytes.size() < maxBytesToLog) _Log_("Bytes: " + ToHexString(bytes));
        for (size_t i = 0; i < bytes.size(); i++) *(uint8_t*)(address + i) = bytes[i];
    }
}
