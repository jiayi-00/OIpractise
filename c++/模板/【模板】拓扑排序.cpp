#include<bits/stdc++.h>
#define int long long
using namespace std;
int head[105], cnt;
int n;
int du[105];
struct node{
    int to, nex;
}edges[205];
void add(int u, int v){
    edges[++cnt].to=v;
    edges[cnt].nex=head[u];
    head[u]=cnt;
}
signed main() {
    cin >> n;
    for(int i=1; i<=n; i++) {
        int x;
        while(cin >> x && x!=0) {
            add(i, x);
            du[x]++;
        }
    }
    queue<int > q;
    for(int i=1; i<=n; i++) {
        if(du[i]==0) q.push(i);
    }
    while(!q.empty()) {
        int u=q.front(); q.pop();
        cout << u << ' ';
        for(int e=head[u]; e; e=edges[e].nex) {
            int v=edges[e].to;
            du[v]--;
            if(du[v]==0)  q.push(v);
        }
    }
    return 0;
}