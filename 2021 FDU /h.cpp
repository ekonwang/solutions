#include <iostream>
using namespace std;
typedef long long ll;
#define debug(x) {cout<<#x<<" -> "<< x <<endl;}
const ll mod = 998244353, N=11;
ll n, s, t, m, res, w[N], c[N], mres[N], dp[10001][1002];
ll gap, g;
double dp2[10001][1001];
inline ll fast_power(ll base, ll exp)
{
    ll res = 1;
    while(exp)
    {
        if (exp & 0x1)
            res = res * base % mod;
        base = base * base % mod;
        exp = exp >> 1;
    }
    return res;
}
inline ll gcd(ll a, ll b) 
{
    if (b>a) swap(a, b);
    while(b)
    {
        ll r = a % b;
        a = b;
        b = r;
    }
    return abs(a);
}
inline ll mod_divide(ll enume, ll denom)
{
    return enume * fast_power(denom, mod-2) % mod;
}
inline void add(ll &v, ll append)
{
    v = (v + append) % mod;
}
int main() 
{
    /* m: options, n:max games count */
    //freopen(".in", "r", stdin);
    scanf("%lld%lld%lld%lld", &s, &t, &n, &m);
    for (int i=1;i<=m;i++)
    {   
        scanf("%lld%lld", &w[i], &c[i]);
        mres[i] = mod_divide(w[i], 10000);
        g = gcd(c[i], g);
    }
    for (int i=1;i<=m;i++)
    {
        c[i] /= g;
    }
    gap = (t-s+g-1)/g;
    s = (s+g-1)/g; t = s + gap;
    dp[0][s] = 1;
    dp2[0][s] = 1;
    for (int i=0;i<n;i++)
    {
        for (int j=1;j<t;j++)
        {
            for (int k=1;k<=m;k++)
            {
                if (j+c[k]>=t) 
                    add(dp[i+1][t], dp[i][j]*mres[k]);
                else if (j+c[k]<=0) 
                    add(dp[i+1][0], dp[i][j]*mres[k]);
                else 
                    add(dp[i+1][j+c[k]], dp[i][j]*mres[k]);
            }
        }
    }
    for (int i=1;i<=n;i++)
    {
        res += dp[i][t];
        res %= mod;
    }
    printf("%lld\n", res);
    return 0;
}