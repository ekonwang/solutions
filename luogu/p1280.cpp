#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;
struct con
{
    int start, len;
    bool operator<(const con&A) const
    {
        return start>A.start;
    }
};
const int N = 1e4 + 2;
int dp[N], sum[N], n, k, pos;
con a[N];
int main()
{
    //freopen(".in", "r", stdin);
    scanf("%d%d", &n, &k);
    for (int i=1;i<=k;i++)
    {
        scanf("%d%d", &a[i].start, &a[i].len);
        sum[a[i].start]++;
    }
    sort(a+1,a+k+1);
    for (int i=n;i>=1;i--)
    {
        if (!sum[i])
        {
            dp[i] = dp[i+1] + 1;
        }
        else
        {
            for (int j=1;j<=sum[i];j++)
            {
                pos++;
                dp[i] = max(dp[i], dp[i+a[pos].len]);
            }
        }
    }
    assert(pos == k);
    printf("%d\n", dp[1]);
}