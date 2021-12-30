#include <iostream>
#include <vector>
using namespace std;
#define debug(x) {cout<<#x<<" -> "<<x<<endl;}
const int N = 1e5 + 1;
struct con
{
    int last, val;
    bool operator<(const con&A) const
    {
        return last<A.last;
    }
    con (int l, int v) 
    {
        last = l, val = v;
    }
};
int a[N], b[N], dp[N], pos[N], n, maxdp;
vector<int> vec;
int main()
{
    freopen(".in", "r", stdin);
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
        vector<int>::iterator it;
        it = lower_bound(vec.begin(), vec.end(), pos[b[i]]);
        if (it == vec.end())
        {
            vec.push_back(pos[b[i]]);
        }
        else
        {
            *it = min(pos[b[i]], *it);
        }
    }
    printf("%d\n", vec.size());
}