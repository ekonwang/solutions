#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define MAXN 210000
using namespace std;
int T,n,m;
int fa[MAXN*2];
struct Edge{
    int l,r,v,id;
}e[MAXN];
int find(int x)
{
    return x==fa[x]?x:fa[x]=find(fa[x]);
}
void init()
{
    for(int i=1;i<=n*2;i++)fa[i]=i;
}
inline int bitcnt(int x)
{
    int ret=0;
    while(x){ret^=(x&1);x>>=1;}
    return ret;
}
void merge(int x,int y)
{
    x=find(x);y=find(y);
    if(x!=y)fa[x]=y;
}

int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        init();
        bool flag=0;
        for(int i=1;i<n;i++)
        {
            scanf("%d%d%d",&e[i].l,&e[i].r,&e[i].v);
            int l=e[i].l,r=e[i].r,v=e[i].v;
            if(v!=-1)
            {
                int bc = bitcnt(v);
                if(bc)
                {
                    merge(l,r+n);
                    merge(l+n,r);
                }
                else
                {
                    merge(l,r);
                    merge(l+n,r+n);
                }
            }
        }
        for(int i=1;i<=m;i++)
        {
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            if(z)
            {
                merge(x,y+n);
                merge(x+n,y);
            }
            else
            {
                merge(x,y);
                merge(x+n,y+n);
            }
        }
        for(int i=1;i<=n;i++)
            if(find(i)==find(i+n))
            {
                flag=1;
                break;
            }
        if(flag)
        {
            puts("NO");
            continue;
        }
        puts("YES");
        for(int i=1;i<n;i++)
        {  
            if(e[i].v==-1)
            {
                int x=e[i].l,y=e[i].r;
                if(find(x)==find(y))
                    e[i].v = 0;
                else if(find(x)==find(y+n))
                    e[i].v = 1;
                else
                {
                    e[i].v=0;
                    merge(x,y);
                    merge(x+n,y+n);
                }
            }
            printf("%d %d %d\n",e[i].l,e[i].r,e[i].v);
        }
    }
    return 0;
}