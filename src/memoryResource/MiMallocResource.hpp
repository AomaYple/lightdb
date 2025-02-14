#pragma once

#include <memory_resource>

namespace lightdb::internal {
    class MiMallocResource final : public std::pmr::memory_resource {
    public:
        constexpr MiMallocResource() noexcept = default;

        MiMallocResource(const MiMallocResource &) = delete;

        auto operator=(const MiMallocResource &) -> MiMallocResource & = delete;

        MiMallocResource(MiMallocResource &&) noexcept = delete;

        auto operator=(MiMallocResource &&) noexcept -> MiMallocResource & = delete;

        ~MiMallocResource() override = default;

        [[nodiscard]] auto do_allocate(std::size_t bytes, std::size_t alignment) -> void * override;

        auto do_deallocate(void *pointer, std::size_t bytes, std::size_t alignment) noexcept -> void override;

        [[nodiscard]] auto do_is_equal(const memory_resource &other) const noexcept -> bool override;
    };
}    // namespace lightdb::internal
