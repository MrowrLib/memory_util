#pragma once

#include <Windows.h>

#include <_Log_>
#include <cstdint>
#include <string_format>

#include "Bytes.h"


namespace MemoryUtil {

    void Write(uintptr_t address, const std::vector<uint8_t>& bytes) {
        _Log_("Writing {} bytes to address {:x}", bytes.size(), address);
        if (bytes.size() < 128) _Log_(Bytes{bytes}.ToHexString());
        for (size_t i = 0; i < bytes.size(); i++) *(uint8_t*)(address + i) = bytes[i];
    }

    void WriteProtected(uintptr_t address, const std::vector<uint8_t>& bytes) {
        _Log_("Writing {} protected bytes to address {:x}", bytes.size(), address);
        if (bytes.size() < 128) _Log_(Bytes{bytes}.ToHexString());
        DWORD oldProtect;
        VirtualProtect((void*)address, bytes.size(), PAGE_EXECUTE_READWRITE, &oldProtect);
        memcpy((void*)address, bytes.data(), bytes.size());
        VirtualProtect((void*)address, bytes.size(), oldProtect, &oldProtect);
    }

    uintptr_t Allocate(size_t size) {
        _Log_("Allocating {} bytes", size);
        auto addressPtr = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        if (addressPtr == nullptr) throw std::runtime_error("Failed to allocate memory");
        auto address = reinterpret_cast<uintptr_t>(addressPtr);
        _Log_("Allocated at address {:x}", address);
        return address;
    }

    void Free(uintptr_t address) {
        _Log_("Freeing memory at address {:x}", address);
        if (VirtualFree((void*)address, 0, MEM_RELEASE))
            _Log_("Freed memory at address {:x}", address);
        else
            throw std::runtime_error(string_format("Failed to free memory at address {:x}", address)
            );
    }
}
