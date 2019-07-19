typedef long long ll;

struct LinearBasis
{
    ll d[64], tot;

    void init()
    {
        for(int i = 0; i < 64; i ++) d[i] = 0;
        tot = 0;
    }

    bool ins(ll x)  //插入线性基
    {
        for(int i = 63; i >= 0; i --)
        {
            if((x >> i) & 1)
            {
                if(d[i]) x ^= d[i];
                else { d[i] = x; tot ++; return true; } //插入成功
            }
        }
        return false;
    }

    ll max_xor()    //在一个序列中取若干个数，使其异或和最大
    {
        ll ans = 0;
        for(int i = 63; i >= 0; i --) 
            if((ans ^ d[i]) > ans) ans ^= d[i];
        return ans;
    }

    void work()
    {
        for(int i = 1; i < 64; i ++) 
            for(int j = 1; j <= i; j ++)
                if(d[i] & (1 << (j - 1))) d[i] ^= d[j - 1];
    }

    ll k_th(ll k)   //取任意个元素进行异或的第k小个数
    {
        //考虑能异或出0的情况，tot表示线性基中的元素个数
        if(k == 1 && tot < n) return 0; 
        if(tot < n) k --;
        work();
        ll ans = 0;
        for(int i = 0; i < 64; i ++) if(d[i] != 0)
        {
            if(k % 2 == 1) ans ^= d[i];
            k >>= 1;
        }
    }
};