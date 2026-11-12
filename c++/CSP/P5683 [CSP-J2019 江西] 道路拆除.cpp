#include<bits/stdc++.h>
using namespace std;

int n,m,a[3001][3001],s1,t1,s2,t2;
int dist1[3001], dist_s1[3001], dist_s2[3001];
int q[3001], front, rear;  // 改名为 q
bool vis[3001];
int ans;

void bfs(int start, int dist[]) {
    for(int i=1; i<=n; i++) {
        dist[i] = 1000000000;
        vis[i] = false;
    }
    dist[start] = 0;
    vis[start] = true;
    front = 0; rear = 0;
    q[rear++] = start;  // 使用 q
    
    while(front < rear) {
        int u = q[front++];  // 使用 q
        for(int v=1; v<=n; v++) {
            if(a[u][v] && !vis[v]) {
                dist[v] = dist[u] + 1;
                vis[v] = true;
                q[rear++] = v;  // 使用 q
            }
        }
    }
}

int main(){
    
    cin>>n>>m;
    int x,y;
    for(int i=1; i<=m; i++){
        cin>>x>>y;
        a[x][y]=a[y][x]=1;
    }
    cin>>s1>>t1>>s2>>t2;
    
    // 计算从1、s1、s2出发到所有点的最短距离
    bfs(1, dist1);
    bfs(s1, dist_s1);
    bfs(s2, dist_s2);
    
    // 先检查是否满足条件
    if(dist1[s1] > t1 || dist1[s2] > t2) {
        cout<<-1;
        return 0;
    }
    
    int min_keep = 1000000000;
    // 枚举中间点x
    for(int x=1; x<=n; x++) {
        if(dist1[x] + dist_s1[x] <= t1 && dist1[x] + dist_s2[x] <= t2) {
            int total = dist1[x] + dist_s1[x] + dist_s2[x];
            if(total < min_keep) {
                min_keep = total;
            }
        }
    }
    
    if(min_keep == 1000000000) {
        cout<<-1;
    } else {
        cout<<m - min_keep;
    }
    
    return 0;
}
