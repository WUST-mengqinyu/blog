| Name                                                         | Date       | Solved |  A   |  B   |  C   |  D   |  E   |  F   |  G   |  H   |  I   |  J   |  K   |  L   |  M   | N    |
| ------------------------------------------------------------ | ---------- | ------ | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | ---- |
| [2018 China Collegiate Programming Contest Final (CCPC-Final 2018)](../Training Logs/2019训练赛/2018 China Collegiate Programming Contest Final (CCPC-Final 2018)) | 2019/11/11 | 6/12   |  O   |  O   |  .   |  .   |  .   |  .   |  O   |  .   |  Ø   |  .   |  O   |  O   |      |      |

## A. Mischievous Problem Setter

签到

## B. Balance of the Force

给一系列点黑白染色，染成黑色/白色可以使这个点得到相应的权值，对其中的一些点连边，连边的两个点颜色不能相同，要使染色后所有点权值的极差最小，求这个极差。

2-SAT判断是否存在解，其中每一个联通块的染色方案是确定的（求出一个染色方案后只能不变或全部翻转）。问题转化为有k个点，每个点需要在(min1,max1)/(min2,max2)中选择一种，如何选择使极差最小。

令min1<min2，考虑将每个点对min的较小值放入set A，在set B中放入k个min(max1,max2)，当经过某个点时计算与B中最大值的差，更新答案。如果当前扫到的点是min1，在setA中删除min1,插入min2，如果max1<max2，在setB中删除max1,插入max2。如果当前A集合首部是min2，说明再向右无法取满k个点