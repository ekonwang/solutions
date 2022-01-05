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
ll vnum, vis[N], d[N], t, n, a[501][501], res;
vector<con> v[N];
void sp()
{
    priority_queue<P, vector<P>, greater<P>> q;
    for (int i=0;i<=n*n*4;i++)
    {
        vis[i] = 0, d[i] = inf;
    }
    d[0] = 0;
    q.push({0, 0});
    for (int i=0;i<vnum;i++)
    {
        ll choose = -1;
        while(choose<0 || vis[choose])
        {
            if (q.empty())
                break;
            P p = q.top();
            choose = p.second;
            q.pop();
        }
        assert(choose>=0 && !vis[choose]);
        for (auto &x: v[choose]) 
        {
            ll to = x.to, c = x.cost;
            if (!vis[to] && d[to] > d[choose]+c)
            {
                d[to] = d[choose]+c;
                q.push({d[to], to});
            }
        }
        vis[choose] = 1;
    }
}
void clear()
{
    for (int i=0;i<=4*n*n;i++)
        v[i].clear();
    res = 0;
}
inline bool valid(int x, int y, int cas)
{
    if (!cas)
        return x<=n && x>=1 && y<=2*n && y>n;
    else 
        return x<=2*n && x>n && y<=n && y>0;
}
inline int tonum(int x, int y)
{
    return 2*(x-1)*n+y;
}
int main()
{
    //freopen(".in", "r", stdin);
    scanf("%lld", &t);
    while(t--)
    {
        scanf("%lld", &n);
        clear();
        for (int i=1;i<=2*n;i++)
            for (int j=1;j<=2*n;j++)
            {
                scanf("%lld", &a[i][j]);
                if (i>n&&j>n) 
                    res += a[i][j];
            }
        vnum = 2 + 2*n*n;
        int dist = tonum(2*n, 2*n);
        for (int i=1;i<=n;i++)
        {
            v[0].push_back({tonum(i, n+1), a[i][n+1]});
            v[0].push_back({tonum(i, 2*n), a[i][2*n]});
            v[0].push_back({tonum(n+1, i), a[n+1][i]});
            v[0].push_back({tonum(2*n, i), a[2*n][i]});
            v[tonum(n+i, 1)].push_back({dist, 0});
            v[tonum(n+i, n)].push_back({dist, 0});
            v[tonum(1, n+i)].push_back({dist, 0});
            v[tonum(n, n+i)].push_back({dist, 0});
        }
        for (int k=0;k<=1;k++)
        {
            for (int i=1;i<=n;i++)
            {
                for (int j=1;j<=n;j++) 
                {
                    int x = i, y = j;
                    if (!k) y+=n;
                    else x+=n;
                    int cnt = tonum(x, y);
                    int newx, newy;
                    newx = x, newy = y+1;
                    if (valid(newx, newy, k)) 
                    {
                        v[cnt].push_back({tonum(newx, newy), a[newx][newy]});
                    }
                    newx = x, newy = y-1;
                    if (valid(newx, newy, k)) 
                    {
                        v[cnt].push_back({tonum(newx, newy), a[newx][newy]});
                    }
                    newx = x-1, newy = y;
                    if (valid(newx, newy, k)) 
                    {
                        v[cnt].push_back({tonum(newx, newy), a[newx][newy]});
                    }
                    newx = x+1, newy = y;
                    if (valid(newx, newy, k)) 
                    {
                        v[cnt].push_back({tonum(newx, newy), a[newx][newy]});
                    }
                }
            }
        }
        sp();
        res = d[dist] + res;
        printf("%lld\n", res);
    }
}
