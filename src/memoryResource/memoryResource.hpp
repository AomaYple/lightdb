#pragma once

#include <memory_resource>

namespace lightdb::internal {
    [[nodiscard]] auto getSyncMemoryResource() -> std::pmr::memory_resource *;

    [[nodiscard]] auto getUnsyncMemoryResource() -> std::pmr::memory_resource *;
}    // namespace lightdb::internal
