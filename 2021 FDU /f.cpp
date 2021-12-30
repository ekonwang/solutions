#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
#define debug(x) {cout<<#x<<" -> "<<x<<endl;}
typedef long long ll;
struct point{
    double x;
    double y;
    double operator*(point&A) const // 叉积
    {
        return x * A.y - A.x * y;
    }
    friend ostream& operator<<(ostream &out, const point&A)
    {
        out<<"("<< A.x<<", " <<A.y <<") ";
        return out;
    }
    point(double ax, double ay) 
    {
        x = ax, y = ay;
    }
    point() 
    {
        x = y = 0;
    }
};
inline double xmul(point &a1, point &a2, point &b1, point &b2)
{
    point a(a2.x-a1.x, a2.y-a1.y);
    point b(b2.x-b1.x, b2.y-b1.y);
    double xres = a*b;
    return xres;
}
inline bool ifcross(point &a1, point &a2, point &b1, point &b2)
{
    double res1 = xmul(a1, a2, a1, b1) * xmul(a1, a2, a1, b2);
    double res2 = xmul(b1, b2, b1, a1) * xmul(b1, b2, b1, a2);
    return res1<=0 && res2<=0;
}
inline point crosspoint(point &a1, point &a2, point &b1, point &b2)
{
    double d = (a2.x-a1.x)*(b2.y-b1.y) -  (b2.x-b1.x)*(a2.y-a1.y);
    double c1 = a1.x*(a2.y-a1.y) - a1.y*(a2.x-a1.x);
    double c2 = b1.x*(b2.y-b1.y) - b1.y*(b2.x-b1.x);
    double x = (c2*(a2.x-a1.x) - c1*(b2.x-b1.x))/d;
    double y = (c2*(a2.y-a1.y) - c1*(b2.y-b1.y))/d;
    point res(x, y);
    return res;
}
const ll N = 1e5 + 1;
point a[N], p1, p2;
ll n, stat[N], pos, neg, zero;
vector<point> origin;
double area(vector<point> vec)
{
    double res = 0.;
    int len = vec.size();
    for (int i=1;i<len-1;i++)
    {
        double local = xmul(vec[0], vec[i], vec[0], vec[i+1]) / 2;
        local = abs(local);
        res += local;
    }
    return res;
}
int main()
{
    //freopen(".in", "r", stdin);
    scanf("%lld", &n);
    for (int i=0;i<n;i++)
    {
        scanf("%lf%lf", &a[i].x, &a[i].y);
        origin.push_back(a[i]);
    }
    scanf("%lf%lf%lf%lf", &p1.x, &p1.y, &p2.x, &p2.y);
    for (int i=0;i<n;i++)
    {
        double xres = xmul(p1, p2, p1, a[i]);
        if (xres > 0) 
        {
            pos ++; stat[i]=1;
        }
        else if (xres == 0) 
        {
            zero ++; stat[i]=0;
        }
        else {
            neg ++; stat[i]=-1;
        }
    }
    if (pos + zero == n || neg + zero == n)
    {
        printf("0\n"); 
        return 0;
    }
    int prefind = 0;
    while(!stat[prefind]) 
    {
        prefind++;
    }
    int find = -stat[prefind], begin = 0, end = n;
    vector<point> vec;
    for (int i=0;i<n;i++)
    {
        if (stat[i] == find)
        {
            if (!begin) 
            {
                vec.push_back(crosspoint(p1, p2, a[i-1], a[i]));
                begin = i; 
            }
            vec.push_back(a[i]);
        }
        else
        {
            if (begin && end==n) end = i;
        }
    }
    vec.push_back(crosspoint(p1, p2, a[end-1], a[end%n]));
    double totarea = area(origin);
    double partarea = area(vec);
    double res = min(totarea-partarea, partarea);
    printf("%.8lf\n", res);
}
