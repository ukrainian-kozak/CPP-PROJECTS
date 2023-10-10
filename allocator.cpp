#include <cstdio>
#include <iostream>
#include <vector>

namespace cxx 
{
    using size_t = std::size_t;

    template <size_t TypeSize>
        constexpr size_t sizeBlock(const size_t count) {
            constexpr bool overFlow = TypeSize > 1;
            if constexpr (overFlow) {
                constexpr size_t maxCap = static_cast<size_t>(-1) / TypeSize;
                if (count > maxCap) {
                    return -1;
                }
                return TypeSize * count;
            }
        }

    template <class Type>
        inline constexpr size_t newAlignOf = alignof(Type);

    struct defaultAllocatorTraits {
    
        static void* _Allocate(const size_t bytes) {
            return ::operator new(bytes);
        }
    
    };

    template <size_t Align, class Traits = defaultAllocatorTraits>
        void* Allocate(const size_t bytes) {
            if (bytes != 0 ) {  
                return Traits::_Allocate(bytes);
            }
            return nullptr;
        }

    template <size_t Allign>
    void Deallocate(void* ptr, const size_t count) noexcept {
        ::operator delete(ptr, count);
    }

    template <class Type>
        class allocator {
            public:
                using size_type = size_t;
                using value_type = Type;
            public:

                constexpr allocator() noexcept {}
                constexpr allocator(const allocator&) noexcept = default;

                Type* allocate(const size_t count) {
                    return static_cast<Type*>(Allocate<newAlignOf<Type>>(sizeBlock<sizeof(Type)>(count)));
                }

                void deallocate(Type* ptr, const size_t count) {
                    Deallocate<newAlignOf<Type>>(ptr, count);
                }
        
        };




}
int main() {
    std::vector<int, cxx::allocator<int>> vec(10);
    for (int i = 0; i < vec.size(); ++i) {
        vec[i] = i;
        std::cout << vec[i] << ' ';
    }
}
