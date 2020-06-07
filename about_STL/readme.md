STL : Standard Template Libaray 

1. 容器库：

    1.顺序容器： 
            array[c++11起]      静态连续数组    类模板
            vector              动态连续数组    类模板
            deque               双端队列        类模板
            forward_list[c++起] 单链表          类模板
            list                双向链表        类模板
            
          
    2.关联容器：快速查找(OlongN)
            set             
                键唯一的有序集合[值也唯一]                        按键排序     底层由红黑树实现   类模板   
            map             
                键唯一的有序集合                        按键排序     底层由红黑树实现   类模板
            multiset        
                键的有序集合,值可以多个[值不唯一,可存储重复的值]        按键排序                      类模板
            multimap       
                键值对的有序集合,值可以多个[值不唯一]     按键排序                       类模板

            无序关联容器：
                快速查找[O1,最坏O（n)]
                底层都是无序数据结构，由hash表实现

            unordered_set[c++11起]            
                键唯一的集合                  按键生成散列      类模板   
            unordered_map[c++11起]            
                键唯一的键值对集合             按键生成散列      类模板   
            unordered_multiset[c++11起]       
                键的集合值,不唯一              按键生成散列      类模板   
            unordered_multimap[c++11起]       
                键值对的集合,键不唯一          按键生成散列      类模板 
        
    3.容器适配器：顺序容器和关联容器的变种
            stack               栈          LIFO                类模板
            queue               队列        FIFO                类模板
            priority_queue      优先队列    以指定顺序存储元素    类模板
            span[C++20]         相接的对象序列上的非占有视图，某个其他对象占有序列的存储。对象的连续序列上的无所有权视图    (类模板)

2. 迭代器:
3. 算法
4. 
