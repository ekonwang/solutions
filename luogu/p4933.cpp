#include <iostream>
using namespace std;
typedef long long ll;
const ll p = 2e4, N=p<<1|1, M=1e3+1, mod = 998244353;
#define debug(x) {cout<<#x<<" -> "<<x<<endl;}
ll dp[M][N], a[M], n, res;
int main()
{
    //freopen(".in", "r", stdin);
    scanf("%lld", &n);
    for (int i=1;i<=n;i++)
        scanf("%lld", &a[i]);
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<i;j++)
        {
            dp[i][a[i]-a[j]+p] += dp[j][a[i]-a[j]+p]+1;
            dp[i][a[i]-a[j]+p] %= mod;
            res += dp[j][a[i]-a[j]+p]+1;
            res %= mod;
        }
    }
    res = (res+n)%mod;
    printf("%lld\n", res);
}