#pragma once

#include "../memoryResource/memoryResource.hpp"

#include <memory>

namespace lightdb::internal {
    class SkipList {
    public:
        struct Node {
            [[nodiscard]] auto operator new(std::size_t bytes) -> void *;

            auto operator delete(void *pointer, std::size_t bytes) noexcept -> void;

            std::shared_ptr<std::pmr::vector<std::byte>> data{
                std::allocate_shared<std::pmr::vector<std::byte>>(std::pmr::polymorphic_allocator{getMemoryResource()},
                                                                  std::pmr::vector<std::byte>{getMemoryResource()})};
            Node *next{}, *down{};
        };

    private:
        static constexpr std::uint8_t maxHeight{12};

        std::array<Node, maxHeight> levels{[] constexpr {
            std::array<Node, maxHeight> levels{};
            for (std::uint8_t i{std::size(levels) - 1}; i != 0; --i) levels[i].down = std::addressof(levels[i - 1]);

            return levels;
        }()};
    };

    [[nodiscard]] auto operator==(const SkipList::Node &, const SkipList::Node &) -> bool;

    [[nodiscard]] auto operator<=>(const SkipList::Node &, const SkipList::Node &) -> std::strong_ordering;
}    // namespace lightdb::internal
