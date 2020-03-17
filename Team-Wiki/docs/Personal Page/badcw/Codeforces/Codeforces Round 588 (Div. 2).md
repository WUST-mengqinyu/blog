[https://codeforces.com/contest/1230](https://codeforces.com/contest/1230)

赛中`A,B,C,D`，赛后`E，F`

## A. Dawid and Bags of Candies

题意：给4个数，求能不能分成两个集合使两个集合内的数和相等

题解：只有4个数随便写都对，我写了状态压缩枚举子集。

## B. Ania and Minimizing

题意：给一个数字串s，求改变其中最多k位，使其变成不含前导零的最小数字

题解：直接分一下类，其中首位如果要改变就只能是1位数。

## C. Anadi and Domino

题意：最多7个点21条边，求其中边包含所给的21条边中最多多少种。

题解：题意杀，直接爆搜枚举7个点的颜色即可。

## D. Marcin and Training Camp

题意：每个人有两个属性a和b，a是它技能点的二进制表示，b是它的权值，定义如果x的a有y的a中不存在的二进制位，则x>y。现在求一个集合使得集合中没有任何一个人大于其他所有人，求满足条件的集合的b权值最大值。

题解：易得多个人a相等时才能满足题意，然后满足题意的集合是可以合并的，所以求出所有满足题意的集合并合并，然后求出他们满足题意的a值的子集和即是答案。

## E. Kamil and Making a Stream

题意：求一棵树上gcd(link(u, v))的和，u是v的祖先。

题解：从上往下递归，每个数的因子数是LOG级别所以建立一个vector或者map存下来算就可以了，复杂度`O(nlogn)`或`O(nlognlogn)`。

## F. Konrad and Company Evaluation

题意：给一张有向图，每次操作将一个点相连的边都朝外连（改变方向），每次求\(\sum in[i] * out[i]\)

题解：暴力维护每个点的入边，每次操作一个点将其入边清空并反向连接即可。复杂度可过，具体算不清，题解说是`O(q*sqrt(m))`。
