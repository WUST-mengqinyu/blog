#include <bits/stdc++.h>
#define ll long long
using namespace std;

template <class T>
inline bool scan(T &ret){
    char c;
    int sgn;
    if (c = getchar(), c == EOF) return 0; //EOF
    while (c != '-' && (c < '0' || c > '9')) c = getchar();
    sgn = (c == '-') ? -1 : 1;
    ret = (c == '-') ? 0 : (c - '0');
    while (c = getchar(), c >= '0' && c <= '9') ret = ret * 10 + (c - '0');
    ret *= sgn;
    return 1;
}

const ll mod = 998244353;
const int maxn = 1e5+5;

ll qp(ll x, ll n) {
    ll res = 1; x %= mod;
    while (n > 0) {
        if (n & 1) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

int main() {
    return 0;
}

freopen("data.in","r",stdin);
freopen("data.out","w",stdout);
clock_t ST = clock();
cerr << "time: " << ((clock()-ST)*1000.0 / CLOCKS_PER_SEC) << "ms" << endl;

__builtin_popcount(unsigned int n) //判断n的二进制有多少个1
__builtin_parity(unsigned int n) //判断n的二进制中1的个数的奇偶性
__builtin_ffs(unsigned int n) //判断n的二进制末尾最后一个1的位置，从一开始
__builtin_ctz(unsigned int n) //判断n的二进制末尾后面0的个数，当n为0时，和n的类型有关
__builtin_clz(unsigned int n) //返回前导0的个数