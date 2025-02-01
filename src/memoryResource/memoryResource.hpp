#pragma once

#include <memory_resource>

namespace lightdb::internal {
    [[nodiscard]] auto getMemoryResource() -> std::pmr::memory_resource *;
}    // namespace lightdb::internal
