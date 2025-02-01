#pragma once

#include "../memoryResource/memoryResource.hpp"

#include <memory>
#include <vector>

namespace lightdb::internal {
    class SkipList {
    public:
        struct Node {
            [[nodiscard]] auto operator new(std::size_t bytes) -> void *;

            auto operator delete(void *pointer, std::size_t bytes) noexcept -> void;

            std::shared_ptr<std::pmr::vector<std::byte>> data;
            Node *next{}, *down{};
        };

        constexpr SkipList() = default;

        ~SkipList();

    private:
        static constexpr std::uint8_t maxHeight{12};

        [[nodiscard]] static auto randomHeight() -> std::uint8_t;

        Node *head{[] constexpr {
            auto *const head{new Node{
                std::allocate_shared<std::pmr::vector<std::byte>>(std::pmr::polymorphic_allocator{getMemoryResource()},
                                                                  std::pmr::vector<std::byte>{getMemoryResource()})}},
                *previous{head};
            for (std::uint8_t i{}; i != maxHeight - 1; ++i) {
                auto *node{new Node{previous->data}};
                previous->down = node;
                previous = node;
            }

            return head;
        }()};
    };

    [[nodiscard]] auto operator==(const SkipList::Node &, const SkipList::Node &) -> bool;

    [[nodiscard]] auto operator<=>(const SkipList::Node &, const SkipList::Node &) -> std::strong_ordering;
}    // namespace lightdb::internal
