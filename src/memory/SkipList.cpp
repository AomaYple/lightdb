#include "SkipList.hpp"

#include <random>

auto lightdb::internal::SkipList::Node::operator new(const std::size_t bytes) -> void * {
    return getMemoryResource()->allocate(bytes);
}

auto lightdb::internal::SkipList::Node::operator delete(void *const pointer, const std::size_t bytes) noexcept -> void {
    getMemoryResource()->deallocate(pointer, bytes);
}

lightdb::internal::SkipList::~SkipList() {
    while (this->head != nullptr) {
        Node *const down{this->head->down};

        const Node *level{this->head};
        while (level != nullptr) {
            const Node *const next{level->next};
            delete level;
            level = next;
        }

        this->head = down;
    }
}

auto lightdb::internal::SkipList::randomHeight() -> std::uint8_t {
    static std::mt19937 generator{std::random_device{}()};
    static std::uniform_int_distribution distribution{0, 3};

    std::uint8_t height{};
    while (distribution(generator) == 0 && height != maxHeight) ++height;

    return height;
}

auto lightdb::internal::operator==(const SkipList::Node &lhs, const SkipList::Node &rhs) -> bool {
    return *lhs.data == *rhs.data;
}

auto lightdb::internal::operator<=>(const SkipList::Node &lhs, const SkipList::Node &rhs) -> std::strong_ordering {
    return *lhs.data <=> *rhs.data;
}
