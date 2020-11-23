#ifndef MYTINYSTL_ALLOC_H_
#define MYTINYSTL_ALLOC_H_
/**
 * 空间配置器分配两级，
 *      第一级是 allocate.h, 一般是对 malloc 的一层封装，没有考虑内存碎片化的问题，在大量申请小空间的内存块内存碎片严重时，导致空闲内存无法充分利用。
 *      第二级是 alloc.h ，采用一个内置轻量级的内存池，对于小内存块的申请，则从内存池中分配，并维护一些空闲链表对内存块加以管理。
 * 
 * alloc.h 用于内存分配和释放，主要以内存池的方式实现
 * 
 * 参考连接：
 *  1. http://ibillxia.github.io/blog/2014/06/13/stl-source-insight-1-memory-allocator/
 *  2. https://zhuanlan.zhihu.com/p/51918715
*/

#include <new>
#include <cstddef>
#include <cstdio>

namespace mystl
{
    // 空闲链表的每个node的定义
    union FreeList
    {
        union FreeList *next; // 指向下一个内存块
        char data[1];         // 存储本块内存的首地址
    };

    // 不同大小的内存块对于的分配大小
    enum
    {
        EAlign128 = 8,
        EAlign256 = 16,
        EAlign512 = 32,
        EAlign1024 = 64,
        EAlign2048 = 128,
        EAlign4096 = 256,
    };

    // 内存块大小 4KB
    enum
    {
        ESmallObjectBytes = 4096
    };

    // 默认 free list 数量
    enum
    {
        EFreeListNumber = 56
    };

    /**
     * 空间配置器类 alloc
     * 采用第二级配置器，内置一个轻量级的内存池。
     *      维持一个链表数组，每个链表的节点都是由不同大小的内存块 mem_block 组成，大小分别是8/16/32/64/256/512 bytes, 每次分配内存时，根据需求选择合适的内存块(向上取整)来分配, 若块不够用时，则调用refill重新分配内存。
     * 策略：
     *  根据需要的内存大小不同采取不同的内存分配策略：
     *      大于默认内存块(4096 bytes),采用第一级空间分配器(malloc/free)
     *      否则，采用第二级内存空间分配器
    */
    class alloc
    {
    private:
        // 内存池起始位置
        static char *start_free;

        // 内存池结束位置
        static char *end_free;

        // 申请 heap 的大小
        static size_t heap_size;

        // 使用链表的方式管理内存碎片，分配和回收小内存(<= 4KB)块

        static FreeList *free_list[EFreeListNumber];

    public:
        // 对外接口
        // 分配 n 字节大小的内存块
        static void *allocate(size_t n);

        // 回收 p 指向 n bytes的空间
        static void *deallocate(void *p, size_t n);

        // 重新分配空间
        static void *reallocate(void *p, size_t old_size, size_t new_size);

    private:
        // 根据需要的空间大小，选用大小不同的内存块
        static size_t M_align(size_t bytes);

        // 向上取整分配内存块
        static size_t M_round_up(size_t bytes);

        // 计算 bytes 需要的内存块的 index
        static size_t M_freelist_index(size_t bytes);

        // 申请大小为n的内存块，并加入到对应的free list
        static void *M_refill(size_t n);

        // 尝试从内存池中取空间给 free list 使用，条件不允许时，会调整 nblock或重新分配内存
        static char *M_chunk_alloc(size_t size, size_t &nobj);
    };

    char *alloc::start_free = nullptr;
    char *alloc::end_free = nullptr;
    size_t alloc::heap_size = 0;

    FreeList *alloc::free_list[EFreeListsNumber] = {
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};

    /**
     * 分配 n 字节大小的内存块
     * 先判断需要申请的内存的大小
     *      若大于默认值，则使用第一级空间分配器(malloc)
     *      否则，从空闲链表中选择一个块大小合适的内存块，并尝试分配 block
     *          如果是空的(nullpr),则进行 refill(申请分配一个内存装入链表)
     *          否则，直接返回
     */
    inline void *alloc::allocate(size_t n)
    {
        // FreeList *my_free_list = nullptr;
        FreeList *result = nullptr;

        // 如果大于 ESmallocObjectByte,则采用第一级配置器(malloc)
        if (n > static_cast<size_t>(ESmallObjectBytes))
            return std::malloc(n);

        // my_free_list = free_list[M_freelist_index(n)];
        // result = my_free_list;

        result = free_list[M_freelist_index(n)];

        // 如果 result 为空，则进行 refill， 否则就调整freelist的表头，并返回
        if (nullptr == result)
        {
            void *r = M_refill(M_round_up(n));
            return r;
        }
        // my_free_list = result->next;

        return result;
    }

    // 回收 p 指向 n bytes的空间
    inline void *alloc::deallocate(void *p, size_t n)
    {
        if (n > static_cast<size_t>(ESmallObjectBytes))
        {
            std::free(p);
            return;
        }
        FreeList *q = reinterpret_cast<FreeList *>(p);
        FreeList *my_free_list;
        my_free_list = free_list[M_freelist_index(n)];
        q->next = my_free_list;
        my_free_list = q;
    }

    inline void *alloc::reallocate(void *p, size_t old_size, size_t new_size)
    {
        deallocate(p, old_size);
        p = allocate(new_size);
        return p;
    }

    inline size_t alloc::M_align(size_t bytes)
    {
        if (bytes <= 512)
        {
            return bytes <= 256 ? (bytes <= 128 ? EAlign128 : EAlign256)
                                : EAlign512;
        }

        return bytes <= 2048 ? (bytes <= 1024 ? EAlign1024 : EAlign2048)
                             : EAlign4096;
    }

    // 获取 bytes 最合适的块大小（采用向上取整的方式）
    inline size_t alloc::M_round_up(size_t bytes)
    {
        return ((bytes + M_align(bytes) - 1) & ~(M_align(bytes) - 1));
    }

    inline size_t alloc::M_freelist_index(size_t bytes)
    {
        if (bytes <= 512)
        {
            return bytes <= 256 ? (bytes <= 128 ? ((bytes + EAlign128 - 1) / EAlign128 - 1)
                                                : (15 + bytes + EAlign256 - 129) / EAlign256)
                                : (23 + (bytes + EAlign512 - 257) / EAlign512);
        }
        return bytes <= 2048 ? (bytes <= 1024 ? (31 + (bytes + EAlign1024 - 513) / EAlign1024)
                                              : (39 + bytes + EAlign2048 - 1025) / EAlign2048)
                             : (47 + (bytes + EAlign4096 - 2049) / EAlign4096);
    }

    /**
     * M_refill() 重新分配内存(进货函数)
     * refill的逻辑是，先尝试去调用chunk_alloc去内存池中分配20个块大小的内存，并且以传 引用 的方式来返回真正分配了的内存块数量。
     * 如果返回的只有1个块，还是返回之。其他情况就把分配得来的空间，给切成小块，然后加入到对应的链表中
    */
    inline void *alloc::M_refill(size_t n)
    {
        size_t nblock = 20; // 默认申请内存块数

        // 尝试去申请内存(这里 nblock是以引用的方式传递，值是可能会改变的)
        char *chunk = M_chunk_alloc(n, nblock);

        FreeList *my_free_list;
        FreeList *result;
        FreeList *cur;
        FreeList *next;

        // 如果只分配了1块内存块，直接返回，否则将第一块返回给用户，剩下的则分成小块，并加入空闲链表中
        if (1 == nblock)
            return chunk;

        // 将大块划分为小块并加入空闲链表
        my_free_list = free_list[M_freelist_index(n)];
        result = (FreeList *)chunk;
        my_free_list = next = (FreeList *)(chunk + n);

        for (size_t i = 1;; ++i)
        {
            cur = next;
            next = (FreeList *)((char *)next + n);

            // 最后一块
            if (nblock - 1 == i)
            {
                cur->next = nullptr;
                break;
            }
            else
            {
                cur->next = next;
            }
        }
        return result;
    }

    /***
     * M_chunk_alloc() 内存分配的实际执行函数
     *  查看内存池剩下的空间是否满足默认块(20)指定大小的需求，若满足，则直接返回
     *  若不满足，但是至少可以分配一块指定大小的需求，则修改 nblock，直接返回
     *  否则，重新计算需求大小，并尝试调用 malloc 分配，
     *      成功则返回
     *      失败，则从当前的freelist查找是否有更大的空闲块，
     *              若有则返回
     *              若没有，则调用第一级空间配置器的allocate，看 oom 机制是否能够解决(在此存没有实现)

    */
    inline char *alloc::M_chunk_alloc(size_t size, size_t &nblock)
    {
        char *result;
        size_t need_bytes = size * nblock;
        size_t left_bytes = end_free - start_free;

        // 如果内存池的剩余空间可以满足要求(分配默认块数(20块)需要的大小)，则直接返回，并修改空闲链表的起始地址
        if (left_bytes >= need_bytes)
        {
            result = start_free;
            start_free += need_bytes;
            return result;
        }
        // 不满足分配默块数(20块)的需求，但是至少可以满足分配一块，则分配尽可能多的分配内存块，并改变 nblock 和 链表起始位置(start_free)的值
        else if (left_bytes >= size)
        {
            nblock = left_bytes / size;
            need_bytes = size * nblock;
            result = start_free;
            start_free += need_bytes;
            return result;
        }
        // 若都不满足，则重新为内存池分配内存
        else
        {
            // 需要分配的大小： 两倍的需求量 + 随分配次数增加的附加量
            size_t bytes_to_get = (need_bytes * 2) + M_round_up(heap_size >> 4);

            // 如果内存池还剩下空闲的内存，则将其加入对应的free_list中，尽量节省内存
            if (left_bytes > 0)
            {
                FreeList *my_free_list = free_list[M_freelist_index(left_bytes)];
                ((FreeList *)start_free)->next = my_free_list;
                my_free_list = (FreeList *)start_free;
            }

            // 调用 malloc 重新分配内存
            start_free = (char *)std::malloc(bytes_to_get);

            // 内存分配失败：
            if (nullptr == start_free)
            {
                FreeList *my_free_list, *p;
                // 尝试从freelist空闲的区块中分配比当前申请大的空间(需求的size倍数递增)
                for (size_t i = size; i <= ESmallObjectBytes; i += M_align(i))
                {
                    my_free_list = free_list[M_freelist_index(i)];
                    p = my_free_list;
                    if (p)
                    {
                        my_free_list = p->next;
                        start_free = (char *)p;
                        end_free = start_free + i;
                        return M_chunk_alloc(size, nblock);
                    }
                }

                // 如果还是没有分配成功，(源码)此处还有一部：调用第一级配置器的allocte，看 oom 机制是否能够解决
                std::printf("out of memory\n");
                end_free = nullptr;
                throw std::bad_alloc();
            }

            end_free = start_free + bytes_to_get;
            heap_size += bytes_to_get;
            return M_chunk_alloc(size, nblock);
        }
    }

} // namespace mystl

#endif