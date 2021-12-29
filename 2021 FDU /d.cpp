#include <iostream>
using namespace std;
typedef long long ll;
const ll N = 501;
ll n, dist[N][N], res, nbuild[N][N];
int main() 
{
    //freopen(".in", "r", stdin);
    scanf("%lld", &n);
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=n;j++)
        {
            scanf("%lld", &dist[i][j]);
        }
    }
    for (ll k=1;k<=n;k++)
    {
        for (ll i=1;i<n;i++)
        {
            for (ll j=i+1;j<=n;j++)
            {
                if (k==i || k==j)
                    continue;
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    printf("-1\n");
                    return 0;
                }
                if (dist[i][k] + dist[k][j] == dist[i][j]) {
                    nbuild[i][j] = 1;
                }
            }
        }
    }
    for (ll i=1;i<n;i++)
    {
        for (ll j=i+1;j<=n;j++)
        {
            if (!nbuild[i][j])
                res += dist[i][j];
        }
    }
    printf("%lld\n", res);
}