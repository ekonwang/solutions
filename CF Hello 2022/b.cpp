#include <iostream>
#include <algorithm>
using namespace std;
struct con
{
    int l, r, c;
    bool operator<(const con&A)
    {
        if (l!=A.l) return l<A.l;
        else return c<A.c;
    }
    bool operator>(const con&A)
    {
        if (r!=A.r) return r>A.r;
        else return c<A.c;
    }
};
const int N = 2e5;
con a[N];
int n, t, ma, mi, all;
int main()
{
    //freopen(".in", "r", stdin);
    scanf("%d", &t);
    while(t--)
    {   
        scanf("%d", &n);
        for (int i=1;i<=n;i++)
        {
            scanf("%d%d%d", &a[i].l, &a[i].r, &a[i].c);
            if (i==1)
                ma = 1, mi = 1, all = 1;
            else {
                if (a[i]<a[mi]) 
                    mi = i;
                if (a[i]>a[ma])
                    ma = i;
                if (a[all].l > a[mi].l || a[all].r < a[ma].r)
                    all = -1;
                if (a[i].l > a[mi].l || a[i].r < a[ma].r);
                else 
                {
                    if (all<0) all = i;
                    else if (a[i].c<a[all].c) all = i;
                }
            }
            if (a[mi].l != a[ma].l && a[ma].r != a[mi].r)
            {
                if (all>0)
                {
                    if (a[ma].c + a[mi].c < a[all].c)
                        printf("%d\n", a[mi].c+a[ma].c);
                    else
                        printf("%d\n", a[all].c);
                }
                else
                    printf("%d\n", a[mi].c+a[ma].c);
            }
            else
                printf("%d\n", max(a[mi].c, a[ma].c));
        }
    }
}
