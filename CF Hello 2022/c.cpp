#include <iostream>
using namespace std;
const int N = 1e5;
int vis[N], map[N], n, t, pos;
#define debug(x) {cout<<#x<<" -> "<<x<<endl;}
int main()
{
    scanf("%d", &t);
    while(t--)
    {
        pos = 1;
        scanf("%d", &n);
        for (int i=1;i<=n+1;i++)
            vis[i] = 0;
        while(pos<=n)
        {
            int need = -1, last, now = -1;
            while(need != pos)
            {
                printf("? %d\n", pos);
                fflush(stdout);
                scanf("%d", &need);
            }
            last = pos;
            while(now != pos)
            {
                printf("? %d\n", pos);
                fflush(stdout);
                scanf("%d", &now);
                map[last] = now;
                vis[last] = 1;
                last = now;
            }
            while(vis[pos]) pos++;
        }
        printf("!");
        for(int i=1;i<=n;i++)
        {
            printf(" %d", map[i]);
        }
        printf("\n");
        fflush(stdout);
    }
}