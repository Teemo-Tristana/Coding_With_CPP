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
                键唯一的有序键集合[值也唯一]                        按键排序     底层由红黑树实现   类模板  
                std::set 是关联容器，含有 Key 类型对象的已排序集。用比较函数 比较 (Compare) 进行排序。搜索、移除和插入拥有对数复杂度。 
                set 通常以[红黑树实现]。
                若二个对象 a 与 b 相互间既不比较大于亦不比较小于： !comp(a, b) && !comp(b, a) ，则认为它们等价。 

            map             
                键唯一的有序键值对集合                        按键排序     底层由红黑树实现   类模板
            multiset        
               按键排序的键集合,[可以重复]        按键排序                      类模板
            multimap       
                按键排序的键值对集合,值可以多个[值不唯一]     按键排序                       类模板

            无序关联容器：
                快速查找[O1,最坏O（n)]
                底层都是无序数据结构，由hash表实现

            unordered_set[c++11起]            
                唯一键的集合                  按键生成散列      类模板   
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

4. 仿函数(函数对象)源码剖析
    - 关系运算类[relational]仿函数[函数对象]
        - STL内建的“关系运算类仿函数”，支持等于、不等于、大于、大于等于、小于、小于等于六种运算
        - 每一个都是二元运算
            - 等于[equality]:                               equal_to<T>
            - 不等于[inequality]:                           not_equal_to<T>
            - 大于[greater-than]:                           greater<T>
            - 大于或等于[greater-than-or-equal]:            greater_equal<T>
            - 小于[ess-than]：                              less<T>
            - 小于或等于[less-than-or-equal]：               less_equal<T>
