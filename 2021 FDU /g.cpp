#include <iostream>
#include <algorithm>  
using namespace std;
#define debug(x) {cout<<#x<<" -> "<<x<<endl;}
typedef long long ll;
const ll N = 2e6, hashmagic = 1e9 + 7;
struct trienode
{
    ll count;
    ll children[26];
    trienode() {}
} nodes[N], nodes1[N];
ll nxt, n, m;
string a[N], b[N];
void insert(string &s, trienode *r)
{   
    int len = s.length();
    for (int i=0;i<len;i++)
    {
        int index = s[i]-'a';
        if (r->children[index] == 0)
            r->children[index] = ++nxt;
        r = &nodes[r->children[index]];
    }
    r->count++;
}
ll query(string &s, trienode *r)
{
    int len = s.length();
    for (int i=0;i<len;i++)
    {
        int index = s[i]-'a';
        if (r->children[index] == 0)
            return 0;
        r = &nodes[r->children[index]];
    }
    return r->count; 
}
ll fastpower(ll base, ll exp)
{
    ll res = 1;
    while(exp)
    {
        if (exp & 0x1)
            res *= base;
        base *= base;
        exp = exp >> 1;
    }
    return res;
}
ll Hash(string &s)
{
    ll res = 0;
    int len = s.length();
    for (int i=0;i<len;i++)
    {
        res *= hashmagic;
        res += (s[i]-'a'+1);
    }
    return res;
}
ll reverse_Hash(string &s)
{
    ll res = 0;
    int len = s.length();
    for (int i=len-1;i>=0;i--)
    {
        res *= hashmagic;
        res += (s[i]-'a'+1);
    }
    return res;
}
int main()
{
    freopen(".in", "r", stdin);
    ll res = 0;
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i=0;i<n;i++) 
    {
        cin >> a[i];
        int len = a[i].length();
        string s = a[i];
        reverse(s.begin(), s.end());
        insert(s, &nodes[0]);
        for (int j=1;j<=len-1;j++)
        {
            string sub = s.substr(0, j);
            if (Hash(sub) == reverse_Hash(sub))
            {
                string ins = s.substr(j, len-j);
                insert(ins, &nodes[0]);
            }   
        }
    }
    cin >> m;
    for (int i=0;i<m;i++)
    {
        cin >> b[i];
        int len = b[i].length();
        string s = b[i];
        reverse(s.begin(), s.end());
        for (int j=1;j<=len-1;j++)
        {
            string sub = b[i].substr(0, j);
            if (Hash(sub) == reverse_Hash(sub))
            {
                string ins = s.substr(0, len-j);
                insert(ins, &nodes1[0]);
            }   
        }
    }
    for (int i=0;i<n;i++)
    {
        res += query(a[i], &nodes1[0]);
    }
    for (int i=0;i<m;i++)
    {
        res += query(b[i], &nodes[0]);
    }
    cout << res << endl;
    return 0;
}