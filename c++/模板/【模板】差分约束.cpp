#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MX = 5005;
const int M  = 5005;
const int MAXE = M + MX + 5;   // m 条 + (n+1) 条超级源点边

int n, m, cnt;
int head[MX];
int dis[MX], tot[MX];
bool inq[MX];
queue<int> q;

struct node{
    int nex, to, w;
} edges[MAXE * 2];   // 保险起见再乘 2

void add(int u, int v, int w){
    edges[++cnt].to  = v;
    edges[cnt].nex   = head[u];
    edges[cnt].w     = w;
    head[u] = cnt;
}

bool spfa(int S){
    memset(dis, 0x3f, sizeof(dis));
    memset(tot, 0, sizeof(tot));
    memset(inq, 0, sizeof(inq));
    while(!q.empty()) q.pop();

    dis[S] = 0;
    q.push(S);
    inq[S] = true;
    tot[S] = 1;

    while(!q.empty()){
        int u = q.front(); q.pop();
        inq[u] = false;
        for(int e = head[u]; e; e = edges[e].nex){
            int v = edges[e].to, w = edges[e].w;
            if(dis[v] > dis[u] + w){
                dis[v] = dis[u] + w;
                if(!inq[v]){
                    q.push(v);
                    inq[v] = true;
                    tot[v]++;
                    // 图中节点总数 = n+1 (1..n 加上超级源点)
                    if(tot[v] >= n + 1) return false;  // 有负环
                }
            }
        }
    }
    return true;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;

    for(int i = 1; i <= m; i++){
        int c, cp, y;
        cin >> c >> cp >> y;
        // x_c - x_{cp} <= y  =>  x_c <= x_{cp} + y  =>  边 cp -> c, 权 y
        add(cp, c, y);
    }

    // 超级源点 n+1，向所有点连权 0 边
    int S = n + 1;
    for(int i = 1; i <= n; i++) add(S, i, 0);

    if(!spfa(S)){
        cout << "NO\n";
    } else {
        // 输出一组可行解
        for(int i = 1; i <= n; i++){
            cout << dis[i] << (i == n ? '\n' : ' ');
        }
    }
    return 0;
}