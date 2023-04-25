#pragma once

#include <Windows.h>  // VirtualAlloc
#include <_Log_.h>

#include <stdexcept>

namespace MemoryUtil {

    //! Allocates memory using VirtualAlloc
    uintptr_t Allocate(size_t size) {
        _Log_("Allocating {} bytes", size);
        auto addressPtr = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        if (addressPtr == nullptr) throw std::runtime_error("Failed to allocate memory");
        auto address = reinterpret_cast<uintptr_t>(addressPtr);
        _Log_("Allocated at address {:x}", address);
        return address;
    }
}
