#include <string>
#include <cstring>
#include <iostream>
#include <cstdio>
#define debug(x) {std::cout << #x << " -> " << x << std::endl;}
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
ll res;
ll t, n, dp[N][10], l, c[N];
const int mod = 998244353;
char s[N];
int fast_power(ll base, ll exp) {
    ll ret=1; while(exp) {
        if (exp & 0x1) {
            ret *= base; ret %= mod;
        }
        base *= base; base %= mod; exp = exp >> 1;
    }
    return ret;
}
void init() {
    res = 0;
    for (int i=0;i<n+2;i++) {
        c[i] = 0;
        for(int j=0;j<10;j++)
            dp[i][j] = 0;
    }
}
int main() {
    //freopen(".in", "r", stdin);
    scanf("%lld", &t);
    while(t--) {
        scanf("%s", &(s[1]));
        l = strlen(&(s[1])); n = l;
        init();
        for (int i=l;i>0;i--) {
            if (s[i] == 'a') 
                c[i] = c[i+1] + 1;
            else c[i] = c[i+1];
        }
        for (int i=1;i<=l;i++) {
            dp[i][1] = dp[i-1][1];
            dp[i][2] = dp[i-1][2];
            dp[i][3] = dp[i-1][3];
            dp[i][4] = dp[i-1][4];
            dp[i][5] = dp[i-1][5];
            dp[i][6] = dp[i-1][6];
            dp[i][7] = dp[i-1][7];
            dp[i][8] = dp[i-1][8];
            switch (s[i])
            {
            case 'n':
                dp[i][1] = (dp[i-1][1] + 1) % mod;
                dp[i][3] = (dp[i-1][3] + dp[i-1][2]) % mod;
                break;
            case 'u':
                dp[i][2] = (dp[i-1][2] + dp[i-1][1]) % mod;
                break;
            case 'h':
                dp[i][4] = (dp[i-1][4] + dp[i-1][3]) % mod;
                dp[i][6] = (dp[i-1][6] + dp[i-1][5]) % mod;
                dp[i][7] = (dp[i-1][7] + dp[i-1][6]) % mod;
                dp[i][9] = dp[i-1][8];
                break;
            case 'e':
                dp[i][5] = (dp[i-1][5] + dp[i-1][4]) % mod;
                dp[i][8] = (dp[i-1][8] + dp[i-1][7]) % mod;
                break;
            default:
                break;
            }
        }
        for (int i=9; i<l;i++) {
            ll local = (fast_power(2, c[i+1])-1);
            local = local * dp[i][9];
            local = local % mod;
            res += local;
        }   
        res %= mod;
        printf("%lld\n", res);
    }
}