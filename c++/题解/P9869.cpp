#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MX=1e5+5;
int n, m;
int fa[MX], vis[MX], w[MX], color[MX];
int head[MX], cnt;
bool erfentu=true;
struct node{
    int to, nex, w;
}edges[2*MX];
void add(int u, int v, int w){
    edges[++cnt].to=v;
    edges[cnt].w=w;
    edges[cnt].nex=head[u];
    head[u]=cnt;
}
int sizeu(int i){
    vis[i]=1;
    int ret=1;
    for(int e=head[i]; e; e=edges[e].nex){
        int v=edges[e].to;
        if(vis[v]==0)  ret+=sizeu(v);
    }
    return ret;
}
int dfs(int i, int c) {
    int ret=1;
    for(int e=head[i]; e; e=edges[e].nex) {
        int v=edges[e].to;
        if(color[v]!=0) {
            if(color[v]==c && edges[e].w==0)  continue;
            else if(color[v]==-c && edges[e].w==1)  continue;
            else erfentu=false;
        }else {
            if(edges[e].w==1)  color[v]=-c;
            else  color[v]=c;
            ret+=dfs(v, color[v]);
        }
    }
    return ret;
}

void init(){
    for(int i=0; i<=n; i++) {
        fa[i]=i;
    }
    memset(vis, 0, sizeof(vis));
    memset(w, 0, sizeof(w));
    memset(color, 0, sizeof(color));
    memset(head, 0, sizeof(head));
    memset(edges, 0, sizeof(edges));
    cnt=0;
}
signed main() {
    int t, c;
    cin >> c >> t;
    while(t--) {
        cin >> n >> m;
        init();
        for(int i=1; i<=m; i++) {
            int x, y;
            char v;
            cin >> v;
            if(v=='+' || v=='-')  cin >> x >> y;
            else  cin >> x;
            
            if(v=='U')  fa[x]=n+1;
            else if(v=='T')  fa[x]=n+2;
            else if(v=='F')  fa[x]=n+3;
            else if(v=='+')  fa[x]=fa[y], w[x]=w[y];
            else  fa[x]=fa[y], w[x]=(w[y]^1);
        }
        for(int i=1; i<=n; i++) {
            add(i, fa[i], w[i]);
            add(fa[i], i, w[i]);
        }
        
        int ans=0;
        for(int i=1; i<=n; i++) {
            erfentu=1;
            if(!color[i]) {
                color[i]=1;
                int sz=dfs(i, 1);
                if(!erfentu) {
                    ans+=sz;
                }
            }
        }
        cout << ans+sizeu(n+1)-1 << '\n';
        
    }
    return 0;
}