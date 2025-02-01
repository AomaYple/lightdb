#include "memoryResource.hpp"

#ifdef NDEBUG
    #include "MiMallocResource.hpp"
#endif    // NDEBUG

auto lightdb ::internal::getMemoryResource() -> std::pmr::memory_resource * {
#ifndef NDEBUG
    thread_local std::pmr::unsynchronized_pool_resource resource;
#else     // NDEBUG
    static MiMallocResource miMallocResource;
    thread_local std::pmr::unsynchronized_pool_resource resource{std::addressof(miMallocResource)};
#endif    // NDEBUG

    return std::addressof(resource);
}
