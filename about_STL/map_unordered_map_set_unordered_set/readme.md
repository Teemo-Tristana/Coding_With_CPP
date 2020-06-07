关于 map unordered_map  | set unordered_map 的一些总结

1. map unordered_map

        map 底层是基于红黑树，有序容器， 按照二叉搜索树存储， 中序遍历得到一个有序序列
            红黑树：

        unorder_map: 底层基于哈希表(hash table), ，无序容器，内部元素是无序的

2. set unordered_set

        set 底层是基于红黑树，有序容器， 插入和删除会自动调整，中序遍历得到一个有序序列

        unordered_set 基于哈希表，无序容器，支持迭代器遍历
