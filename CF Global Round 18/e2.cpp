#include <iostream>
#include <algorithm>
using namespace std;
#define debug(x) {cout << #x << " -> " << x << endl;}
typedef long long ll;
struct node
{
    int dep, index;
    bool operator<(const node&A) const 
    {
        return dep>A.dep;
    }
};
const int N = 1e6;
int n, k, ne[N], dst[N], h[N], h1[N], dep[N], vis[N], fat[N], cnt, leafcnt;
node nodes[N], lens[N];
bool leaf[N];
void init() 
{
    for (int i=0;i<3*n;i++) 
    {
        ne[i] = h[i] = h1[i] = -1;
    }
}
void add(int from, int to) 
{
    ne[cnt] = h[from], dst[cnt] = to, h[from] = cnt++;
}
void add1(int from, int to)
{
    ne[cnt] = h1[from], dst[cnt] = to, h1[from] = cnt++;
}
void dfs(int u, int fa)
{
    int child = 0;
    dep[u] = dep[fa] + 1;
    fat[u] = fa;
    for (int i=h[u];~i;i=ne[i])
    {
        int v = dst[i];
        if (v == fa) continue;
        dfs(v, u);
        child ++;
    }
    if (!child) {leaf[u] = true; leafcnt ++;}
}
int dfs1(int u) 
{
    if (vis[u] || !u)
        return 0;
    int res = dfs1(fat[u]) + 1;
    vis[u] = 1;
    return res;
}
int main() {
    //freopen(".in", "r", stdin);
    scanf("%d%d", &n, &k);
    init();
    for (int i=1;i<n;i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
    }
    dep[0] = 0;
    dfs(1, 0);
    for (int i=1;i<=n;i++)
    {
        nodes[i].dep = dep[i];
        nodes[i].index = i;
    }
    sort(nodes+1, nodes+n+1);
    for (int i=1;i<=n;i++)
    {
        int index = nodes[i].index;
        lens[i].index = index;
        lens[i].dep = dfs1(index);
    }
    sort(lens+1, lens+n+1);
    ll r = 0, b = 0;
    ll res = 0;
    for (int i=1;i<=leafcnt;i++) 
    {
        if (i>k)
            b += lens[i].dep;
        else
            r++;
    }
    res = (r-b)*(n-r-b);
    for (ll i=leafcnt+1;i<=k;i++)
    {
        res = max(res, (i)*(n-i));
    }
    for (ll i=r;i<=b;i++)
    {
        res = min(res, (n-r-i)*(r-i));
    }
    printf("%lld\n", res);
}