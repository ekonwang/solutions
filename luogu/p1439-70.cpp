#include <iostream>
#include <map>
using namespace std;
#define debug(x) {cout<<#x<<" -> "<<x<<endl;}
const int N = 1e5 + 1;
int a[N], b[N], dp[N], pos[N], n, maxdp;
map<int, int> mp;
int main()
{
    //freopen(".in", "r", stdin);
    scanf("%d", &n);
    for (int i=1;i<=n;i++)
    {
        scanf("%d", &a[i]);
        pos[a[i]] = i;
    }
    for (int i=1;i<=n;i++)
    {
        scanf("%d", &b[i]);
    }
    for (int i=1;i<=n;i++)
    {
        int maximal = 0;
        for (int j=maxdp;j>0;j--)
        {
            if (mp[j] < pos[b[i]])
            {
                maximal = j;
                break;
            }
        }
        // maintain dp array and map.
        dp[i] = maximal + 1;
        if (mp.count(dp[i]) == 0)
            mp[dp[i]] = pos[b[i]];
        else 
            mp[dp[i]] = min(pos[b[i]], mp[dp[i]]);
        maxdp = max(dp[i], maxdp);
    }
    int res = 0;
    for (int i=1;i<=n;i++)
    {       
        res = max(res, dp[i]);
    }
    printf("%d\n", res);
}