## Overview

- 博客: [https://v-verly.github.io/](https://v-verly.github.io/)
- CF: [Verly](https://codeforces.com/profile/Verly)
- 有想详细写的题解丢在博客，wiki放个(mo)人(yu)记录
- 这边写的东西应该不会很详细，康不懂的话私聊我一哈子

## To-Do List

- 补一下字符串(undo:exKMP, manachar, SA, SAM)
- 切图论杂题，有空的时候学一些高级一点的东西
- 以上两项都不想看的时候，去摸一下组合数学或者多项式
- 有空开一个CF补题记录的page

## Logs

### Topic



### Contest

- 2019/7/27 KMP(done)
- 2019/7/17 [网络流24题](../Verly/智力康复专题/网络流24题)(done)

### Daily

#### 2019/7/29

- BZOJ-3931: 最短路+最大流，按题意模拟，求出所有满足最短路的边，拆点跑网络流即可

- BZOJ-3624: 给定一张图，图上有01两类边，要求找到一棵生成树，使0边的数量恰好为k

	先取所有1边建生成树，然后添加0边，这时候添加进的0边是必须添加的；重新建生成树，先加入必须添加的0边，然后依次加入0边直到共有k条，再加1边，这样形成的生成树就是答案

