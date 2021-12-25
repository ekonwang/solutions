#pragma GCC OPTIMIZE ('O3')
#include <bits/stdc++.h>
#define debug(x) {std::cout<< \
 "[" <<#x <<"->"<< x<<"]"<< \
std::endl;}
#define debugLine {std::cout<< \
"\n======= Debug =======\n" << \
std::endl;}
using namespace std;
typedef long long ll;
typedef struct Point{
int x, y, w;
} P;
typedef struct  Edge{
    /* data */
    int to, w;
} E;


const int N = 2e5 + 10;
int x, y, t, n, m, c[N];
P a[N];
vector<E> g[N];

int bits(int &v) {
    int cnt = 0;
    for (int i=0;i<30;i++) {
        cnt += ((v>>i) & 0x1);
    }
    return cnt;
}

bool dfs(int u) {
    for (auto elem: g[u]) {
        int v = elem.to;
        int w = elem.w;
        if (c[v] == -1) {
            c[v] = c[u] ^ w;
            if (dfs(v) == false) 
                return false; 
        }else {
            if(c[v] ^ (c[u] ^ w)) {
                return false;
            }
        }
    } 
    return true;
}

bool color() {
    for (int i=1;i<=n;i++) {
        if (c[i] == -1) {
            c[i] = 0;
            if(dfs(i)==false) {
                return false;
            }
        }
    }
    return true;
}

void solve() {
    cin >> n >> m;
    for (int i=1;i<=n;i++) {
        c[i] = -1;
        g[i].clear();
    }
    for (int i=1;i<=n-1;i++) {
        cin >> a[i].x >> a[i].y >> a[i].w;
        if (a[i].w>=0) {
            int bitn = bits(a[i].w);
            g[a[i].x].push_back({a[i].y, bitn % 2});
            g[a[i].y].push_back({a[i].x, bitn % 2});
        }
    }
    for (int i=1;i<=m;i++) {
        int x, y, w;
        cin >> x >> y >> w;
        g[x].push_back({y, w});
        g[y].push_back({x, w});
    }
    if(color()) {
        cout << "YES" << "\n";
        for (int i=1;i<=n-1;i++) {
            cout << a[i].x << " " << a[i].y << " ";
            if (a[i].w >= 0) cout << a[i].w << "\n";
            else cout << (c[a[i].x] ^ c[a[i].y]) << "\n";
        }
    } else {
        cout << "NO" << "\n";
    }
}

int main() {
    //freopen(".in", "r", stdin);
    ios::sync_with_stdio(0);
    cin >> t;
    while(t--)
    solve();
}
