#pragma once

#include <memory>
#include <vector>

namespace lightdb::internal {
    class SkipList {
    public:
        struct Node {
            [[nodiscard]] auto operator new(std::size_t bytes) -> void *;

            auto operator delete(void *pointer, std::size_t bytes) noexcept -> void;

            std::shared_ptr<std::pmr::vector<std::byte>> data;
            Node *next, *down;
        };
    };

    [[nodiscard]] auto operator==(const SkipList::Node &, const SkipList::Node &) -> bool;

    [[nodiscard]] auto operator<=>(const SkipList::Node &, const SkipList::Node &) -> std::strong_ordering;
}    // namespace lightdb::internal
