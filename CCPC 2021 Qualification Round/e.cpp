#include <iostream>
#include <map>
#define debug(x) {std::cout<<#x<<"->"<<x<<std::endl;}
using namespace std;
typedef long long ll;
const ll N = 2e5;
struct con
{
    ll round, index;
    bool operator<(const con&A) const
    {
        if (round==A.round) return index<A.index;
        return round<A.round;
    }
};
map<ll, map<ll, ll>> mp;
map<ll, ll> zmp;
ll a[N], s[N], q[N], t, n, m;
void init()
{
    mp.clear();
}
ll remain(ll v)
{
    return ((v - v/s[n]*s[n]) + s[n]) % s[n];
}
void tackle()
{
    for (int i=n;i>=1;i--)
    {
        ll rem = remain(s[i]);
        if (mp.count(rem)) 
        {
            mp[rem][s[i]] = i;
        }
        else
        {
            map<ll, ll> bmap;
            bmap[s[i]] = i;
            mp[rem] = bmap;
        }
    }
    for (int i=1;i<=m;i++)
    {
        if (!q[i]) 
        {
            printf("0\n");
            continue;
        }
        int qv = remain(q[i]);
        if (mp.count(qv))
        {
            ll res;
            map<ll, ll> &bmap = mp[qv];
            map<ll, ll>::iterator it = bmap.lower_bound(q[i]);
            if (it == bmap.end() || (it != bmap.begin() && it->first > q[i])) 
            {
                it--;
                res = (q[i]-it->first)/s[n] *n + it->second;
            }
            else if (it->first == q[i]) 
            {
                res = it->second;
            }
            else
            {
                res = -1;
            }
            printf("%lld\n", res);
        }
        else
            printf("-1\n");
    }
}
void tackle0()
{
    for (int i=n;i>=1;i--)
    {
        zmp[s[i]] = i;
    }
    for (int i=1;i<=m;i++)
    {
        if (!q[i])
        {
            printf("0\n");
            continue;
        }
        if (zmp.count(q[i]))
        {
            ll res = zmp[q[i]];
            printf("%lld\n", res);
        }
        else
        {
            printf("-1\n");
        }
    }
}
int main() 
{
    //freopen(".in", "r", stdin);
    scanf("%lld", &t);
    while(t--)
    {
        init();
        scanf("%lld%lld", &n, &m);
        for (int i=1;i<=n;i++)
        {
            scanf("%lld", &a[i]);
            s[i] = a[i] + s[i-1]; // prefix sum
        }
        for (int i=1;i<=m;i++)
            scanf("%lld", &q[i]);
        if (s[n]) {
            if (s[n] < 0) 
            {
                for (int i=1;i<=n;i++)
                    s[i] = -s[i];
                for (int i=1;i<=m;i++)
                    q[i] = -q[i];
            }
            tackle();
        }
        else
            tackle0();
    }
    return 0;
}

