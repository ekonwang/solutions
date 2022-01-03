#include <iostream>
#include <cassert>
using namespace std;
#define debug(x) {cout<<#x<<" -> "<<x<<endl;}
typedef long long ll;
const ll N = 5e3 + 10, inf = 1e18;
struct con
{
    ll val, index;
    bool operator<(const con&A) const
    {
        return val<=A.val;
    }
    con (ll v, ll i)
    {
        val = v;
        index = i;
    }
    con () {}
};
ll dp[N][N], n, w, s, a[N], head, tail;
con q[N];
void popback()
{
    assert(tail > head);
    tail -= 1;
}
void pophead()
{
    assert(tail > head);
    head += 1;
}
void insert(ll val, ll index)
{
    con A(val, index);
    if (A.index == q[tail-1].index)
        return;
    while(tail > head)
    {
        if (q[tail-1]<A) 
            popback();
        else 
            break;
    }
    q[tail].val = A.val;
    q[tail].index = A.index;
    tail++;
}
void init()
{
    head = tail = 0;
}
int main()
{
    //freopen(".in", "r", stdin);
    ll res = -inf;
    scanf("%lld%lld%lld", &n, &w, &s);
    for (int i=1;i<=n;i++)
        scanf("%lld", a+i);
    for (ll i=1;i<=n;i++)
        for (ll j=0;j<=w;j++)
            dp[i][j] = -inf;
    dp[1][1] = a[1];
    for (ll i=2;i<=n;i++)
    {
        init();
        ll r = -1;
        for (ll j=1;j<=w;j++)
        {
            while(r<min(j-1+s, w))
            {
                r++;
                insert(dp[i-1][r], r);
            }
            if (tail > head && q[head].index < j-1)
                pophead();
            if (tail > head)
            {
                dp[i][j] = q[head].val + j*a[i];
            }
        }
    }
    for (ll j=1;j<=w;j++)
        res = max(res, dp[n][j]);
    printf("%lld\n", res);
}   