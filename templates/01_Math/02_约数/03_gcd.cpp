ll gcd(ll a,ll b) {while(b^=a^=b^=a%=b);return a;}

void exgcd(ll a, ll b, ll& x, ll& y, ll& c) {
    if(!b) {y = 0; x = 1; c = a; return;}
    exgcd(b, a % b, y, x); y -= a / b * x;
}