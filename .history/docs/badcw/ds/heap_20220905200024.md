# 堆结构


## 1. 相关操作

一般定义的优先队列/堆结构 支持操作：

1. find-min 找堆顶
2. delete-min 推出堆顶
3. insert 往堆中加入一个元素
4. decrease-key 修改一个元素
5. meld 合并堆

一些魔改堆为了便于使用往往增加操作同时维护 min max 堆顶

 

## 2. Implement 对比

摘自 Wikipedia

|                          Operation                           |   find-min   |  delete-min  |    insert    | decrease-key |     meld     |
| :----------------------------------------------------------: | :----------: | :----------: | :----------: | :----------: | :----------: |
|     [Binary](https://en.wikipedia.org/wiki/Binary_heap)      |    *Θ*(1)    | *Θ*(log *n*) | *O*(log *n*) | *O*(log *n*) |   *Θ*(*n*)   |
|    [Leftist](https://en.wikipedia.org/wiki/Leftist_tree)     |    *Θ*(1)    | *Θ*(log *n*) | *Θ*(log *n*) | *O*(log *n*) | *Θ*(log *n*) |
|   [Binomial](https://en.wikipedia.org/wiki/Binomial_heap)    |    *Θ*(1)    | *Θ*(log *n*) |    *Θ*(1)    | *Θ*(log *n*) | *O*(log *n*) |
|  [Fibonacci](https://en.wikipedia.org/wiki/Fibonacci_heap)   |    *Θ*(1)    | *O*(log *n*) |    *Θ*(1)    |    *Θ*(1)    |    *Θ*(1)    |
|    [Pairing](https://en.wikipedia.org/wiki/Pairing_heap)     |    *Θ*(1)    | *O*(log *n*) |    *Θ*(1)    | *o*(log *n*) |    *Θ*(1)    |
|                            Brodal                            |    *Θ*(1)    | *O*(log *n*) |    *Θ*(1)    |    *Θ*(1)    |    *Θ*(1)    |
| [Rank-pairing](https://en.wikipedia.org/w/index.php?title=Rank-pairing_heap&action=edit&redlink=1) |    *Θ*(1)    | *O*(log *n*) |    *Θ*(1)    |    *Θ*(1)    |    *Θ*(1)    |
| [Strict Fibonacci](https://en.wikipedia.org/wiki/Fibonacci_heap) |    *Θ*(1)    | *O*(log *n*) |    *Θ*(1)    |    *Θ*(1)    |    *Θ*(1)    |
|      [2–3 heap](https://en.wikipedia.org/wiki/2–3_heap)      | *O*(log *n*) | *O*(log *n*) | *O*(log *n*) |    *Θ*(1)    |     *?*      |

二项堆的实现过程比较简单，复杂度稳定，且实现常数很小，一般使用已经足够了，c++ 各 std 的 priority_queue 都是这种实现，没有实现修改接口，土制一个也比较简单

冷知识std库的不但有priority_queue还有heap相关函数，pbds中有多种实现（支持修改、删除和堆合并、分裂），使用方式如下：


=== "std"
     ```cpp
     --8<-- "docs/badcw/ds/heap/std_sample.cc"
     ```
=== "pbds"
     ```cpp
     --8<-- "docs/badcw/ds/heap/pbds_sample.cc"
     ```

