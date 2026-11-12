#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m, ans, outn;
int cnt, head[10005];
int du[10005], s[10005];
struct {
    int to, nex;
}edges[20005];
void add(int u, int v){
    edges[++cnt].to = v;
    edges[cnt].nex = head[u];
    head[u] = cnt;
}
queue <int> q;
signed main(){
    cin >> n >> m;
    for(int i=1; i<=m; i++){
        int a,b;
        cin >> a >> b;
        add(b,a);
        du[a]++;
    }
    for(int i=1; i<=n; i++){
        if(du[i]==0) q.push(i);
    }
    for(int i=1; i<=n; i++)  s[i]=100;
    while(!q.empty()){
        outn++;
        int u = q.front();
        ans += s[u];
        q.pop();
        for(int i=head[u]; i; i=edges[i].nex){
            int v = edges[i].to;
            s[v]=max(s[v], s[u]+1);
            du[v]--;
            if(du[v]==0){
                q.push(v);
            } 
        }
    }
    if(outn < n) {
        cout << "Oh no";
    }
    else  cout << ans << endl;
    return 0;
}