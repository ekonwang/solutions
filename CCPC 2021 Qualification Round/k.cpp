#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;
#define debug(x) {std::cout << #x << "->" << x << std::endl;}
typedef long long ll;
const int N = 2e5 + 10;
struct edge
{
    int to, next;
    edge(int t, int n) {to=t,next=n;}
    edge() {to=0, next=0;}
};
struct node{
    int i, val;
    bool operator<(const node&A) const{
        return val<A.val;
    }
};
int n, t, en, en1, nxt[N], nxt1[N], vis[N], fa[N], res[N];
edge e[N], e1[N];
node nodes[N];
int find(int v) 
{
    return (v == fa[v]) ? v : (fa[v]=find(fa[v]));
}
void add(int from, int to) 
{
    int edge_index = nxt[from];
    ++en;
    e[en].next = edge_index;
    e[en].to = to;
    nxt[from] = en;
}
void add1(int from, int to) 
{
    int edge_index = nxt1[from];
    ++en1;
    e1[en1].next = edge_index;
    e1[en1].to = to;
    nxt1[from] = en1;
}
void dfs(int u, int father) 
{
    int cnte = nxt1[u];
    while(cnte)
    {
        int to = e1[cnte].to, nexte = e1[cnte].next;
        res[to] = res[u] + 1;
        dfs(to, u);
        cnte = nexte;
    }
}
void init() 
{
    for (int i=1;i<=n;i++) 
    {
        nxt[i] = 0;
        nxt1[i] = 0;
        vis[i] = 0;
        fa[i] = i;
    }
    en = 0;
    en1 = 0;
}
int main() 
{
    //freopen(".in", "r", stdin);
    scanf("%d", &t);
    while(t--) 
    {
        scanf("%d", &n);
        init();
        for (int i=1;i<n;i++) 
        {
            int x, y;
            scanf("%d%d", &x, &y);
            add(x, y);
            add(y, x);
        }
        for (int i=1;i<=n;i++) 
        {
            int val;
            scanf("%d", &val);
            nodes[i].i = i;
            nodes[i].val = val;
        }
        assert(en == 2*n-2);
        sort(nodes+1, nodes+n+1);
        for (int i=1;i<=n;i++)  // 建树
        {
            int u = nodes[i].i;
            int cnte = nxt[u];
            while(cnte)
            {
                int to = e[cnte].to, nexte = e[cnte].next;
                if (vis[to]) 
                {
                    int f = find(to);
                    if (f != u)
                    {
                        fa[f] = u;
                        add1(u, f);
                    }
                }
                cnte = nexte;
            }
            vis[u] = 1;
        }  
        int u = nodes[n].i;
        res[u] = 1;
        dfs(u, 0); 
        for (int i=1;i<=n;i++) 
        {
            printf("%d\n", res[i]);
        }
    }
    return 0;
}

