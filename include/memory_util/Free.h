#pragma once

#include <Windows.h>  // VirtualFree
#include <_Log_.h>
#include <string_format.h>

#include <cstdint>
#include <stdexcept>

namespace MemoryUtil {

    void Free(uintptr_t address) {
        _Log_("Freeing memory at address {:x}", address);
        if (VirtualFree((void*)address, 0, MEM_RELEASE))
            _Log_("Freed memory at address {:x}", address);
        else
            throw std::runtime_error(string_format("Failed to free memory at address {:x}", address)
            );
    }
}
