#include "SkipList.hpp"

auto lightdb::internal::SkipList::Node::operator new(const std::size_t bytes) -> void * {
    return getMemoryResource()->allocate(bytes);
}

auto lightdb::internal::SkipList::Node::operator delete(void *const pointer, const std::size_t bytes) noexcept -> void {
    getMemoryResource()->deallocate(pointer, bytes);
}

auto lightdb::internal::operator==(const SkipList::Node &lhs, const SkipList::Node &rhs) -> bool {
    return *lhs.data == *rhs.data;
}

auto lightdb::internal::operator<=>(const SkipList::Node &lhs, const SkipList::Node &rhs) -> std::strong_ordering {
    return *lhs.data <=> *rhs.data;
}
