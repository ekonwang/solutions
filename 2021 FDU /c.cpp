#include <iostream>
#include <stack>
#include <cassert>
using namespace std;
#define debug(x) {cout << #x << " -> " << x << endl;}
typedef long long ll;
struct con
{
    ll length;
    ll color;
    con(ll l, ll c)
    {
        length = l;
        color = c;
    }
    bool operator<(const con&A) const
    {
        return length<=A.length;
    }
};
const ll N = 1e6 + 10;
stack<struct con> stk;
ll n, m, cnt[N], tot;
void add(ll color)
{
    if (cnt[color]++ == 0)
        tot++; 
}
void del(ll color)
{
    assert(cnt[color]);
    if (--cnt[color] == 0) 
        tot--;
}
void deladd(ll len, ll color)
{
    con newadd = con(len, color);
    while(!stk.empty()) {
        con &elem = stk.top();
        if (elem<newadd) {
            stk.pop();
            del(elem.color);            
        }
        else 
            break;
    }
    stk.push(newadd);
    add(color);
}
int main()
{
    //freopen(".in", "r", stdin);
    scanf("%lld%lld", &n, &m);
    deladd(n, 0);
    for (int i=1;i<=m;i++)
    {
        ll cmd, len, color;
        scanf("%lld", &cmd);
        if (cmd == 1)
        {
            scanf("%lld%lld", &len, &color);
            deladd(len, color);
        }
        else 
        {
            printf("%lld\n", tot);
        }
    }
}
