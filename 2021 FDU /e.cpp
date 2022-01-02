#include <iostream>
#include <cassert>
#include <vector>
using namespace std;
#define debug(x) {cout<<#x<<" -> "<<x<<endl;}
int n;
struct con
{
    int x;
    int y;
};
void put(con&A, bool slot)
{
    printf("%d %d", A.x, A.y);
    if (slot) printf(" ");
    else printf("\n");
}
vector<struct con> v[501]; 
void oddput(int m)
{
    assert(m&0x1);
    int even = (m-1);
    int broad = (m+1)/2;
    for (int i=1;i<=even/2;i++)
    {
        for (int j=0;j<i;j++)
        {
            v[i<<1].push_back({even-(i<<1)+2-!(j&0x1), broad-j});
            v[i<<1].push_back({even-(i<<1)+2-(j&0x1), broad-j});
        }
    }
    for (int i=0;i<=even/2;i++)
    {
        for (int j=0;j<=i;j++)
        {
            if (j)
                v[(i<<1)+1].push_back({(i<<1)+(j&0x1), i+1-j});
            v[(i<<1)+1].push_back({(i<<1)+!(j&0x1), i+1-j});
        }
    }
}
int main()
{
    scanf("%d", &n);
    if (n&0x1) 
    {
        printf("%d %d\n", n, (n+1)/2);
        oddput(n);
    }
    else 
    {
        printf("%d %d\n", n+1, n/2);
        oddput(n-1);
        for (int i=1;i<=n/2;i++)
        {
            v[n].push_back({n+(i&0x1), i});
            v[n].push_back({n+!(i&0x1), i});
        }
    }
    for (int i=1;i<=n;i++)
    {
        assert(i==v[i].size());
        for (int j=0;j<i;j++)
            put(v[i][j], j<i-1);
    }
}