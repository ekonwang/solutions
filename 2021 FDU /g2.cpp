#include <iostream>
#include <algorithm>  
#include <vector>
#include <cassert>
using namespace std;
#define debug(x) {cout<<#x<<" -> "<<x<<endl;}
#define debugi(v) {cout<<#v<<endl;for(auto &x:v) cout << x << " ";cout<<endl;}
typedef unsigned long long ll;
const ll N = 2e6, hashmagic = 1e9 + 7;
struct trienode
{
    ll count;
    ll children[26];
    trienode() {}
} nodes[N], nodes1[N];
ll nxt, n, m;
string a[N], b[N];
vector<int> veca[N], vecb[N];
void insert(string &s, trienode *r, int vi)
{   
    int len = s.length();
    int vpos = veca[vi].size()-1;
    for (int i=0;i<len;i++)
    {
        int index = s[i]-'a';
        if (r->children[index] == 0)
            r->children[index] = ++nxt;
        r = &nodes[r->children[index]];
        if (vpos>=0 && veca[vi][vpos] <= i) 
        {
            assert(veca[vi][vpos] == i);
            r->count++;
            vpos--;
        }
    }
}
void insert1(string &s, trienode *r, int vi)
{   
    int len = s.length();
    int vpos = vecb[vi].size()-1;
    for (int i=0;i<len;i++)
    {
        int index = s[i]-'a';
        if (r->children[index] == 0)
            r->children[index] = ++nxt;
        r = &nodes1[r->children[index]];
        if (vpos>=0 && vecb[vi][vpos] <= i) 
        {
            assert(vecb[vi][vpos] == i);
            r->count++;
            vpos--;
        }
    }
}
ll query(string &s, trienode *r)
{
    int len = s.length();
    ll res = 0;
    for (int i=0;i<len;i++)
    {
        int index = s[i]-'a';
        if (r->children[index] == 0)
            return 0;
        r = &nodes[r->children[index]];
    }
    return r->count; 
}
ll query1(string &s, trienode *r)
{
    int len = s.length();
    ll res = 0;
    for (int i=0;i<len;i++)
    {
        int index = s[i]-'a';
        if (r->children[index] == 0)
            return 0;
        r = &nodes1[r->children[index]];
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
int main()
{
    // freopen(".in", "r", stdin);
    ll res = 0;
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i=0;i<n;i++) 
    {
        cin >> a[i];
        int len = a[i].length();
        veca[i].push_back(len-1);
        ll lhash = 0, rhash = 0;
        for (int j=1;j<=len-1;j++)
        {
            lhash = lhash + fastpower(hashmagic, j-1) * (a[i][len-j]);
            rhash = rhash * hashmagic + (a[i][len-j]);
            if (lhash == rhash)
            {
                veca[i].push_back(len-j-1);
            }
        }
        insert(a[i], &nodes[0], i);
    }
    cin >> m;
    for (int i=0;i<m;i++)
    {
        cin >> b[i];
        int len = b[i].length();
        string s = b[i];
        reverse(s.begin(), s.end());
        ll lhash = 0, rhash = 0;
        for (int j=1;j<=len-1;j++)
        {
            lhash = lhash + fastpower(hashmagic, j-1) * (s[len-j]);
            rhash = rhash * hashmagic + (s[len-j]);
            if (lhash == rhash)
            {
                vecb[i].push_back(len-j-1);
            }
        }
        insert1(s, &nodes1[0], i);
    }
    for (int i=0;i<n;i++)
    {
        res += query1(a[i], &nodes1[0]);
    }
    for (int i=0;i<m;i++)
    {
        reverse(b[i].begin(), b[i].end());
        res += query(b[i], &nodes[0]);
    }
    cout << res << endl;
    return 0;
}
/* 
2
abaka
aba
2
ba
kaba
 */