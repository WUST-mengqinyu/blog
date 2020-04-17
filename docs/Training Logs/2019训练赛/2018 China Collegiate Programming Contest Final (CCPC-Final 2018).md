| Name                                                         | Date       | Solved |  A   |  B   |  C   |  D   |  E   |  F   |  G   |  H   |  I   |  J   |  K   |  L   |
| ------------------------------------------------------------ | ---------- | ------ | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
| [2018 China Collegiate Programming Contest Final (CCPC-Final 2018)](../Training Logs/2019训练赛/2018 China Collegiate Programming Contest Final (CCPC-Final 2018)) | 2019/11/11 | 6/12   |  O   |  O   |  .   |  .   |  .   |  .   |  O   |  .   |  Ø   |  .   |  O   |  O   |

## A. Mischievous Problem Setter

签到

## B. Balance of the Force

给一系列点黑白染色，染成黑色/白色可以使这个点得到相应的权值，对其中的一些点连边，连边的两个点颜色不能相同，要使染色后所有点权值的极差最小，求这个极差。

2-SAT判断是否存在解，其中每一个联通块的染色方案是确定的（求出一个染色方案后只能不变或全部翻转）。问题转化为有k个点，每个点需要在(min1,max1)/(min2,max2)中选择一种，如何选择使极差最小。

令min1<min2，考虑将每个点对min的较小值放入set A，在set B中放入k个min(max1,max2)，当经过某个点时计算与B中最大值的差，更新答案。如果当前扫到的点是min1，在setA中删除min1,插入min2，如果max1<max2，在setB中删除max1,插入max2。如果当前A集合首部是min2，说明再向右无法取满k个点，处理即可得到最大值

## G. Pastoral Life in Stardew Valley

给一个$n×m$的矩阵，选取一个子矩阵，在子矩阵中放一个稻草人，使稻草人能被放在子矩阵中的作物包围，求方案数。

推反正也不会推……打表找规律了。

## I. Cockroaches

给m个二维点。选择一个坐标点，在其同行/同列上的所有点都会被删除。问一次最多能删除多少个点，及删除最多个点的方案数（删除的点编号全部相同视作同一种方案）。

有两种特殊情况：1.全在同一行/同一列只有一种；2.所有的行、列全不相同，有n×(n-1)/2种方案。剩下的情况则取点数最多、次多的行和列，枚举答案即可。

## K. Mr. Panda and Kakin

已知$c,p$，求$X^{2^{30}+3}≡c\ mod\ p$

有$x^y≡z\ mod \ p$，取对数有$y·lg(x)≡lg(z) \ mod \ p$

两边同乘inv(y)有$lg(x)≡inv(y)·lg(z) \ mod \ p$

推出$x≡z^{inv(y)}\ mod\ p$

即$X=c^{inv({2^{30}+3})} \ mod \ p$

所以快速幂搞一下就行

## L. Ultra Weak Goldbach's Conjecture

给你一个数，把它拆成6个素数。

n≤11无解，否则n是奇数则把它拆成2+2+2+3+偶数，n是偶数则把它拆成2+2+2+2+偶数，暴力分解偶数为两个素数即可。