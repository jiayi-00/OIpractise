#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MX = 500005;
int c, n, m, q;
int x[MX], y[MX];
int yuanx[MX], yuany[MX];
int idx[MX], kx;
int idy[MX], ky;
int xpremn[MX], xpremnid[MX];
int xpremx[MX], xpremxid[MX];
int ypremn[MX], ypremnid[MX];
int ypremx[MX], ypremxid[MX];
int xpostmn[MX], xpostmnid[MX];
int xpostmx[MX], xpostmxid[MX];
int ypostmn[MX], ypostmnid[MX];
int ypostmx[MX], ypostmxid[MX];

// 检查(1,1)到(h,l)范围可否画线 x<y的情况
bool check1(int h, int l) {
    if (h == 0 || l == 0) return 1; // 边界
    int nh = h, nl = l;
    if (ypremn[l] > xpremn[h]) {
        // y的最小值 > x的最小值
        // 那么 xpremnid[n]行 可以和 1~m 列 都是1
        nh = xpremnid[h] - 1;
    }
    if (xpremx[h] < ypremx[l]) {
        // x的最大值 < y的最大值
        // 那么 ypremxid[l]列 可以和 1~n 行 都是1
        nl = ypremxid[l] - 1;
    }
    //行列都无法画线，那么无解
    if (h == nh && l == nl) return false;
    return check1(nh, nl);
}

// 检查(h,l)到(n,m)范围可否画线 x<y的情况
bool check2(int h, int l) {
    if (h == n+1 || l == m+1) return 1;
    int nh = h, nl = l;
    if (ypostmn[l] > xpostmn[h]) {
        nh = xpostmnid[h] + 1;
    }
    if (xpostmx[h] < ypostmx[l]) {
        nl = ypostmxid[l] + 1;
    }
    if (h == nh && l == nl) return false;
    return check2(nh, nl);
}

bool check11(int h, int l) { // x>y的情况
    // 把check1程序x和y反转即可
    if (h == 0 || l == 0) return 1;
    int nh = h, nl = l;
    if (ypremn[l] < xpremn[h]) {
        nl = ypremnid[l] - 1;
    }
    if (xpremx[h] > ypremx[l]) {
        nh = xpremxid[h] - 1;
    }
    if (h == nh && l == nl) return false;
    return check11(nh, nl);
}

bool check22(int h, int l) { // x>y的情况
    // 把check2程序x和y反转即可
    if (h == n+1 || l == m+1) return 1;
    int nh = h, nl = l;
    if (ypostmn[l] < xpostmn[h]) {
        nl = ypostmnid[l] + 1;
    }
    if (xpostmx[h] > ypostmx[l]) {
        nh = xpostmxid[h] + 1;
    }
    if (h == nh && l == nl) return false;
    return check22(nh, nl);
}

int work() {
    int mx = 0, mxid, mn = 1e18, mnid;
    for (int i = 1; i <= n; i ++) {
        if (x[i] < mn) mn = x[i], mnid = i;
        xpremn[i] = mn, xpremnid[i] = mnid;
        if (x[i] > mx) mx = x[i], mxid = i;
        xpremx[i] = mx, xpremxid[i] = mxid;
    }
    mx = 0, mn = 1e18;
    for (int i = 1; i <= m; i ++) {
        if (y[i] < mn) mn = y[i], mnid = i;
        ypremn[i] = mn, ypremnid[i] = mnid;
        if (y[i] > mx) mx = y[i], mxid = i;
        ypremx[i] = mx, ypremxid[i] = mxid;
    }
    mx = 0, mn = 1e18;
    for (int i = n; i >= 1; i --) {
        if (x[i] < mn) mn = x[i], mnid = i;
        xpostmn[i] = mn, xpostmnid[i] = mnid;
        if (x[i] > mx) mx = x[i], mxid = i;
        xpostmx[i] = mx, xpostmxid[i] = mxid;
    }
    mx = 0, mn = 1e18;
    for (int i = m; i >= 1; i --) {
        if (y[i] < mn) mn = y[i], mnid = i;
        ypostmn[i] = mn, ypostmnid[i] = mnid;
        if (y[i] > mx) mx = y[i], mxid = i;
        ypostmx[i] = mx, ypostmxid[i] = mxid;
    }
    int h = xpremnid[n]; // x序列的最小值位置
    int l = ypremxid[m]; // y序列的最大值位置
    return check1(h, l) && check2(h, l) || 
           check11(h, l) && check22(h, l);
}

signed main() {
    cin >> c >> n >> m >> q;
    for (int i = 1; i <= n; i ++) {
        scanf("%lld", &yuanx[i]);
        x[i] = yuanx[i];
    }
    for (int i = 1; i <= m; i ++) {
        scanf("%lld", &yuany[i]);
        y[i] = yuany[i];
    }
    printf("%lld", work());
    while (q--) {
        scanf("%lld%lld", &kx, &ky);
        int id, v;
        for (int i = 1; i <= kx; i ++) {
            scanf("%lld%lld", &id, &v);
            x[id] = v, idx[i] = id;
        }
        for (int i = 1; i <= ky; i ++) {
            scanf("%lld%lld", &id, &v);
            y[id] = v, idy[i] = id;
        }
        printf("%lld", work());
        for (int i = 1; i <= kx; i ++)
            x[idx[i]] = yuanx[idx[i]];
        for (int i = 1; i <= ky; i ++)
            y[idy[i]] = yuany[idy[i]];
    }
    return 0;
}