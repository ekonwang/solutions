#include <iostream>
#include <vector>
#include <cassert>
#include <queue>
using namespace std;
#define debug(x) {cout<<#x<<" -> "<<x<<endl;}
#define sdebug(x) {cout<<#x<<" -> "<<x<<"\t";}
typedef long long ll;
typedef pair<ll, ll> P; 
const ll N = 2e5, inf = 1e17;
struct con
{
    ll to, cost;
};
ll t, n, a[501][501], res;
int main()
{
    //freopen(".in", "r", stdin);
    scanf("%lld", &t);
    while(t--)
    {
        scanf("%lld", &n);
        res = 0;
        for (int i=1;i<=2*n;i++)
            for (int j=1;j<=2*n;j++)
            {
                scanf("%lld", &a[i][j]);
                if (i>n&&j>n) 
                    res += a[i][j];
            }
        ll res1 = min(min(a[1][n+1], a[1][2*n]), min(a[n][n+1], a[n][2*n]));
        ll res2 = min(min(a[n+1][1], a[n+1][n]), min(a[2*n][1], a[2*n][n]));
        res += min(res1, res2);
        printf("%lld\n", res);
    }
}
