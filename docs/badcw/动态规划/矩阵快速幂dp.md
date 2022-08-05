# 矩阵快速幂

- 能解决的问题：能用滚动优化的前后项关联的动态规划问题，而且一般递推项数过大使用普通枚举不能解决。

- 复杂度：\(构造矩阵的长度^3*log(递推项数)\)

- 基本思想和前置技能：矩阵乘法

## 1、矩阵快速幂的基本过程

- 构造初始矩阵
- 构造递推矩阵
- 递推矩阵使用快速幂算法递推出结果矩阵
- 初始矩阵与结果矩阵相乘得到最终结果

- 几大特点
    - 初始矩阵只有一行（当然也可以是一列，但是由于数组的方便性和习惯问题常采用一行），列数由递推式决定
    - 递推矩阵是方阵，行列数与初始矩阵列数相同
    - 快速幂真的是快速幂，就是按照倍增的思想将递推矩阵变成n次方，由于递推矩阵是方阵所以是存在次方的。
    - 由于快速幂一开始需要一个幺元作为初始结果，常常直接把初始矩阵替换上去，带入计算，最终快速幂的结果就是解。
    
## 2、例题

### 求大fib数

- 众所周知`fib[i]=fib[i-1]+fib[i-2]`，所以直接构造上一个二维的矩阵，像这种简单的加减递推的话维数就可以等于递推式中的项数

- 初始矩阵`fib[0] = 1, fib[1] = 1`，递推矩阵
$$
\begin{bmatrix}
0&1\\ 
1&1\\
\end{bmatrix}
$$
- 都知道左行乘右列，所以右边的第一列和左边的第一行就构成了下一个递推的数，从`fib[0] fib[1]`变成`fib[1] fib[2]`，这样以来就可以写出递推矩阵了。

### 求\(f[n] = f[n-1] + n^3\)

- 具体是不是我也不记得了，但是大概就是这样的一个东西，像这种带非常数次方的东西讲个道理确实比较难构造递推矩阵
- 由于\((n+1)^3=n^3+3*n^2+3*n+1\)，不会可以学二项式定理
- 构造
$$
\begin{cases} 
 p[n]=1
 \\
 g1[n]=g1[n-1]*3+p[n-1]
 \\
 g2[n]=g2[n-1]*3+g1[n-1]
 \\
 g3[n]=g3[n-1]+g2[n]
 \\
 f[n]=f[n-1]+g3[n-1]
\end{cases}
$$
即可。

### 求高维矩阵的矩阵快速幂

- 具体来讲是初始矩阵不止一维
- 有没有解我不知道，但是这是个显然不是几个小时能写出来的算法能解决的问题，而且复杂度成指数级暴涨
- 具体来讲就是把二维变成一维，从左到右，从上到下依次编号之后将矩阵化成一维再求解。(codeforces 1152F2)

## 3、模板

- 一套自用的模板，不算简便但是毕竟亲手写的很熟悉。

```cpp
const int maxn = 10;
const int mod = 1e9+7;

int sz;

struct matrix {
    ll gg[maxn][maxn];
    matrix() {memset(gg, 0, sizeof(gg));}
    void show() {
        printf("*\n");
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                printf("%lld ", gg[i][j]);
            }
            printf("\n");
        }
    }
    int tr() {
        int res = 0;
        // for (int i = 0; i < n; ++i) {
        //     res += gg[i][i];
        // }
        return res;
    }
}t1, res;

int n, m, k;

//a * b， x为a的列数， y为b的行数，k为a的行和b的列数
matrix multiply(matrix a, matrix b, int x, int y, int kk) {
    matrix temp;//构造函数清零
    memset(temp.gg, 0, sizeof(temp.gg));
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < kk; ++k) {
                temp.gg[i][j] = (temp.gg[i][j] + a.gg[i][k] * b.gg[k][j]) % mod;
            }
        }
    }
    return temp;
}

void quickSolve(ll k) {
    while (k > 0) {
        if (k & 1) {
            res = multiply(res, t1, 1, sz, sz);
        }
        t1 = multiply(t1, t1, sz, sz, sz);
        k >>= 1;
    }
}

```