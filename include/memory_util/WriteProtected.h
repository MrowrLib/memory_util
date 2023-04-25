
#pragma once

#include <Windows.h>  // VirtualProtect
//
#include <_Log_.h>

#include <cstdint>
#include <vector>

#include "Bytes.h"

namespace MemoryUtil {

    void WriteProtected(
        uintptr_t address, const std::vector<uint8_t>& bytes, size_t maxBytesToLog = 128
    ) {
        _Log_("Writing {} protected bytes to address {:x}", bytes.size(), address);
        if (bytes.size() < maxBytesToLog) _Log_("Bytes: " + ToHexString(bytes));
        DWORD oldProtect;
        VirtualProtect((void*)address, bytes.size(), PAGE_EXECUTE_READWRITE, &oldProtect);
        memcpy((void*)address, bytes.data(), bytes.size());
        VirtualProtect((void*)address, bytes.size(), oldProtect, &oldProtect);
    }
}
