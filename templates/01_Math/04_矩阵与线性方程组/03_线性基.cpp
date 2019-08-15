typedef long long ll;

struct LinearBasis
{
    ll d[64], tot;

    void ins(ll x)  //插入线性基
    {
        for(int i = 63; i >= 0; i --)
        {
            if((x >> i) & 1)
            {
                if(!d[i]) return void(d[i] = x);
                x ^= d[i];
            }
        }
    }

    ll max_xor()    //在一个序列中取若干个数，使其异或和最大
    {
        ll ans = 0;
        for(int i = 63; i >= 0; i --) 
            if((ans ^ d[i]) > ans) ans ^= d[i];
        return ans;
    }

    void init()
    {
        for(int i = 0; i < 64; i ++) if(d[i])
            for(int j = 0; j < i; j ++)
                if(d[i] & (1ll << j)) d[i] ^= d[j];
        for(int i = 0; i < 64; i ++) if(d[i]) d[tot ++] = d[i];
    }

    ll k_th(ll k)   //取任意个元素进行异或的第k小个数
    {
        //考虑能异或出0的情况，tot表示线性基中的元素个数
        k -= (n != tot);
        if(k > (1ll << tot)) return -1;
        ll ans = 0;
        for(int i = 0; i < tot; i ++) if(k & (1ll << i)) ans ^= d[i];
        return ans;
    }
};